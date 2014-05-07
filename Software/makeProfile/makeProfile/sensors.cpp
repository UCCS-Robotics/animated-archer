#include "sensors.h"
#include "mainwindow.h"

sensors::sensors(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    lightsensor = new SensorThread(mainwindowin);
    adcsensor = new ADS1015;
    usb = new Device;
    connect(adcsensor, SIGNAL(sensorData(QDateTime,quint8,quint16)),
            mainwindow, SLOT(processADCData(QDateTime,quint8,quint16)));
    connect(usb, SIGNAL(deviceError(QString)),
            mainwindow, SLOT(on_deviceError(QString)));
    fakesensor = new FakeSensor(mainwindowin);
}


sensors::~sensors(){
    lightsensor->quit();    //Stop thread
    while(lightsensor->isRunning());    //Wait for thread to stop
    delete lightsensor;
}

void sensors::select_infrared(){
    set_used_graphs(1); //Number of IR connected
    set_sensor_type(INFRARED);
}

void sensors::select_ls20031(){
    set_used_graphs(1); //Number of GPS connected
    set_sensor_type(GPS);
}

void sensors::select_lsm9ds0(){
    set_used_graphs(9); //Number of 9 DOF's connected
    set_sensor_type(NINEDOF);
}

void sensors::select_mpl3115a2(){
    set_used_graphs(1); //Number of altimiters connected
    set_sensor_type(ALTIMITER);
}

void sensors::select_sudo_sensor(){
    set_used_graphs(9); //Number of fake sensors connected
    set_sensor_type(FAKE);
}

void sensors::select_ultra_sonic(){
    set_used_graphs(4); //Number of US connected
    set_sensor_type(ULTRASONIC);
}

void sensors::select_light_sensor(){
    set_used_graphs(1); //Number of light connected
    set_sensor_type(LIGHT);
}

void sensors::stop_all_sensors(){
    if(lightsensor->isRunning())
        lightsensor->quit();
    if(fakesensor->isRunning())
        fakesensor->quit();
}

void sensors::clear_data(){
    globalRawData.resize(0);
    globalData.resize(0);
}

void sensors::set_sensor_type(uchar sensor_type){
    sensorType = sensor_type;
    clear_data();
}
