#ifndef DEVICECONNECTION_H
#define DEVICECONNECTION_H

#include "devicetransaction.h"

#include <QObject>
#include <QTimer>
#include <QMap>

#include <stdint.h>

class DeviceConnection : public QObject
{
    Q_OBJECT
public:
    explicit DeviceConnection(QObject *parent = 0);

signals:
    void connected();
    void disconnected();
    void error(const QString& error);

    void transactionStarted(const DeviceTransactionPtr& trans);
    void transactionComplete(const DeviceTransactionPtr& trans);
    void transactionFailed(const DeviceTransactionPtr& trans);

public slots:
    void write(quint8 addr, const QByteArray& data,
        const QVariant& userData = QVariant());
    void read(quint8 addr, quint64 sz,
        const QVariant& userData = QVariant());

private slots:
    void update();
    void deviceLost();

private:
    typedef enum _DeviceState
    {
        DeviceState_Connected,
        DeviceState_Disconnected,
    } DeviceState;

    // Firmware version.
    // 0xMMmmRRRR
    // MM - Major
    // mm - Minor
    // RRRR - Revision
    static const uint32_t FIRMWARE_VER = 0x01010001;

    // RawHID packets are always 64 bytes.
    static const int PACKET_SIZE = 64;

    // Time (in milliseconds) to wait for a packet to be sent before giving up.
    static const int SEND_TIMEOUT = 100;

    // Time (in milliseconds) to wait for a packet to be read before giving up.
    static const int RECV_TIMEOUT = 0;

    // Time (in milliseconds) to wait for a transaction to fail.
    static const int TRANS_TIMEOUT = 2000;

    // Time (in milliseconds) between info packets.
    static const unsigned int INFO_PACKET_DELAY = 1000; // 1 sec.

    typedef enum _PacketType
    {
      // These are sent from the PC to the device.
      PacketType_ReqRead = 'R',  // Request a read from an I2C slave.
      PacketType_ReqWrite = 'W', // Request a write to an I2C slave.

      // These are send from the device to the PC.
      PacketType_Info = 'I',     // Device is idle but responding/working.
      PacketType_Data = 'D',     // Data returned from a I2C slave read request.
      PacketType_Status = 'S',   // Status (return code) of a request.
    } PacketType;

    typedef struct _Packet
    {
      uint8_t  type;      // 00 Packet type.
      uint8_t  addr;      // 01 Address for the I2C slave.
      uint8_t  sz;        // 02 Size (in bytes) of the transaction.
      uint8_t  reserved1; // 03 Reserved byte (should be 0).
      uint32_t tag;       // 04 Data from PC that will be echoed back (or 0).
      uint32_t reserved2; // 08 Reserved bytes (should be 0).
      uint8_t  data[48];  // 0C Data for the command.
      uint32_t crc;       // 3C CRC-32 checksum of the packet (bytes 00-3B).
    } __attribute__ ((__packed__)) Packet;

    void parseInfo(Packet *p);
    void parseData(Packet *p);
    void parseStatus(Packet *p);

    uint32_t nextTransactionID();
    bool sendPacket(Packet *p);
    void close();

    bool mReportedBadFirmware;
    uint32_t mNextTransactionID;

    DeviceState mState;
    QTimer mUpdateTimer, mDeviceLostTimer;

    QMap<uint32_t, DeviceTransactionPtr> mPendingTransactions;
};

#endif // DEVICECONNECTION_H
