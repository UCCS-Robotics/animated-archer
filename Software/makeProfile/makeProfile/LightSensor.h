#ifndef __LightSensor_h__
#define __LightSensor_h__

#include "device.h"

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include <stdint.h>

class QTextEdit;

class LightSensor : public QObject
{
	Q_OBJECT

public:
    LightSensor(QObject *parent = 0);

private slots:
	void updateSensor();
    void transactionComplete(const DeviceTransactionPtr& trans);

signals:
//    void sendStringMain(const QString &);
    void sentLightSensorData(quint16);

private:
	void enable();
	void disable();

    void read16(uint8_t reg, const QString& userData);
	void write8(uint8_t reg, uint8_t value);

    uint16_t mIR, mFull;
    bool mDidInit;

    Device mDevice;
	QTextEdit *mEditor;
	QTimer mTimer;
};

#endif // __Sensor_h__
