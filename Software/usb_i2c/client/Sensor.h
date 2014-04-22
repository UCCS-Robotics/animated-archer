#ifndef __Sensor_h__
#define __Sensor_h__

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include <stdint.h>

class QTextEdit;

class Sensor : public QObject
{
	Q_OBJECT

public:
	Sensor(QObject *parent = 0);

private slots:
	void updateSensor();

private:
	void enable();
	void disable();

	uint16_t read16(uint8_t reg);
	void write8(uint8_t reg, uint8_t value);

	QTextEdit *mEditor;
	QTimer mTimer;
};

#endif // __Sensor_h__
