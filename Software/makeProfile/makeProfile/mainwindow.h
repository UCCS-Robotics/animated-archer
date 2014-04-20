#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "commandwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
