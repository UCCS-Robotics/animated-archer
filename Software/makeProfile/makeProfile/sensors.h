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
#define NINEDOF 10
#define FAKE 99

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

    //////////////////////////////////////////////////

    void select_ultra_sonic();
    void select_lsm9ds0();   //9 DOF IMU
    void select_ls20031();   //GPS
    void select_mpl3115a2(); //altimiter
    void select_infrared();
    void select_sudo_sensor();
    void select_light_sensor();

    //////////////////////////////////////////////////

    void clear_data();
    void stop_all_sensors();
    void switch_sensor();

    //////////////////////////////////////////////////

    uchar get_sensor_type() const { return sensorType;}
    uchar get_used_graphs() const { return usedGraphs; }
    quint32 get_sample_period() const { return samplePeriod; }
    const QVector <QVector <qint32> > &get_data_raw() const { return globalRawData; }
    const QVector <QVector <float> > &get_data() const { return globalData; }

    FakeSensor *get_sudo_sensor() const { return fakesensor; }
    ADS1015 *get_ads1015() const { return adcsensor; }
    LightSensor *get_light_sensor() const { return lightsensor; }


    //////////////////////////////////////////////////

    void set_sensor_type(const uchar sensor_type);
    void set_used_graphs(const uchar num_graphs){ if(num_graphs < 9) usedGraphs = num_graphs; }
    void set_sample_period(const quint32 sample){ samplePeriod = sample; }
    void set_raw_data(const QVector <QVector <qint32> > &data){ globalRawData = data; }
    void set_data(const QVector <QVector <float> > &data){ globalData = data; }

    //////////////////////////////////////////////////

signals:
    void raw_data_ready(const QVector < QVector<qint32> > &data);

public slots:
    void recordSensor(const QDateTime &time_cast, const QVector<qint32> &data);

private:
    MainWindow *mainwindow;

    LightSensor *lightsensor;
    ADS1015 *adcsensor;
    FakeSensor *fakesensor;
    Device *usb;

    uchar sensorType, usedGraphs;
    quint32 samplePeriod;
    quint64 elapsedTime;
    QVector <QVector <qint32> > globalRawData;
    QVector <QVector <float> > globalData;
    QDateTime currentTime;
    QTimer *timer;

public:


};

#endif // SENSORS_H
