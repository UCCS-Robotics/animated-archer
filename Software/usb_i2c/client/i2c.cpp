#include "i2c.h"

#include <QtCore/QFile>

#define I2C_CMD_READ  ('R')
#define I2C_CMD_WRITE ('W')

void i2cWrite(uint8_t addr, const uint8_t *data, uint8_t sz)
{
	uint8_t cmd = I2C_CMD_WRITE;

	QFile tty("/dev/ttyACM0");
	tty.open(QIODevice::ReadWrite);
	tty.write((char*)&cmd, 1);
	tty.write((char*)&addr, 1);
	tty.write((char*)&sz, 1);
	tty.write((char*)data, sz);
	tty.close();
}

void i2cWriteSingle(uint8_t addr, uint8_t byte)
{
	i2cWrite(addr, &byte, 1);
}

void i2cRead(uint8_t addr, uint8_t *data, uint8_t sz)
{
	bool ok = false;
	uint8_t cmd = I2C_CMD_READ;

	QFile tty("/dev/ttyACM0");
	tty.open(QIODevice::ReadWrite);
	tty.write((char*)&cmd, 1);
	tty.write((char*)&addr, 1);

	while(sz--)
		*(data++) = QString::fromAscii(tty.readLine()).toUInt(&ok, 16);

	tty.close();
}

uint8_t i2cReadSingle(uint8_t addr)
{
	uint8_t byte;
	i2cRead(addr, &byte, 1);
	return byte;
}
