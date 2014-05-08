#include "sensors.h"
#include "mainwindow.h"
#include <QDateTime>

sensors::sensors(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    usb = new Device;
    connect(usb, SIGNAL(deviceError(QString)),
            mainwindow, SLOT(on_deviceError(QString)));
}


sensors::~sensors(){
    stop_all_sensors();
}

void sensors::select_infrared(){
    stop_all_sensors();
    set_used_graphs(1); //Number of IR connected
    set_sensor_type(INFRARED);
}

void sensors::select_ls20031(){
    stop_all_sensors();
    set_used_graphs(1); //Number of GPS connected
    set_sensor_type(GPS);
}

void sensors::select_lsm9ds0(){
    stop_all_sensors();
    set_used_graphs(9); //Number of 9 DOF's connected
    set_sensor_type(NINEDOF);
}

void sensors::select_mpl3115a2(){
    stop_all_sensors();
    set_used_graphs(1); //Number of altimiters connected
    set_sensor_type(ALTIMITER);
}

void sensors::select_sudo_sensor(){
    stop_all_sensors();
    fakesensor = new FakeSensor(mainwindow);
    set_used_graphs(9); //Number of fake sensors connected
    set_sensor_type(FAKE);
    connect(fakesensor, SIGNAL(sensorData(QVector<float>)),
            this,SLOT(recordSensor(QVector<float>)));
}

void sensors::select_ultra_sonic(){
    stop_all_sensors();
    adcsensor = new ADS1015;
    set_used_graphs(4); //Number of US connected
    set_sensor_type(ULTRASONIC);
    connect(adcsensor, SIGNAL(sensorData(QVector<float>)),
            this, SLOT(recordSensor(QVector<float>)));
}

void sensors::select_light_sensor(){
    stop_all_sensors();
    lightsensor = new LightSensor;
    set_used_graphs(1); //Number of light connected
    set_sensor_type(LIGHT);
    connect(lightsensor, SIGNAL(sensorData(QVector<float>)),
            this, SLOT(recordSensor(QVector<float>)));
}

void sensors::recordSensor(const QVector<float> &data){ // Format: [stamp.ms,graph0,graph1,...]
    globalRawData.push_back(data);
    globalRawData[globalRawData.size()-1][0] += data.at(0) - currentTime.toMSecsSinceEpoch();
    currentTime = QDateTime::currentDateTime();
}

void sensors::stop_all_sensors(){
    delete lightsensor;
    delete adcsensor;
    fakesensor->exit();
    while(fakesensor->isRunning());
    delete fakesensor;
}

void sensors::clear_data(){
    globalRawData.resize(0);
    globalData.resize(0);
}

void sensors::set_sensor_type(uchar sensor_type){
    sensorType = sensor_type;
    clear_data();
}
