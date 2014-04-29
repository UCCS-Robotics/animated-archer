#include "fakesensor.h"
#include <stdlib.h>
#include "mainwindow.h"

FakeSensor::FakeSensor(MainWindow *mainwindowin,QObject *parent) :
    QThread(parent)
{
    mainwindow = mainwindowin;
}

void FakeSensor::update(){
    // Calculate the absolute time of the event.
    QDateTime stamp = QDateTime::currentDateTime();

    // Notify the graph about the new sensor data.
    emit sensorData(stamp, rand()%1000);
}

void FakeSensor::run(){
    connect(this,SIGNAL(sensorData(QDateTime,quint16)),mainwindow,SLOT(processLightSensorData(QDateTime,quint16)));
    connect(mainwindow,SIGNAL(send_timer()),this,SLOT(update()));
    exec();
}
