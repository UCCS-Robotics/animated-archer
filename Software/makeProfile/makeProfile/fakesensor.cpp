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
    emit sensorData(stamp, rand()%1500, rand()%1000, rand()%500);
}

void FakeSensor::run(){
    connect(this,SIGNAL(sensorData(QDateTime,quint16,quint16,quint16)),mainwindow,SLOT(recordSensor(QDateTime,quint16,quint16,quint16)));
    connect(mainwindow,SIGNAL(send_timer()),this,SLOT(update()));
    exec();
}
