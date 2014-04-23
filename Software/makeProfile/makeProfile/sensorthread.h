#ifndef SENSORTHREAD_H
#define SENSORTHREAD_H

#include <QThread>
#include <LightSensor.h>
#include <QTimer>
class MainWindow;

class SensorThread : public QThread
{
    Q_OBJECT
public:
    explicit SensorThread(MainWindow *,QObject *parent = 0);

signals:

public slots:
    void on_pauseResume(bool);

private:
    void run();
    LightSensor *lightsensor;
    MainWindow *mainwindow;
    QTimer *timer;
};

#endif // SENSORTHREAD_H
