#ifndef DEVICE_H
#define DEVICE_H

#include "burstprogram.h"
#include "devicetransaction.h"

#include <QObject>
#include <QByteArray>
#include <QVariant>
#include <stdint.h>

class DeviceConnection;

class Device : public QObject
{
    Q_OBJECT

public:
    explicit Device(QObject *parent = 0);
    ~Device();

    QString lastError() const;
    bool isConnected() const;

    DeviceConnection* connection() const;

    void sendWrite(uint8_t addr, const QByteArray& data,
        const QVariant& userData = QVariant());
    void sendWrite(uint8_t addr, const uint8_t *data, size_t sz,
        const QVariant& userData = QVariant());

    void sendRead(uint8_t addr, size_t sz,
        const QVariant& userData = QVariant());
    void sendProgram(const BurstProgram& prog,
        const QVariant& userData = QVariant());

signals:
    void startWrite(quint8 addr, const QByteArray& data,
        const QVariant& userData);
    void startRead(quint8 addr, quint64 sz,
        const QVariant& userData);
    void startProgram(const BurstProgram& prog,
        const QVariant& userData);

    void transactionStarted(const DeviceTransactionPtr& trans);
    void transactionComplete(const DeviceTransactionPtr& trans);
    void transactionFailed(const DeviceTransactionPtr& trans);
    void deviceError(const QString& msg);

    void burstResult(quint8 programID, quint32 timeStamp, const QByteArray& data);

private slots:
    void connected();
    void disconnected();
    void error(const QString& msg);

private:
    bool mConnected;
    QString mLastError;
    DeviceConnection *mConnection;
};

#endif // DEVICE_H
