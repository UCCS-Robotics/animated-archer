#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->radioFilter->click();
    ui->label->hide();
    ui->label_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioSample_clicked()
{
    ui->label->show();
    ui->label_2->show();
    ui->spinBoxNumSample->show();
    ui->spinBoxSampleDelay->show();
    ui->pushButtonSample->show();
    ui->pushButtonPauseResume->hide();
}
void MainWindow::on_radioFilter_clicked()
{
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonPauseResume->show();
}

void MainWindow::on_radioRunningAverage_clicked()
{
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonPauseResume->show();
}

void MainWindow::on_radioKalman_clicked()
{
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonPauseResume->show();
}

//Ultrasonic Sensor
void MainWindow::on_actionUS_Sensor_triggered()
{
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}

void MainWindow::on_actionAccelerometer_triggered()
{
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
}

void MainWindow::on_actionGyroscope_triggered()
{
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
}

void MainWindow::on_actionGPS_triggered()
{
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
}

void MainWindow::on_actionCompass_triggered()
{
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}
void MainWindow::on_actionAltimiter_triggered()
{
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}

void MainWindow::on_actionIR_Sensor_triggered()
{
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}
