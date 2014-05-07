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
#include "sensorthread.h"
#include "fakesensor.h"
#include "ads1015.h"

class MainWindow;

class sensors : public QObject
{
    Q_OBJECT
public:
    explicit sensors(MainWindow*,QObject *parent = 0);
    void stop_all_sensors();
    void setup_ultra_sonic();
    void setup_lsm9ds0();   //9 DOF IMU
    void setup_ls20031();   //GPS
    void setup_mpl3115a2(); //altimiter
    void setup_infrared();
    void setup_sudo_sensor();
    uchar get_sensor() const { return sensorType;}
    void set_sensor(uchar sensor_type){ sensorType = sensor_type; }
    FakeSensor *get_sudo_sensor() const { return fakesensor; }
    ADS1015 *get_ads1015() const { return adcsensor; }
    SensorThread *get_light_sensor() const { return lightsensor; }


    ~sensors();

signals:

public slots:

private:
    MainWindow *mainwindow;

    SensorThread *lightsensor;
    ADS1015 *adcsensor;
    FakeSensor *fakesensor;
    quint32 usedDataGraphs;
    uchar sensorType;

public:


};

#endif // SENSORS_H
