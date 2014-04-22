#include "LightSensor.h"
#include "i2c.h"

#include <unistd.h>

#define	I2C_0  (0x40) // I2C Remote 8-bit I/O
#define	I2C_1  (0x42) // Expander addresses
#define	I2C_2  (0x44) // PCF8574
#define	I2C_3  (0x46)
#define	I2C_4  (0x48)
#define	I2C_5  (0x4A)
#define	I2C_6  (0x4C)
#define	I2C_7  (0x4E)
#define	I2C_0A (0x70) // I2C Remote 8-bit I/O
#define	I2C_1A (0x72) // Expander addresses
#define	I2C_2A (0x74) // PCF8574A
#define	I2C_3A (0x76)
#define	I2C_4A (0x78)
#define	I2C_5A (0x7A)
#define	I2C_6A (0x7C)
#define	I2C_7A (0x7E)

#define SWITCH    (I2C_0)
#define SEG_LEFT  (I2C_3)
#define SEG_RIGHT (I2C_4)

#define TSL2561_ADDR_FLOAT 0x39

#define TSL2561_COMMAND_BIT       (0x80)    // Must be 1
#define TSL2561_CLEAR_BIT         (0x40)    // Clears any pending interrupt (write 1 to clear)
#define TSL2561_WORD_BIT          (0x20)    // 1 = read/write word (rather than byte)
#define TSL2561_BLOCK_BIT         (0x10)    // 1 = using block read/write

#define TSL2561_CONTROL_POWERON   (0x03)
#define TSL2561_CONTROL_POWEROFF  (0x00)

enum
{
	TSL2561_REGISTER_CONTROL          = 0x00,
	TSL2561_REGISTER_TIMING           = 0x01,
	TSL2561_REGISTER_THRESHHOLDL_LOW  = 0x02,
	TSL2561_REGISTER_THRESHHOLDL_HIGH = 0x03,
	TSL2561_REGISTER_THRESHHOLDH_LOW  = 0x04,
	TSL2561_REGISTER_THRESHHOLDH_HIGH = 0x05,
	TSL2561_REGISTER_INTERRUPT        = 0x06,
	TSL2561_REGISTER_CRC              = 0x08,
	TSL2561_REGISTER_ID               = 0x0A,
	TSL2561_REGISTER_CHAN0_LOW        = 0x0C,
	TSL2561_REGISTER_CHAN0_HIGH       = 0x0D,
	TSL2561_REGISTER_CHAN1_LOW        = 0x0E,
	TSL2561_REGISTER_CHAN1_HIGH       = 0x0F
};

typedef enum
{
	TSL2561_INTEGRATIONTIME_13MS      = 0x00,    // 13.7ms
	TSL2561_INTEGRATIONTIME_101MS     = 0x01,    // 101ms
	TSL2561_INTEGRATIONTIME_402MS     = 0x02     // 402ms
}
tsl2561IntegrationTime_t;

typedef enum
{
	TSL2561_GAIN_0X                   = 0x00,    // No gain
	TSL2561_GAIN_16X                  = 0x10,    // 16x gain
}
tsl2561Gain_t;

LightSensor::LightSensor(QObject *p) : QObject(p)
{
    // Initialize the light LightSensor.
	i2cWriteSingle(TSL2561_ADDR_FLOAT, TSL2561_REGISTER_ID);

//	if(i2cReadSingle(TSL2561_ADDR_FLOAT) & 0x0A)
//        emit sendStringMain("Found TSL2561\n");
//	else
//        emit sendStringMain("Missing TSL2561\n");

	// Set timing and gain.
	enable();
	write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING,
		TSL2561_INTEGRATIONTIME_101MS | TSL2561_GAIN_16X);
	disable();
}

void LightSensor::updateSensor()
{
    enable();
//	usleep(1000*102);
	uint16_t ir = read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT |
		TSL2561_REGISTER_CHAN1_LOW);
	uint16_t full = read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT |
		TSL2561_REGISTER_CHAN0_LOW);
    disable();

	uint16_t visible = full - ir;

//    emit sendStringMain(tr("Light: %1\n").arg(visible));
    emit sentLightSensorData(visible);

	//i2cWriteSingle(SEG_LEFT >> 1, i2cReadSingle(SWITCH >> 1));
	//i2cWriteSingle(SEG_RIGHT >> 1, i2cReadSingle(SWITCH >> 1));
}

uint16_t LightSensor::read16(uint8_t reg)
{
	uint16_t x;
	i2cWriteSingle(TSL2561_ADDR_FLOAT, reg);
	i2cRead(TSL2561_ADDR_FLOAT, (uint8_t*)&x, 2);
	return x;
}

void LightSensor::write8(uint8_t reg, uint8_t value)
{
	uint8_t data[2] = { reg, value };
	i2cWrite(TSL2561_ADDR_FLOAT, data, 2);
}

void LightSensor::enable()
{
	write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL,
		TSL2561_CONTROL_POWERON);
}

void LightSensor::disable()
{
	write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL,
		TSL2561_CONTROL_POWEROFF);
}
