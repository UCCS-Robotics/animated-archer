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

    QWidget::setWindowTitle("Live Data");

    usb = new Device;
    timer = new QTimer(this);
    lightsensor = new SensorThread(this);

    autoScale = true;
    currentTime = QDateTime::currentDateTime();
    ui->horizontalSliderTScale->setValue(10);
    ui->horizontalSliderSpeed->setRange(1,100);
    ui->horizontalSliderSpeed->setValue(100);

    connect(timer, SIGNAL(timeout()),this,SLOT(on_timerExpire()));
    usb->write_LCD("Initialized.");

    plot();
    lightsensor->start();
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete usb;
    delete timer;
    delete lightsensor;
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

void MainWindow::processLightSensorData(quint16 data){
    elapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    globalData.push_back(data);
    ui->mainPlot->graph(0)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data);

    set_xscreen();

    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    //    ui->mainPlot->graph(0)->rescaleAxes(true);

    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(elapsedTime/1000.0) + " " + QString::number(data)+"\n");
    ui->plainTextOutput->ensureCursorVisible();
}

void MainWindow::plot(){
    // add two new graphs and set their look:
    ui->mainPlot->addGraph();
    ui->mainPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->mainPlot->graph(0)->setScatterStyle(ui->mainPlot->graph(0)->scatterStyle().ssCircle);

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
    // Note: we could have also just called ui->mainPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->mainPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->mainPlot->xAxis->setDateTimeFormat("mm:ss:zzz");
    ui->mainPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
}

void MainWindow::on_actionConnect_Device_triggered()
{
    lcdSendCommand(LCD_CLEAR);
}

void MainWindow::on_pushButtonPauseResume_clicked(bool checked)
{
    if(checked){
        timer->stop();
    } else {
        timer->start();

    }
}

void MainWindow::on_timerExpire(){
    emit send_timer();
}

void MainWindow::on_horizontalSliderScale_valueChanged(int value)
{
    ui->mainPlot->yAxis->setScaleRatio(ui->mainPlot->xAxis,value*5);
    ui->mainPlot->replot();
}

void MainWindow::on_checkBoxAutoScale_clicked(bool checked)
{
    autoScale = checked;
}

void MainWindow::set_xscreen(){
    // Set xAxis scale data
    if(globalData.size()-ui->horizontalSliderTScale->value() > 0){
        lsg0.resize(ui->horizontalSliderTScale->value());
        for(int i = globalData.size()-ui->horizontalSliderTScale->value() - 1; i < lsg0.size(); i++){
            lsg0[i] = globalData.at(i);
        }
    }
    ui->mainPlot->rescaleAxes();
    if(elapsedTime/1000.0 > ui->horizontalSliderTScale->value())
        ui->mainPlot->xAxis->setRange(elapsedTime/1000.0 - ui->horizontalSliderTScale->value(), elapsedTime/1000.0+1);
//    ui->mainPlot->xAxis->setAutoTickStep(false);
//    ui->mainPlot->xAxis->setTickStep(1);
    if(autoScale){
        QVector<double>::iterator it = std::max_element(lsg0.begin(), lsg0.end());
        QVector<double>::iterator it2 = std::min_element(lsg0.begin(), lsg0.end());
        ui->mainPlot->yAxis->setRange(*it2-0.1*(*it-*it2)/2, *it+0.1*(*it-*it2)/2);
    }
}

void MainWindow::on_horizontalSliderTScale_valueChanged(int value)
{
    set_xscreen();
    ui->mainPlot->xAxis->setScaleRatio(ui->mainPlot->yAxis,value);
    ui->mainPlot->replot();
}

void MainWindow::on_horizontalSliderSpeed_valueChanged(int value)
{
    ui->lcdNumberSpeed->display(value*10);
    timer->stop();
    timer->start(value*10);
}
