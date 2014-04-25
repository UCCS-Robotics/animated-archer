#include "deviceconnection.h"
#include "crc32.h"
#include "hid.h"

#define DEVICE_MAX (1)
#define DEVICE_VID (0x16C0)
#define DEVICE_PID (0x0486)
#define DEVICE_USAGE_PAGE (0xFFAB)
#define DEVICE_USAGE (0x0200)

#define UPDATE_TIME (5) // 100ms
#define LOST_TIME (2000)  // 2s

DeviceConnection::DeviceConnection(QObject *parent) :
    QObject(parent), mReportedBadFirmware(false),
    mNextTransactionID(1),
    mState(DeviceState_Disconnected)
{
    // Initialize the CRC-32 module.
    crc32_init();

    // Periodicly call update().
    mUpdateTimer.start(UPDATE_TIME);

    // Connect the timers.
    connect(&mUpdateTimer, SIGNAL(timeout()), this, SLOT(update()));
    connect(&mDeviceLostTimer, SIGNAL(timeout()), this, SLOT(deviceLost()));
}

void DeviceConnection::update()
{
    // Iterator for the pending transactions.
    QMutableMapIterator<uint32_t, DeviceTransactionPtr> it(mPendingTransactions);

    // Process dead transactions.
    while(it.hasNext())
    {
        it.next();

        if(it.value()->msElapsed() > TRANS_TIMEOUT)
        {
            emit error(tr("Transaction with ID %1 timed out.").arg(
                it.value()->id()));
            emit transactionFailed(it.value());

            it.remove();
        }
    }

    // Buffer to store the packet in.
    uint8_t buffer[PACKET_SIZE];

    //  If the device is not connected, try to connect to the device.
    if(mState == DeviceState_Disconnected)
    {
        // Try to connect to the device.
        if(rawhid_open(DEVICE_MAX, DEVICE_VID, DEVICE_PID,
            DEVICE_USAGE_PAGE, DEVICE_USAGE) <= 0)
        {
            // Failed to connect to the device, stay disconnected.
            return;
        }
        else
        {
            // We connected to the device, let the client know.
            emit connected();

            // Update the device state.
            mState = DeviceState_Connected;

            // Start the device lost timer.
            mDeviceLostTimer.start(LOST_TIME);

            // Make sure we reset the firmware error.
            mReportedBadFirmware = false;
        }
    }

    // Check if a packet has arrived.
    int sz = rawhid_recv(0, buffer, PACKET_SIZE, RECV_TIMEOUT);

    // Check if the device was disconnected.
    if(sz < 0)
    {
        // Close the device.
        rawhid_close(0);

        // Let the client know the device was disconnected.
        emit disconnected();

        // Update the device state.
        mState = DeviceState_Disconnected;

        // Stop the device lost timer.
        mDeviceLostTimer.stop();

        return;
    }

    // Check if we have a new packet.
    if(sz == 0)
        return;

    // Check that the whole packet was read.
    if(sz != PACKET_SIZE)
    {
        emit error(tr("Packet size was %1 but we expected %2.").arg(
            sz).arg(PACKET_SIZE));

        return;
    }

    // Cast the buffer to a packet.
    Packet *p = (Packet*)buffer;

    // Calculate the CRC-32 checksum of the packet.
    uint32_t crc = crc32(buffer, PACKET_SIZE - 4);

    // Validate the CRC-32 checksum. If it's invalid, ignore the packet.
    if(p->crc != crc)
    {
        emit error(tr("Bad packet checksum. Packet ignored."));

        return;
    }

    // Sanity check the size.
    if(p->sz > 48)
    {
        emit error(tr("Data size of %1 is out of bounds.").arg(p->sz));

        return;
    }

    // Restart the device lost timer since we got some data back.
    mDeviceLostTimer.stop();
    mDeviceLostTimer.start(LOST_TIME);

    // Process the packet based on it's type.
    // Ignore all unknown or unhandled packet types.
    switch(p->type)
    {
        case PacketType_Info:
            parseInfo(p);
            break;
        case PacketType_Data:
            parseData(p);
            break;
        case PacketType_Status:
            parseStatus(p);
            break;
        default:
            emit error(tr("Unknown Packet type: %1 (%2)").arg(
                (char)p->type).arg((int)p->type));
            break;
    }
}

void DeviceConnection::parseInfo(Packet *p)
{
    // Only look at the info packet if we have not
    // checked the firmware version.
    if(mReportedBadFirmware)
        return;

    // The firmware has been checked now.
    mReportedBadFirmware = true;

    // Get the firmware version from the info packet.
    uint32_t firmwareVer = p->tag;

    if(firmwareVer < FIRMWARE_VER)
    {
        emit error(tr("Device firmware is old. The device "
            "may not function correctly."));
    }
    else if(firmwareVer > FIRMWARE_VER)
    {
        emit error(tr("Device firmware is new. The device "
            "may not function correctly."));
    }
}

void DeviceConnection::parseData(Packet *p)
{
    // Check for the pending transaction.
    if(!mPendingTransactions.contains(p->tag))
    {
        emit error(tr("Got data for unknown transaction %1.").arg(p->tag));

        return;
    }

    // Get the pending transaction.
    DeviceTransactionPtr trans = mPendingTransactions.take(p->tag);

    // Add the data to the transaction.
    if(p->sz)
        trans->setReadData(QByteArray((char*)p->data, p->sz));

    // The transaction is complete.
    emit transactionComplete(trans);
}

