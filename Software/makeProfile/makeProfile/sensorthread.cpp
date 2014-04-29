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
    timer->start(500);
    connect(lightsensor,SIGNAL(sensorData(const QDateTime&, quint16)),mainwindow,SLOT(processLightSensorData(const QDateTime&, quint16)));
    //connect(timer, SIGNAL(timeout()), lightsensor, SLOT(updateSensor()));
    //connect(mainwindow,SIGNAL(send_timer()),lightsensor,SLOT(updateSensor()));
    exec();
}

void SensorThread::on_pauseResume(bool pauseResume){
    if(pauseResume){
        if(!timer->isActive()){
            timer->start(500);
        }
    } else {
        if(timer->isActive()){
            timer->stop();
        }
    }
}
