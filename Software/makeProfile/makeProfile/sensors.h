#ifndef SENSORS_H
#define SENSORS_H

#define ADC 1
#define ACCELEROMETER 2
#define GYROSCOPE 3
#define THERMOMETER 4
#define GPS 5
#define COMPASS 6
#define ALTIMITER 7
#define INFRARED 8
#define LIGHT 9
#define NINEDOF 10
#define FAKE 99
#define NONE 100

#include <QObject>
#include <QVector>
#include <QTimer>
#include "LightSensor.h"
#include "fakesensor.h"
#include "ads1015.h"
#include "device.h"


class MainWindow;

class sensors : public QObject
{
    Q_OBJECT
public:
    explicit sensors(MainWindow*,QObject *parent = 0);
    ~sensors();

    /********************************************************************
     * Sensor Select                                                    *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::select_ultra_sonic
    /// Set configure and reinitialize device to read the ADC (Ultra
    /// sonic sensors)
    /////////////////////////////////////////////////////////////////////
    void select_ads1015();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::select_infrared
    /// Set configure and reinitialize device to read the IR sensor
    /////////////////////////////////////////////////////////////////////
    void select_infrared();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::select_light_sensor
    /// Set configure and reinitialize device to read the light sensor
    /////////////////////////////////////////////////////////////////////
    void select_light_sensor();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::select_ls20031
    /// Set configure and reinitialize device to read the GPS
    /////////////////////////////////////////////////////////////////////
    void select_ls20031();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::select_lsm9ds0
    /// Set configure and reinitialize device to read the 9 Degrees
    /// of Freedom Inertial Measurement Unit
    /////////////////////////////////////////////////////////////////////
    void select_lsm9ds0();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::select_mpl3115a2
    /// Set configure and reinitialize device to read the altimiter
    /////////////////////////////////////////////////////////////////////
    void select_mpl3115a2();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::select_sudo_sensor
    /// Set configure and reinitialize device to read the pseudo
    /// sensor
    /////////////////////////////////////////////////////////////////////
    void select_sudo_sensor();

    /********************************************************************
     * Helper Methods                                                   *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief convert_data
    /// \param data
    /// \return convertedData
    /// Convert the existing raw data, only when conversion flag is set
    /////////////////////////////////////////////////////////////////////
    void convert_data();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::clear_data
    /// Clear data, primarily used after switching sensors
    /////////////////////////////////////////////////////////////////////
    void clear_data();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::stop_all_sensors
    /// If sensor is active, disable it so that the next sensor can
    /// initialize.
    /////////////////////////////////////////////////////////////////////
    void stop_all_sensors();

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::switch_sensor
    /// Reinitialize data and config variables for new sensor
    /////////////////////////////////////////////////////////////////////
    void switch_sensor();

    /********************************************************************
     * Getters                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief get_ads1015
    /// \return adcsensor
    /// Returns ADC device pointer
    /////////////////////////////////////////////////////////////////////
    ADS1015 *get_ads1015() const { return adcsensor; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_conversion_flag
    /// \return
    /// Returns the status of the conversion flag
    /////////////////////////////////////////////////////////////////////
    bool get_conversion_flag() const { return convertDataFlag; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_data
    /// \return globalData
    /// Returns the converted data received from the devices
    /////////////////////////////////////////////////////////////////////
    const QVector <QVector <float> > &get_data() const { return globalData; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_data_raw
    /// \return globalRawData
    /// Returns the raw data received from the devices
    /////////////////////////////////////////////////////////////////////
    const QVector <QVector <qint32> > &get_data_raw() const { return globalRawData; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_light_sensor
    /// \return lightsensor
    /// Returns the light sensor device pointer
    /////////////////////////////////////////////////////////////////////
    LightSensor *get_light_sensor() const { return lightsensor; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_number_samples
    /// \return
    /// Returns the number of samples that the object will record
    /////////////////////////////////////////////////////////////////////
    qint32 get_number_samples() const { return numSamples; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_sample_period
    /// \return samplePeriod
    /// Returns the current sample period for the devices
    /////////////////////////////////////////////////////////////////////
    quint32 get_sample_period() const { return samplePeriod; }

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::get_sensor_type
    /// \return sensorType
    /// Used to get the sensor that is currently in use
    /////////////////////////////////////////////////////////////////////
    uchar get_sensor_type() const { return sensorType;}

    /////////////////////////////////////////////////////////////////////
    /// \brief get_sudo_sensor
    /// \return fakesensor
    /// Returns the fake sensor device pointer
    /////////////////////////////////////////////////////////////////////
    FakeSensor *get_sudo_sensor() const { return fakesensor; }

    /////////////////////////////////////////////////////////////////////
    /// \brief get_used_graphs
    /// \return usedGraphs
    /// Returns the number of graphs used
    /////////////////////////////////////////////////////////////////////
    uchar get_used_graphs() const { return usedGraphs; }    

    /********************************************************************
     * Setters                                                          *
     *******************************************************************/

