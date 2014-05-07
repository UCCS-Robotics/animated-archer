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
