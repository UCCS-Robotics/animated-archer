#include "LightSensor.h"
#include "deviceconnection.h"

#include <iostream>

#define TSL2561_ADDR_FLOAT        (0x39)

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

LightSensor::LightSensor(QObject *p) : QObject(p), mFirstStamp(0)
{
    // Connect the driver signals.
    connect(&mDevice, SIGNAL(transactionComplete(DeviceTransactionPtr)),
        this, SLOT(transactionComplete(DeviceTransactionPtr)));
    connect(&mDevice, SIGNAL(burstResult(quint8, quint32, const QByteArray&)),
        this, SLOT(burstResult(quint8, quint32, const QByteArray&)));
    connect(mDevice.connection(), SIGNAL(connected()), this, SLOT(connected()));
    connect(mDevice.connection(), SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void LightSensor::connected()
{
    // Data for the commands that are about to be written.
    const uint8_t powerOnData[2] = {
        TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL,  // Register
        TSL2561_CONTROL_POWERON                          // Argument
    };
    const uint8_t configSensorData[2] = {
        TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING,   // Register
        TSL2561_INTEGRATIONTIME_101MS | TSL2561_GAIN_16X // Argument
    };

    // Turn on the sensor then set timing and gain.
    mDevice.sendWrite(TSL2561_ADDR_FLOAT, powerOnData, 2, "light");
    mDevice.sendWrite(TSL2561_ADDR_FLOAT, configSensorData, 2, "light");

    // Data for the burst program commands.
    const uint8_t reg1 = TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW;
    const uint8_t reg2 = TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW;

    // The burst program we are about to describe.
    BurstProgram prog;

    // First send the command to read the IR value.
    prog.addWrite(TSL2561_ADDR_FLOAT, QByteArray((char*)&reg1, 1));
    prog.addRead(TSL2561_ADDR_FLOAT, 2);

    // Next send the command to read the full value.
    prog.addWrite(TSL2561_ADDR_FLOAT, QByteArray((char*)&reg2, 1));
    prog.addRead(TSL2561_ADDR_FLOAT, 2);

    // Set the program ID and update interval.
    prog.setProgramID(0);
    prog.setRunInterval(25); // 25ms or 40Hz

    // Make sure the program is valid.
    Q_ASSERT(prog.isValid());

    // Send the program to the device.
    mDevice.startProgram(prog, "light:prog");
}

void LightSensor::burstResult(quint8 programID, quint32 timeStamp, const QByteArray& data)
{
    // If the burst result is not from this program, ignore the result.
    if(programID != 0 || data.size() != 4)
        return;

    // Convert the results to an array of 16-bit integers.
    const uint16_t *values = (uint16_t*)data.constData();

    // Calculate the visible light from: visible = IR - full
    uint16_t visible = values[1] - values[0];

    // Calculate a time offset for the first burst value.
    if(mFirstStamp == 0)
    {
        // Set the connection time.
        mConnectTime = QDateTime::currentDateTime();
        mFirstStamp = timeStamp;
    }

    // Calculate the absolute time of the event.
    QDateTime stamp = mConnectTime.addMSecs(timeStamp - mFirstStamp);

    // Notify the graph about the new sensor data.
    emit sensorData(stamp, visible);
}

void LightSensor::transactionComplete(const DeviceTransactionPtr& trans)
{
    // If the transaction was the burst program, make sure it programmed right.
    if(trans->type() == DeviceTransaction::Transaction_BurstProg && trans->userData().toString() == "light:prog")
    {
        // Get the status code for the program.
        uint8_t statusCode = *trans->readData().constData();

        // Print an error to the console if it failed to program.
        if(statusCode != 0)
            std::cerr << "Light sensor burst program failed with status code: " << (int)statusCode << std::endl;
    }
}

void LightSensor::disconnected()
{
    // Clear the first time stamp.
    mFirstStamp = 0;
}
