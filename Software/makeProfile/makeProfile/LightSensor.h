#ifndef __LightSensor_h__
#define __LightSensor_h__

#include "device.h"

#include <QtCore/QObject>
#include <QtCore/QDateTime>

#include <stdint.h>

class QTextEdit;

class LightSensor : public QObject
{
	Q_OBJECT

public:
    LightSensor(QObject *parent = 0);

private slots:
    void connected();
    void disconnected();
    void transactionComplete(const DeviceTransactionPtr& trans);
    void burstResult(quint8 programID, quint32 timeStamp, const QByteArray& data);

public slots:
    void program(quint16);

signals:
    void sensorData(const QDateTime &stamp, const QVector<qint32>& data);

private:
    uint32_t mFirstStamp;

    Device mDevice;
    QDateTime mConnectTime;
};

#endif // __Sensor_h__
