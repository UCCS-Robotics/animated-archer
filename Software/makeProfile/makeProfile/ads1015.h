#ifndef ADS1015_H
#define ADS1015_H

#include "device.h"

#include <QObject>
#include <QDateTime>

#include <stdint.h>

class ADS1015 : public QObject
{
    Q_OBJECT
public:
    explicit ADS1015(QObject *parent = 0);

private slots:
    void connected();
    void disconnected();
    void transactionComplete(const DeviceTransactionPtr& trans);
    void transactionFailed(const DeviceTransactionPtr& trans);
    void burstResult(quint8 programID, quint32 timeStamp, const QByteArray& data);

signals:
    void sensorData(const QDateTime &,const QVector<qint32>& data);  // format: [stamp.ms,value,channel]

public slots:
    void program(qint16 delay_ms);

private:
    QByteArray writeRegister(uint8_t reg, uint16_t value);

    uint32_t mFirstStamp;

    Device mDevice;
    QDateTime mConnectTime;
};

#endif // ADS1015_H
