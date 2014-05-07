#include "sensors.h"
#include "mainwindow.h"

sensors::sensors(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    lightsensor = new SensorThread(mainwindowin);
    adcsensor = new ADS1015;
    connect(adcsensor, SIGNAL(sensorData(QDateTime,quint8,quint16)),
            mainwindow, SLOT(processADCData(QDateTime,quint8,quint16)));
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
