#ifndef DEVICETRANSACTION_H
#define DEVICETRANSACTION_H

#include "burstprogram.h"

#include <QDateTime>
#include <QByteArray>
#include <QVariant>
#include <QSharedDataPointer>
#include <stdint.h>

class DeviceTransactionData;

class DeviceTransaction
{    
public:
    typedef enum _TransactionType
    {
        Transaction_Invalid,
        Transaction_Read,
        Transaction_Write,
        Transaction_WriteRead,
        Transaction_BurstProg
    } TransactionType;

    DeviceTransaction();
    DeviceTransaction(TransactionType type, uint32_t id);

    QDateTime timeStarted() const;
    qint64 msElapsed() const;
    TransactionType type() const;

    QByteArray writeData() const;
    void setWriteData(const QByteArray& data);

    QByteArray readData() const;
    void setReadData(const QByteArray& data);

    QVariant userData() const;
    void setUserData(const QVariant& data);

    uint8_t address() const;
    void setAddress(uint8_t addr);

    BurstProgram program() const;
    void setBurstProgram(const BurstProgram& prog);

    uint32_t id() const;

private:
    QSharedDataPointer<DeviceTransactionData> d;
};

class DeviceTransactionData : public QSharedData
{
public:
    DeviceTransactionData();
    DeviceTransactionData(DeviceTransaction::TransactionType type, uint32_t id);

    BurstProgram prog;
    DeviceTransaction::TransactionType type;
    QDateTime time;
    QByteArray writeData, readData;
    QVariant userData;
    uint8_t address;
    uint32_t id;
};

typedef QSharedPointer<DeviceTransaction> DeviceTransactionPtr;

Q_DECLARE_METATYPE(DeviceTransaction);
Q_DECLARE_METATYPE(DeviceTransactionPtr);

#endif // DEVICETRANSACTION_H
