#include "sensorthread.h"
#include "mainwindow.h"

SensorThread::SensorThread(MainWindow *mainwindowin,QObject *parent) :
    QThread(parent)
{
    mainwindow = mainwindowin;
}

void SensorThread::run(){
    lightsensor = new LightSensor;
    timer = new QTimer;
    timer->start(1000);
    connect(lightsensor,SIGNAL(sentLightSensorData(quint16)),mainwindow,SLOT(processLightSensorData(quint16)));
    connect(timer, SIGNAL(timeout()), lightsensor, SLOT(updateSensor()));
    exec();
}
