#include "ads1015.h"
#include "deviceconnection.h"

#include <iostream>

#define ADS1015_ADDRESS (0x48)

#define ADS1015_REG_POINTER_CONVERT     (0x00)
#define ADS1015_REG_POINTER_CONFIG      (0x01)
#define ADS1015_REG_POINTER_LOWTHRESH   (0x02)
#define ADS1015_REG_POINTER_HITHRESH    (0x03)

#define ADS1015_REG_CONFIG_MUX_SINGLE_0 (0x4000)  // Single-ended AIN0
#define ADS1015_REG_CONFIG_MUX_SINGLE_1 (0x5000)  // Single-ended AIN1
#define ADS1015_REG_CONFIG_MUX_SINGLE_2 (0x6000)  // Single-ended AIN2
#define ADS1015_REG_CONFIG_MUX_SINGLE_3 (0x7000)  // Single-ended AIN3

#define ADS1015_REG_CONFIG_OS_SINGLE    (0x8000)  // Write: Set to start a single-conversion
#define ADS1015_REG_CONFIG_PGA_6_144V   (0x0000)  // +/-6.144V range = Gain 2/3
#define ADS1015_REG_CONFIG_PGA_4_096V   (0x0200)  // +/-4.096V range = Gain 1
#define ADS1015_REG_CONFIG_MODE_SINGLE  (0x0100)
#define ADS1015_REG_CONFIG_DR_3300SPS   (0x00C0)  // 3300 samples per second
#define ADS1015_REG_CONFIG_CMODE_TRAD   (0x0000)  // Traditional comparator with hysteresis (default)
#define ADS1015_REG_CONFIG_CPOL_ACTVLOW (0x0000)  // ALERT/RDY pin is low when active (default)
#define ADS1015_REG_CONFIG_CLAT_NONLAT  (0x0000)  // Non-latching comparator (default)
#define ADS1015_REG_CONFIG_CQUE_NONE    (0x0003)  // Disable the comparator and put ALERT/RDY in high state (default)