    /////////////////////////////////////////////////////////////////////
    /// \brief set_conversion_flag
    /// \param convert
    /// Sets the conversion flag for the sensors
    /////////////////////////////////////////////////////////////////////
    void set_conversion_flag(bool convert){ convertDataFlag = convert; }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_number_samples
    /// \param num_samples
    /// Sets the number of samples to take, if value is 0, free run
    /////////////////////////////////////////////////////////////////////
    void set_number_samples(qint32 num_samples){
        numSamples = num_samples; clear_data();}

    /////////////////////////////////////////////////////////////////////
    /// \brief set_sample_period
    /// \param sample
    /// Sets the sample period for the devices
    /////////////////////////////////////////////////////////////////////
    void set_sample_period(const quint32 sample){ samplePeriod = sample; }

signals:
    /////////////////////////////////////////////////////////////////////
    /// \brief device_error
    /// Emitted when the device encounters an error
    /////////////////////////////////////////////////////////////////////
    void device_error(QString);

    /////////////////////////////////////////////////////////////////////
    /// \brief raw_data_ready
    /// Emitted when the raw data is ready for processing
    /////////////////////////////////////////////////////////////////////
    void raw_data_ready(const QVector < QVector<qint32> > &);

public slots:
    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::on_device_error
    /// \param error
    /// Slot used to relay error out of the object
    /////////////////////////////////////////////////////////////////////
    void on_device_error(QString error);

    /////////////////////////////////////////////////////////////////////
    /// \brief sensors::recordSensor
    /// \param time_cast
    /// \param data
    /// Slot to receive live raw data from the device. Calculates elapsed
    /// time and saves the time and data to globalRawData.
    /////////////////////////////////////////////////////////////////////
    void on_record_sensor(const QDateTime &time_cast, const QVector<qint32> &data);

private:
    MainWindow *mainwindow;

    LightSensor *lightsensor;   // Light sensor device
    ADS1015 *adcsensor; // ADC sensor device
    FakeSensor *fakesensor; // Fake sensor device
    Device *usb;    // Connection to teensy

    uchar sensorType, usedGraphs;   // sensorType: sensor in use,
                                    // usedGraphs: number of individual data sets
    quint32 samplePeriod;   // Determines the sample period for the devices
    quint64 elapsedTime;    // Amount of time passed since data capture
    QVector <QVector <qint32> > globalRawData;  // Raw data from sensors
    QVector <QVector <float> > globalData;  // Converted data from sensors
    QDateTime currentTime;  // ... Self explanitory? It's for the timestamps
    QTimer *timer;  // Used to trigger the fake sensor
    bool convertDataFlag;   // Flag to run conversion on incoming data
    qint32 numSamples;

private:
    /////////////////////////////////////////////////////////////////////
    /// \brief convert_immediate_data
    /// \param data
    /// \return convertedData
    /// Convert the incoming raw data, only when conversion flag is set
    /////////////////////////////////////////////////////////////////////
    QVector<float> convert_immediate_data(QVector<qint32> data);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_data
    /// \param data
    /// Sets the converted data from the sensor, just in case
    /////////////////////////////////////////////////////////////////////
    void set_data(const QVector <QVector <float> > &data){ globalData = data; }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_raw_data
    /// \param data
    /// Sets the raw data from the sensor, just in case it's ever needed
    /////////////////////////////////////////////////////////////////////
    void set_raw_data(const QVector <QVector <qint32> > &data){ globalRawData = data; }

    /////////////////////////////////////////////////////////////////////
    /// \brief set_sensor_type
    /// \param sensor_type
    /// Sets the sensor type
    /////////////////////////////////////////////////////////////////////
    void set_sensor_type(const uchar sensor_type);

    /////////////////////////////////////////////////////////////////////
    /// \brief set_used_graphs
    /// \param num_graphs
    /// Sets the number of used graphs
    /////////////////////////////////////////////////////////////////////
    void set_used_graphs(const uchar num_graphs){ if(num_graphs < 9) usedGraphs = num_graphs; }
};

#endif // SENSORS_H
