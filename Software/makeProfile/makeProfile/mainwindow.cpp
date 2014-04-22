#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

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
    QWidget::setWindowTitle("Live Data");
    usb = new Device;
    plot();
    //connect(usb,SIGNAL(updateChart(double),this,SLOT(on_updateChart(double)));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processOneThing()));

    lightsensor = new LightSensor;
    connect(lightsensor,SIGNAL(sentLightSensorData(uint16_t)),this,SLOT(processLightSensorData(uint16_t)));
    connect(timer, SIGNAL(timeout()), lightsensor, SLOT(updateSensor()));
    timer->start(1000);
    time = 0;
    ui->mainPlot->addGraph();
    ui->mainPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    connect(ui->mainPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->mainPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainPlot->yAxis2, SLOT(setRange(QCPRange)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete usb;
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
    sensor = ULTRASONIC;
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}

void MainWindow::on_actionAccelerometer_triggered()
{
    sensor = ACCELEROMETER;
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
}

void MainWindow::on_actionGyroscope_triggered()
{
    sensor = GYROSCOPE;
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
}

void MainWindow::on_actionGPS_triggered()
{
    sensor = GPS;
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
}

void MainWindow::on_actionCompass_triggered()
{
    sensor = COMPASS;
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}
void MainWindow::on_actionAltimiter_triggered()
{
    sensor = ALTIMITER;
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}

void MainWindow::on_actionIR_Sensor_triggered()
{
    sensor = INFRARED;
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
}

void MainWindow::on_radioRaw_clicked()
{
    switch(sensor){
    case ULTRASONIC:
        ui->mainPlot->yAxis->setLabel("ADC Voltage");
        break;
    case ACCELEROMETER:
        ui->mainPlot->yAxis->setLabel("Reg Values");
        break;
    case GYROSCOPE:
        ui->mainPlot->yAxis->setLabel("Reg Values");
        break;
    case GPS:

        break;
    case COMPASS:
        ui->mainPlot->yAxis->setLabel("Reg Values");
        break;
    case ALTIMITER:
        ui->mainPlot->yAxis->setLabel("Reg Values");
        break;

    case INFRARED:
        ui->mainPlot->yAxis->setLabel("Raw PWM");
        break;
    default:
        if(!ui->radioRaw->isChecked())
            ui->radioRaw->click();
    }

    ui->mainPlot->replot();
}

void MainWindow::sensor_switched(){
    if(ui->radioRaw->isChecked()){
        ui->radioRaw->click();
    } else {
        ui->radioConvert->click();
    }
}

void MainWindow::on_radioConvert_clicked()
{
    switch(sensor){
    case ULTRASONIC:
        ui->mainPlot->yAxis->setLabel("Distance (mm)");
        break;
    case ACCELEROMETER:
        ui->mainPlot->yAxis->setLabel("Acceleration (mm/s^2)");
        break;
    case GYROSCOPE:
        ui->mainPlot->yAxis->setLabel("Angular Velocity (rad/s)");
        break;
    case GPS:

        break;
    case COMPASS:
        ui->mainPlot->yAxis->setLabel("Direction (rad)");
        break;
    case ALTIMITER:
        ui->mainPlot->yAxis->setLabel("Altitude (m)");
        break;

    case INFRARED:
        ui->mainPlot->yAxis->setLabel("Distance (mm)");
        break;
    default:
        if(!ui->radioRaw->isChecked())
            ui->radioRaw->click();
    }

    ui->mainPlot->replot();
}

void MainWindow::processLightSensorData(uint16_t data){
    ui->mainPlot->graph(1)->addData(QVector<double>() << time++, QVector<double>() << data);
    ui->mainPlot->graph(1)->selectedPen().isSolid();
    ui->mainPlot->graph(1)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->mainPlot->graph(1)->rescaleAxes(true);
    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(time) + " " + QString::number(data)+"\n");
    ui->plainTextOutput->ensureCursorVisible();
}

void MainWindow::plot(){
    // add two new graphs and set their look:
    ui->mainPlot->addGraph();
    ui->mainPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph

//    ui->mainPlot->graph(0)->addData(QVector<double>() << 1, QVector<double>() << 1);

    ui->mainPlot->addGraph();
    ui->mainPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->mainPlot->xAxis2->setVisible(true);
    ui->mainPlot->xAxis2->setTickLabels(false);
    ui->mainPlot->yAxis2->setVisible(true);
    ui->mainPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->mainPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->mainPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainPlot->yAxis2, SLOT(setRange(QCPRange)));

//    ui->mainPlot->graph(0)->addData(QVector<double>() << 1, QVector<double>() << 1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->mainPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->mainPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called ui->mainPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->mainPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::on_actionConnect_Device_triggered()
{
    lcdSendCommand(LCD_CLEAR);
}

void MainWindow::on_updateChart(double value){

}

void MainWindow::processOneThing(){
//    time += 1;
//    ui->plainTextOutput->insertPlainText(QString::number(time)+"\n");
//    usb->write_LCD(QString::number(time));
}

//void MainWindow::processLightSensorString(const QString &stringer){
//    ui->plainTextOutput->insertPlainText(stringer);
//    ui->plainTextOutput->ensureCursorVisible();
//}