ADS1015::ADS1015(QObject *parent) :
    QObject(parent), mFirstStamp(0)
{
    // Connect the driver signals.
    connect(&mDevice, SIGNAL(transactionComplete(DeviceTransactionPtr)),
        this, SLOT(transactionComplete(DeviceTransactionPtr)));
    connect(&mDevice, SIGNAL(transactionFailed(DeviceTransactionPtr)),
        this, SLOT(transactionFailed(DeviceTransactionPtr)));
    connect(&mDevice, SIGNAL(burstResult(quint8, quint32, const QByteArray&)),
        this, SLOT(burstResult(quint8, quint32, const QByteArray&)));
    connect(mDevice.connection(), SIGNAL(connected()), this, SLOT(connected()));
    connect(mDevice.connection(), SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ADS1015::connected()
{
    program(500);
}

void ADS1015::disconnected()
{
    //
}

void ADS1015::transactionComplete(const DeviceTransactionPtr& trans)
{
    // If the transaction was the burst program, make sure it programmed right.
    if(trans->type() == DeviceTransaction::Transaction_BurstProg && trans->userData().toString() == "adc:prog0")
    {
        // Get the status code for the program.
        uint8_t statusCode = *trans->readData().constData();

        // Print an error to the console if it failed to program.
        if(statusCode != 0)
            std::cerr << "ADC burst program failed with status code: " << (int)statusCode << std::endl;
        else
            std::cerr << "ADC burst program OK." << std::endl;
    }

    // If the transaction was the burst program, make sure it programmed right.
    if(trans->type() == DeviceTransaction::Transaction_BurstProg && trans->userData().toString() == "adc:prog1")
    {
        // Get the status code for the program.
        uint8_t statusCode = *trans->readData().constData();

        // Print an error to the console if it failed to program.
        if(statusCode != 0)
            std::cerr << "ADC burst program failed with status code: " << (int)statusCode << std::endl;
        else
            std::cerr << "ADC burst program OK." << std::endl;
    }
}

void ADS1015::transactionFailed(const DeviceTransactionPtr& trans)
{
    // If the transaction was the burst program, make sure it programmed right.
    if(trans->type() == DeviceTransaction::Transaction_BurstProg && trans->userData().toString() == "adc:prog0")
        std::cerr << "ADC burst program failed." << std::endl;

    // If the transaction was the burst program, make sure it programmed right.
    if(trans->type() == DeviceTransaction::Transaction_BurstProg && trans->userData().toString() == "adc:prog1")
        std::cerr << "ADC burst program failed." << std::endl;
}

void ADS1015::burstResult(quint8 programID, quint32 timeStamp, const QByteArray& data)
{
    //std::cout << "Burst Result: " << (int)programID << " | Size: " << data.size() << std::endl;
    // If the burst result is not from this program, ignore the result.
    if((programID != 1 && programID != 2) || data.size() != 4)
        return;

    // Convert the results to an array of 16-bit integers.
    const uint16_t *values = (uint16_t*)data.constData();

    // Calculate a time offset for the first burst value.
    if(mFirstStamp == 0)
    {
        // Set the connection time.
        mConnectTime = QDateTime::currentDateTime();
        mFirstStamp = timeStamp;
    }

    // Calculate the absolute time of the event.
    QDateTime stamp = mConnectTime.addMSecs(timeStamp - mFirstStamp);

    uint8_t offset = (programID - 1) * 2;

    // Notify the graph about the new sensor data.
    for(int i = 0; i < 2; i++)
    {
        uint16_t val = values[i];
        val = (val >> 8) | (val << 8);
        val >>= 4;
        if((i + offset) == 0)
        {
            std::cout << "Channel " << (i + offset) << ": " << val << std::endl;
            emit sensorData(stamp, i + offset, val);
        }
    }
}

QByteArray ADS1015::writeRegister(uint8_t reg, uint16_t value)
{
    uint8_t data[3] = { reg, (uint8_t)(value >> 8), (uint8_t)(value & 0xFF) };

    return QByteArray((char*)data, 3);
}

void ADS1015::program(qint16 delay_ms)
{
    // The burst program we are about to describe.
    BurstProgram prog;

    // Register for reading the sample
    uint8_t reg = ADS1015_REG_POINTER_CONVERT;

    // Default config values for the ADC.
    uint16_t config = ADS1015_REG_CONFIG_OS_SINGLE |
        /*ADS1015_REG_CONFIG_PGA_4_096V |*/
        ADS1015_REG_CONFIG_PGA_6_144V |
        ADS1015_REG_CONFIG_MODE_SINGLE |
        ADS1015_REG_CONFIG_DR_3300SPS |
        ADS1015_REG_CONFIG_CMODE_TRAD |
        ADS1015_REG_CONFIG_CPOL_ACTVLOW |
        ADS1015_REG_CONFIG_CLAT_NONLAT |
        ADS1015_REG_CONFIG_CQUE_NONE;

    //
    // Program sqeuence (config, delay, sample) for each channel.
    //

    // Channel 0
    prog.addWrite(ADS1015_ADDRESS, writeRegister(ADS1015_REG_POINTER_CONFIG,
        ADS1015_REG_CONFIG_MUX_SINGLE_0 | config));
    prog.addDelayUS(2000); // ~303us at 3.3kSPS
    prog.addWrite(ADS1015_ADDRESS, &reg, 1);
    prog.addRead(ADS1015_ADDRESS, 2);

    // Channel 1
    prog.addWrite(ADS1015_ADDRESS, writeRegister(ADS1015_REG_POINTER_CONFIG,
        ADS1015_REG_CONFIG_MUX_SINGLE_1 | config));
    prog.addDelayUS(310); // ~303us at 3.3kSPS
    prog.addWrite(ADS1015_ADDRESS, &reg, 1);
    prog.addRead(ADS1015_ADDRESS, 2);

    // Set the program ID and update interval.
    prog.setProgramID(1);
    prog.setRunInterval(delay_ms);

    // Make sure the program is valid.
    Q_ASSERT(prog.isValid());

    // Send the program to the device.
    mDevice.startProgram(prog, "adc:prog0");

    // The burst program we are about to describe.
    BurstProgram prog2;

    // Channel 2
    prog2.addWrite(ADS1015_ADDRESS, writeRegister(ADS1015_REG_POINTER_CONFIG,
        ADS1015_REG_CONFIG_MUX_SINGLE_2 | config));
    prog2.addDelayUS(310); // ~303us at 3.3kSPS
    prog2.addWrite(ADS1015_ADDRESS, &reg, 1);
    prog2.addRead(ADS1015_ADDRESS, 2);

    // Channel 3
    prog2.addWrite(ADS1015_ADDRESS, writeRegister(ADS1015_REG_POINTER_CONFIG,
        ADS1015_REG_CONFIG_MUX_SINGLE_3 | config));
    prog2.addDelayUS(310); // ~303us at 3.3kSPS
    prog2.addWrite(ADS1015_ADDRESS, &reg, 1);
    prog2.addRead(ADS1015_ADDRESS, 2);

    // Set the program ID and update interval.
    prog2.setProgramID(2);
    prog2.setRunInterval(delay_ms);

    // Make sure the program is valid.
    Q_ASSERT(prog2.isValid());

    // Send the program to the device.
    mDevice.startProgram(prog2, "adc:prog1");
}
