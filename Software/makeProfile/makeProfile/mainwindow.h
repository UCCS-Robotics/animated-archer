#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include "qcustomplot.h"
#include "device.h"
#include "sensorthread.h"

#define ULTRASONIC 1
#define ACCELEROMETER 2
#define GYROSCOPE 3
#define THERMOMETER 4
#define GPS 5
#define COMPASS 6
#define ALTIMITER 7
#define INFRARED 8

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void sensor_switched();
    void plot();
    void set_xscreen();

signals:
    void send_timer();

private slots:

    void on_radioSample_clicked();

    void on_radioFilter_clicked();

    void on_radioRunningAverage_clicked();

    void on_radioKalman_clicked();

    void on_actionUS_Sensor_triggered();

    void on_actionAccelerometer_triggered();

    void on_actionGyroscope_triggered();

    void on_actionGPS_triggered();

    void on_actionCompass_triggered();

    void on_actionAltimiter_triggered();

    void on_actionIR_Sensor_triggered();

    void on_radioRaw_clicked();

    void on_radioConvert_clicked();

    void on_actionConnect_Device_triggered();

    void processLightSensorData(quint16);

    void on_pushButtonPauseResume_clicked(bool checked);

    void on_timerExpire();

    void on_horizontalSliderScale_valueChanged(int value);

    void on_checkBoxAutoScale_clicked(bool checked);

    void on_horizontalSliderTScale_valueChanged(int value);

    void on_horizontalSliderSpeed_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    char sensor;
    Device *usb;
    QTimer *timer;
    SensorThread *lightsensor;
    int time;
    QDateTime currentTime;
    QVector <double> lsg0, globalData;
    qint64 elapsedTime, pauseTime;
    bool timerStopped, autoScale;
};

#endif // MAINWINDOW_H
