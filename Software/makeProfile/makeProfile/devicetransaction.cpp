#include "devicetransaction.h"

DeviceTransactionData::DeviceTransactionData() : type(DeviceTransaction::Transaction_Invalid), id(0)
{
    qRegisterMetaType<DeviceTransaction>("DeviceTransaction");
    qRegisterMetaType<DeviceTransactionPtr>("DeviceTransactionPtr");

    time = QDateTime::currentDateTime();
}

DeviceTransactionData::DeviceTransactionData(DeviceTransaction::TransactionType _type,
    uint32_t _id) : type(_type), id(_id)
{
    qRegisterMetaType<DeviceTransaction>("DeviceTransaction");
    qRegisterMetaType<DeviceTransactionPtr>("DeviceTransactionPtr");

    time = QDateTime::currentDateTime();
}

DeviceTransaction::DeviceTransaction() : d(new DeviceTransactionData)
{
    // nothing here
}

DeviceTransaction::DeviceTransaction(TransactionType type, uint32_t id) :
    d(new DeviceTransactionData(type, id))
{
    // nothing here
}

QDateTime DeviceTransaction::timeStarted() const
{
    return d->time;
}

qint64 DeviceTransaction::msElapsed() const
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch() -
        d->time.toMSecsSinceEpoch();
}

DeviceTransaction::TransactionType DeviceTransaction::type() const
{
    return d->type;
}

QByteArray DeviceTransaction::writeData() const
{
    return d->writeData;
}

void DeviceTransaction::setWriteData(const QByteArray& data)
{
    d->writeData = data;
}

QByteArray DeviceTransaction::readData() const
{
    return d->readData;
}

void DeviceTransaction::setReadData(const QByteArray& data)
{
    d->readData = data;
}

QVariant DeviceTransaction::userData() const
{
    return d->userData;
}

void DeviceTransaction::setUserData(const QVariant& data)
{
    d->userData = data;
}

uint8_t DeviceTransaction::address() const
{
    return d->address;
}

void DeviceTransaction::setAddress(uint8_t addr)
{
    d->address = addr;
}

uint32_t DeviceTransaction::id() const
{
    return d->id;
}
