#ifndef SENSORS_H
#define SENSORS_H

#define ULTRASONIC 1
#define ACCELEROMETER 2
#define GYROSCOPE 3
#define THERMOMETER 4
#define GPS 5
#define COMPASS 6
#define ALTIMITER 7
#define INFRARED 8
#define LIGHT 9
#define FAKE 99

#include <QObject>
#include <QVector>
#include "sensorthread.h"
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

    //////////////////////////////////////////////////

    void setup_ultra_sonic();
    void setup_lsm9ds0();   //9 DOF IMU
    void setup_ls20031();   //GPS
    void setup_mpl3115a2(); //altimiter
    void setup_infrared();
    void setup_sudo_sensor();

    //////////////////////////////////////////////////

    void clear_data();
    void stop_all_sensors();

    //////////////////////////////////////////////////

    uchar get_sensor_type() const { return sensorType;}
    uchar get_used_graphs() const { return usedGraphs; }
    quint32 get_samplePeriod() const { return samplePeriod; }
    const QVector <quint32> &get_data_raw() const { return globalRawData; }
    const QVector <double> &get_data() const { return globalData; }

    FakeSensor *get_sudo_sensor() const { return fakesensor; }
    ADS1015 *get_ads1015() const { return adcsensor; }
    SensorThread *get_light_sensor() const { return lightsensor; }


    //////////////////////////////////////////////////

    void set_sensor_type(const uchar sensor_type);
    void set_used_graphs(const uchar num_graphs){ if(num_graphs < 8) usedGraphs = num_graphs; }
    void set_sample_period(const quint32 sample){ samplePeriod = sample; }
    void set_raw_data(const QVector <quint32> &data){ globalRawData = data; }

    //////////////////////////////////////////////////

signals:

public slots:

private:
    MainWindow *mainwindow;

    SensorThread *lightsensor;
    ADS1015 *adcsensor;
    FakeSensor *fakesensor;
    uchar sensorType, usedGraphs;
    quint32 samplePeriod;
    QVector <quint32> globalRawData;
    QVector <double> globalData;
    Device *usb;

public:


};

#endif // SENSORS_H
