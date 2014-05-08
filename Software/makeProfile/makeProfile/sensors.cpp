#include "sensors.h"
#include "mainwindow.h"
#include <QDateTime>

sensors::sensors(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    usb = new Device;
    timer = new QTimer(this);
    elapsedTime = 0;
    connect(usb, SIGNAL(deviceError(QString)),
            mainwindow, SLOT(on_deviceError(QString)));
}


sensors::~sensors(){
    stop_all_sensors();
}

void sensors::switch_sensor(){
    elapsedTime = 0;
    stop_all_sensors();
    currentTime = QDateTime::currentDateTime();
}

void sensors::select_infrared(){
    switch_sensor();
    set_used_graphs(1); //Number of IR connected
    set_sensor_type(INFRARED);
}

void sensors::select_ls20031(){
    switch_sensor();
    set_used_graphs(1); //Number of GPS connected
    set_sensor_type(GPS);
}

void sensors::select_lsm9ds0(){
    switch_sensor();
    set_used_graphs(9); //Number of 9 DOF's connected
    set_sensor_type(NINEDOF);
}

void sensors::select_mpl3115a2(){
    switch_sensor();
    set_used_graphs(1); //Number of altimiters connected
    set_sensor_type(ALTIMITER);
}

void sensors::select_sudo_sensor(){
    switch_sensor();
    fakesensor = new FakeSensor(mainwindow);
    set_used_graphs(9); //Number of fake sensors connected
    set_sensor_type(FAKE);
    connect(fakesensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
            this,SLOT(recordSensor(QDateTime,QVector<qint32>)));
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), fakesensor, SLOT(update()));
}

void sensors::select_ultra_sonic(){
    switch_sensor();
    adcsensor = new ADS1015;
    set_used_graphs(4); //Number of US connected
    set_sensor_type(ULTRASONIC);
    connect(adcsensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
            this, SLOT(recordSensor(QDateTime,QVector<qint32>)));
}

void sensors::select_light_sensor(){
    switch_sensor();
    lightsensor = new LightSensor;
    set_used_graphs(1); //Number of light connected
    set_sensor_type(LIGHT);
    connect(lightsensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
            this, SLOT(recordSensor(QDateTime,QVector<qint32>)));
}

void sensors::recordSensor(const QDateTime &time_cast, const QVector<qint32> &data){ // Format: [stamp.ms,graph0,graph1,...]
    elapsedTime += time_cast.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    globalRawData.push_back(QVector<qint32>() << elapsedTime << data);
    currentTime = QDateTime::currentDateTime();
    emit raw_data_ready(get_data_raw());
}

void sensors::stop_all_sensors(){
    if(timer->isActive())
        timer->stop();
    switch(get_sensor_type()){
    case LIGHT:
        delete lightsensor;
        break;
    case ULTRASONIC:
        delete adcsensor;
        break;
    case FAKE:
        if(fakesensor->isRunning())
            fakesensor->exit();
        while(fakesensor->isRunning());
        delete fakesensor;
        break;
    default:
        break;
    }
}

void sensors::clear_data(){
    globalRawData.resize(0);
    globalData.resize(0);
}

void sensors::set_sensor_type(uchar sensor_type){
    sensorType = sensor_type;
    clear_data();
}
