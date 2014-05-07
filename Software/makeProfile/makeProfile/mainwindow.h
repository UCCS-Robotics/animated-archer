#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QClipboard>
#include <QList>
#include "qcustomplot.h"
#include "sensors.h"

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
    void set_xscreen(const QVector <double>&);
    void set_xscreen(const QVector <double>&,const QVector <double>&);
    void set_xscreen(const QVector <double>&,const QVector <double>&,const QVector <double>&);
    QCPRange find_axis_range(QVector<double>);
    QCPRange find_axis_range(const QVector<double>&,const QVector<double>&);
    QCPRange find_axis_range(const QVector<double>&,const QVector<double>&,const QVector<double>&);
    QCPRange find_axis_range_logic(const QCPRange&,const QCPRange&);
    void stop_all_sensors();
    void sampleData();

signals:
    void send_timer();
    void send_disconnect();
    void send_connect();
    void time_changed(qint32);

private slots:

    void on_radioSample_clicked();

    void on_radioFilter_clicked();

    void on_radioRunningAverage_clicked();

    void on_radioKalman_clicked();

    void on_actionUS_Sensor_triggered();

    void on_actionGPS_triggered();

    void on_actionAltimiter_triggered();

    void on_actionIR_Sensor_triggered();

    void on_radioRaw_clicked();

    void on_radioConvert_clicked();

    void on_actionConnect_Device_triggered();

    void processLightSensorData(const QDateTime&, quint16);
    void processADCData(const QDateTime&, quint8, quint16);

    void processAxisX(const QDateTime&, quint16);

    void recordSensor(const QDateTime&, quint16, quint16, quint16);

    void recordSensor(const QDateTime&, quint16, quint16);

    void recordSensor(const QDateTime&, quint16);

    void on_deviceError(const QString& msg);

    void on_pushButtonPauseResume_clicked(bool checked);

    void on_timerExpire();

    void on_horizontalSliderScale_valueChanged(int value);

    void on_checkBoxAutoScale_clicked(bool checked);

    void on_horizontalSliderTScale_valueChanged(int value);

    void on_horizontalSliderSpeed_valueChanged(int value);

    void on_spinBoxTime_valueChanged(int arg1);

    void on_spinBoxData_valueChanged(int arg1);

    void on_spinBoxSpeed_valueChanged(int arg1);

    void on_checkBoxData1_clicked(bool checked);

    void on_checkBoxData2_clicked(bool checked);

    void on_checkBoxData3_clicked(bool checked);

    void on_actionFake_Sensor_triggered();

    void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable);
    void graphCopy();
    void windowCopy();

    void on_actionLight_Sensor_triggered();

    void on_pushButtonRecord_clicked();

    void on_pushButtonSample_clicked();

    void on_action9_DOF_triggered();

private:
    Ui::MainWindow *ui;
    char sensor, usedAxes;
    Device *usb;
    QTimer *timer;
    int time;
    QDateTime currentTime, currTime, nextTime;
    QVector <double> lsg0, lsg1, lsg2, globalData, globalData1, globalData2, globalData3;
    qint64 elapsedTime, pauseTime, numSamples;
    bool timerStopped, autoScale, limitSamples;
    QCustomPlot *refPlot;
    QClipboard *clipboard;
    sensors *device;
};

#endif // MAINWINDOW_H
