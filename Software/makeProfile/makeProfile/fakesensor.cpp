#include "fakesensor.h"
#include <stdlib.h>
#include "mainwindow.h"

FakeSensor::FakeSensor(MainWindow *mainwindowin,QObject *parent) :
    QThread(parent)
{
    mainwindow = mainwindowin;
}

void FakeSensor::update(){
    emit fakeSensorOutput(rand()%1000);
}

void FakeSensor::run(){
    connect(this,SIGNAL(fakeSensorOutput(quint16)),mainwindow,SLOT(processLightSensorData(quint16)));
    connect(mainwindow,SIGNAL(send_timer()),this,SLOT(update()));
    exec();
}
