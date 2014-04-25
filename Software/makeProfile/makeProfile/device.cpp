#include "device.h"
#include "devicethread.h"
#include "deviceconnection.h"

Device::Device(QObject *parent) : QObject(parent)
{
    // Get the device connection.
    mConnection = DeviceThread::getConnection();

    // Create the connections.
    connect(mConnection, SIGNAL(connected()), this, SLOT(connected()));
    connect(mConnection, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mConnection, SIGNAL(error(const QString&)), this, SLOT(error(const QString&)));
    connect(mConnection, SIGNAL(error(const QString&)), this, SIGNAL(deviceError(const QString&)));
    connect(mConnection, SIGNAL(transactionStarted(DeviceTransactionPtr)),
        this, SIGNAL(transactionStarted(DeviceTransactionPtr)));
    connect(mConnection, SIGNAL(transactionComplete(DeviceTransactionPtr)),
        this, SIGNAL(transactionComplete(DeviceTransactionPtr)));
    connect(mConnection, SIGNAL(transactionFailed(DeviceTransactionPtr)),
        this, SIGNAL(transactionFailed(DeviceTransactionPtr)));
    connect(this, SIGNAL(startWrite(quint8,const QByteArray&,const QVariant&)),
        mConnection, SLOT(write(quint8,const QByteArray&,const QVariant&)));
    connect(this, SIGNAL(startRead(quint8,quint64,const QVariant&)),
        mConnection, SLOT(read(quint8,quint64,const QVariant&)));
}

Device::~Device()
{
    // nothing here
}

void Device::connected()
{
    mConnected = true;

    // Debug for my LCD.
    uint8_t clearCmd[] = { 0xFE, 0x51 };
    sendWrite(0x28, clearCmd, 2);
    sendWrite(0x28, "Hello I2C!", 10);
}

void Device::disconnected()
{
    mConnected = false;
}

void Device::error(const QString& msg)
{
    mLastError = msg;
}

QString Device::lastError() const
{
    return mLastError;
}

bool Device::isConnected() const
{
    return mConnected;
}

DeviceConnection* Device::connection() const
{
    return mConnection;
}

void Device::sendWrite(uint8_t addr, const QByteArray& data,
    const QVariant& userData)
{
    emit startWrite(addr, data, userData);
}

void Device::sendWrite(uint8_t addr, const uint8_t *data, size_t sz,
    const QVariant& userData)
{
    startWrite(addr, QByteArray((char*)data, sz), userData);
}

void Device::sendRead(uint8_t addr, size_t sz, const QVariant& userData)
{
    emit startRead(addr, sz, userData);
}