void DeviceConnection::parseStatus(Packet *p)
{
    // Check for the pending transaction.
    if(!mPendingTransactions.contains(p->tag))
    {
        emit error(tr("Got status for unknown transaction %1.").arg(p->tag));

        return;
    }

    // Get the pending transaction.
    DeviceTransactionPtr trans = mPendingTransactions.take(p->tag);

    // Check the return code.
    switch(p->data[0])
    {
        case 0:
        {
            // The transaction is complete.
            emit transactionComplete(trans);

            break;
        }
        case 1:
        {
            emit error(tr("Transaction with ID %1 was "
                "too long.").arg(p->tag));

            // The transaction failed.
            emit transactionFailed(trans);

            break;
        }
        case 2:
        {
            emit error(tr("Transaction with ID %1 was sent to an invalid"
                " address (or slave is not responding).").arg(p->tag));

            // The transaction failed.
            emit transactionFailed(trans);

            break;
        }
        default:
        {
        emit error(tr("Transaction with ID %1 encountered an "
            " unknown error.").arg(p->tag));

        // The transaction failed.
        emit transactionFailed(trans);

        break;
        }
    }
}

void DeviceConnection::deviceLost()
{
    // Don't bother if we know it is disconnected.
    if(mState == DeviceState_Disconnected)
    {
        mDeviceLostTimer.stop();
        return;
    }

    // Close the device.
    rawhid_close(0);

    // Let the client know the device was disconnected.
    emit disconnected();

    // Update the device state.
    mState = DeviceState_Disconnected;

    // Report an error.
    emit error(tr("Device timeout. Device has been lost to ninjas."));

    // Stop the device lost timer.
    mDeviceLostTimer.stop();
}

void DeviceConnection::write(quint8 addr, const QByteArray& _data,
    const QVariant& userData)
{
    // Make sure the device is connected.
    if(mState != DeviceState_Connected)
    {
        emit error(tr("Write will not complete because device is not connected."));

        return;
    }

    // To make shit easy.
    uint8_t *data = (uint8_t*)_data.constData();
    uint8_t sz = _data.size();

    // Sanity check the write size.
    if(sz > 48)
    {
        emit error(tr("Write size of %1 exceeeds the maximum"
            " of 48 bytes.").arg(sz));

        return;
    }

    // Sanity check the address.
    if(addr & 0x80)
    {
        emit error(tr("Address is not 7-bit. Shift it down?"));

        return;
    }

    // Where to write the packet data.
    uint8_t buffer[PACKET_SIZE];

    // Cast the buffer to a packet.
    Packet *p = (Packet*)buffer;

    // Set the packet info.
    p->type = PacketType_ReqWrite;
    p->addr = addr;
    p->sz = sz;
    p->reserved1 = 0;
    p->tag = nextTransactionID();
    p->reserved2 = 0;

    // Add the data to the packet.
    for(uint8_t i = 0; i < p->sz; i++)
        p->data[i] = data[i];

    // Zero the rest of the data.
    for(uint8_t i = p->sz; i < 48; i++)
        p->data[i] = 0;

    // Calculate the CRC-32 checksum.
    p->crc = crc32(buffer, PACKET_SIZE - 4);

    // Create a transaction for this device.
    DeviceTransactionPtr trans(new DeviceTransaction(
        DeviceTransaction::Transaction_Write, p->tag));
    trans->setAddress(addr);
    trans->setWriteData(QByteArray((char*)data, sz));
    trans->setUserData(userData);

    // Advertise the transaction.
    emit transactionStarted(trans);

    // Add the transaction to the pending transactions.
    mPendingTransactions[p->tag] = trans;

    // Send the packet to the device.
    sendPacket(p);
}

void DeviceConnection::read(quint8 addr, quint64 sz,
    const QVariant& userData)
{
    // Make sure the device is connected.
    if(mState != DeviceState_Connected)
    {
        emit error(tr("Read will not complete because device is not connected."));

        return;
    }

    // Sanity check the read size.
    if(sz > 48)
    {
        emit error(tr("Read size of %1 exceeeds the maximum"
            " of 48 bytes.").arg(sz));

        return;
    }

    // Sanity check the address.
    if(addr & 0x80)
    {
        emit error(tr("Address is not 7-bit. Shift it down?"));

        return;
    }

    // Where to write the packet data.
    uint8_t buffer[PACKET_SIZE];

    // Cast the buffer to a packet.
    Packet *p = (Packet*)buffer;

    // Set the packet info.
    p->type = PacketType_ReqRead;
    p->addr = addr;
    p->sz = sz;
    p->reserved1 = 0;
    p->tag = nextTransactionID();
    p->reserved2 = 0;

    // Zero the data.
    for(uint8_t i = 0; i < 48; i++)
        p->data[i] = 0;

    // Calculate the CRC-32 checksum.
    p->crc = crc32(buffer, PACKET_SIZE - 4);

    // Create a transaction for this device.
    DeviceTransactionPtr trans(new DeviceTransaction(
        DeviceTransaction::Transaction_Read, p->tag));
    trans->setAddress(addr);
    trans->setUserData(userData);

    // Advertise the transaction.
    emit transactionStarted(trans);

    // Add the transaction to the pending transactions.
    mPendingTransactions[p->tag] = trans;

    // Send the packet to the device.
    sendPacket(p);
}

uint32_t DeviceConnection::nextTransactionID()
{
    uint32_t id = mNextTransactionID;

    // Loop around but skip zero.
    if(mNextTransactionID == 0xFFFFFFFFUL)
        mNextTransactionID = 1;
    else
        mNextTransactionID++;

    return id;
}

void DeviceConnection::sendPacket(Packet *p)
{
    // Send the packet.
    int sentSize = rawhid_send(0, p, PACKET_SIZE, SEND_TIMEOUT);

    // Make sure it sent.
    if(sentSize != PACKET_SIZE)
        emit error(tr("Failed to send packet. Sent size: %1.").arg(sentSize));
}
