#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initialize GUI
    ui->setupUi(this);
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->radioFilter->click();
    ui->label->hide();
    ui->label_2->hide();
    QWidget::setWindowTitle("Live Data");

    // Initialize pointers
    usb = new Device;
    timer = new QTimer(this);
    lightsensor = new SensorThread(this);
    fakesensor = new FakeSensor(this);

    connect(timer, SIGNAL(timeout()),this,SLOT(on_timerExpire()));  // Used to update plot
    connect(usb, SIGNAL(deviceError(QString)), this, SLOT(on_deviceError(QString)));  // Used to emit an error from the device interface

    plot(); // Initialize plot
    //    lightsensor->start();   // Start lightsensor thread
    fakesensor->start();


    // The following slider options must be initialized after starting the timer
    ui->horizontalSliderTScale->setValue(10);
    ui->horizontalSliderSpeed->setRange(1,100);
    ui->horizontalSliderSpeed->setValue(100);

    timer->start(1000); // Start sampling at 1 second

}

MainWindow::~MainWindow()
{
    delete ui;
    delete usb;
    delete timer;
    lightsensor->quit();    //Stop thread
    while(lightsensor->isRunning());    //Wait for thread to stop
    delete lightsensor;
}

// Option to take samples instead of streaming live data
void MainWindow::on_radioSample_clicked()
{
    ui->label->show();
    ui->label_2->show();
    ui->spinBoxNumSample->show();
    ui->spinBoxSampleDelay->show();
    ui->pushButtonSample->show();
    ui->pushButtonPauseResume->hide();
}

// This option exists if the user doesn't want filtered data
void MainWindow::on_radioFilter_clicked()
{
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonPauseResume->show();
}

// Apply a running average filter to the incoming data
void MainWindow::on_radioRunningAverage_clicked()
{
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonPauseResume->show();
}

// Apply the Kalman filter to incoming data
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

// Accelerometer
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

// Gyroscope
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

// Global Positioning System
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

// Magnetometer
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

// Barometer
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

// Infrared Sensor
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

// Raw data (not passed through transfer function)
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

// Make sure UI is displaying correct options
void MainWindow::sensor_switched(){
    if(ui->radioRaw->isChecked()){
        ui->radioRaw->click();
    } else {
        ui->radioConvert->click();
    }
}

// Run the raw data through the proper transfer functions
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

// Import light sensor data (for testing purposes)
void MainWindow::processLightSensorData(const QDateTime& stamp, quint16 data){
    processAxisX(stamp,data);
}

void MainWindow::processAxisX(const QDateTime& stamp, quint16 data){
    elapsedTime = stamp.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    globalData1.push_back(data);


    ui->mainPlot->graph(0)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data);
    ui->mainPlot->graph(0)->selectedPen().isSolid();

    set_xscreen(globalData1);

    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(elapsedTime/1000.0) + " " + QString::number(data)+"\n");
    ui->plainTextOutput->ensureCursorVisible();
}

void MainWindow::plotSensor(const QDateTime &stamp, quint16 data1, quint16 data2, quint16 data3){
    elapsedTime = stamp.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    globalData1.push_back(data1);
    globalData2.push_back(data2);
    globalData3.push_back(data3);


    ui->mainPlot->graph(0)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data1);
    ui->mainPlot->graph(1)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data2);
    ui->mainPlot->graph(2)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data3);

    set_xscreen(globalData1, globalData2, globalData3);


    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(elapsedTime/1000.0) + ":\n1)\t" + QString::number(data1)+"\n2)\t" + QString::number(data2)+"\n3)\t" + QString::number(data3)+ "\n" );
    ui->plainTextOutput->ensureCursorVisible();
}

void MainWindow::on_deviceError(const QString& msg)
{
    ui->plainTextOutput->insertPlainText(tr("Device error: %1\n").arg(msg));
    ui->plainTextOutput->ensureCursorVisible();
}

// Setup the plot params
void MainWindow::plot(){
    autoScale = true;  // Autoscale plot
    currentTime = QDateTime::currentDateTime();

    ui->mainPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->mainPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->mainPlot->legend->setFont(legendFont);
    ui->mainPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    ui->mainPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop |Qt::AlignLeft);

    // add new graph and set style
    // line for first graphs
    // Adds circles at each datapoint
    ui->mainPlot->addGraph();
    ui->mainPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->mainPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->mainPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->mainPlot->graph(0)->setName("Axis 1");

    ui->mainPlot->addGraph();
    ui->mainPlot->graph(1)->setPen(QPen(Qt::red));
    ui->mainPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->mainPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->mainPlot->graph(1)->setName("Axis 2");

    ui->mainPlot->addGraph();
    ui->mainPlot->graph(2)->setPen(QPen(Qt::green));
    ui->mainPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->mainPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->mainPlot->graph(2)->setName("Axis 3");

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->mainPlot->xAxis2->setVisible(true);
    ui->mainPlot->xAxis2->setTickLabels(false);
    ui->mainPlot->yAxis2->setVisible(true);
    ui->mainPlot->yAxis2->setTickLabels(false);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->mainPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->mainPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainPlot->yAxis2, SLOT(setRange(QCPRange)));

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->mainPlot->graph(0)->rescaleAxes();
    // Note: we could have also just called ui->mainPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->mainPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // Set axis display type
    ui->mainPlot->xAxis->setDateTimeFormat("mm:ss:zzz");
    ui->mainPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);

    ui->mainPlot->plotLayout()->insertRow(0);
    ui->mainPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->mainPlot, "Live Data"));

    ui->mainPlot->xAxis->setLabel("Time (sec)");
    ui->mainPlot->yAxis->setLabel("Data");

    refPlot = ui->mainPlot;
}

void MainWindow::on_actionConnect_Device_triggered()
{
    // nothing
}

// Used to pause the sampling of data, and updating the plot
void MainWindow::on_pushButtonPauseResume_clicked(bool checked)
{
    if(checked){
        timer->stop();
    } else {
        timer->start(ui->horizontalSliderSpeed->value());
    }
}

// Emit timer expiration to sensors to sample and update plot
void MainWindow::on_timerExpire(){
    emit send_timer();
}

void MainWindow::on_checkBoxAutoScale_clicked(bool checked)
{
    autoScale = checked;
    ui->mainPlot->yAxis->setScaleRatio(refPlot->xAxis,ui->spinBoxData->value()*5);
    ui->mainPlot->replot();
}

void MainWindow::set_xscreen(const QVector <double> &data){
    int tmp = 100*ui->horizontalSliderTScale->value()/ui->horizontalSliderSpeed->value();
    lsg0.resize(tmp+1);
    int j =0;
    if(data.size()-tmp-2 > 0)
        for(int i = data.size()-1; i > data.size()-2-tmp;i--){
            lsg0[j++]=data.at(i);
        }

    ui->mainPlot->graph(0)->rescaleAxes();

    if(elapsedTime/1000.0 > ui->horizontalSliderTScale->value())
        ui->mainPlot->xAxis->setRange(elapsedTime/1000.0 - ui->horizontalSliderTScale->value(), elapsedTime/1000.0);

    if(autoScale){
        ui->mainPlot->yAxis->setRange(find_axis_range(lsg0));
    }
}

void MainWindow::set_xscreen(const QVector <double> &data1,const QVector <double> &data2,const QVector <double> &data3){
    int tmp = 100*ui->horizontalSliderTScale->value()/ui->horizontalSliderSpeed->value();
    int j =0;

    if(data1.size()-tmp-2 > 0){
        lsg0.resize(tmp+1);
        for(int i = data1.size()-1; i > data1.size()-2-tmp;i--){
            lsg0[j++]=data1.at(i);
        }
    }
    else{
        lsg0 = data1;
    }

    j = 0;
    if(data2.size()-tmp-2 > 0){
        lsg1.resize(tmp+1);
        for(int i = data2.size()-1; i > data2.size()-2-tmp;i--){
            lsg1[j++]=data2.at(i);
        }
    }
    else{
        lsg1 = data2;
    }

    j = 0;
    if(data3.size()-tmp-2 > 0){
        lsg2.resize(tmp+1);
        for(int i = data3.size()-1; i > data3.size()-2-tmp;i--){
            lsg2[j++]=data3.at(i);
        }
    }
    else{
        lsg2 = data3;
    }


    ui->mainPlot->rescaleAxes();

    if(!autoScale)
        ui->mainPlot->yAxis->setScaleRatio(refPlot->xAxis,ui->spinBoxData->value()*5);

    if(elapsedTime/1000.0 > ui->horizontalSliderTScale->value())
        ui->mainPlot->xAxis->setRange(elapsedTime/1000.0 - ui->horizontalSliderTScale->value(), elapsedTime/1000.0);

    if(autoScale){
        ui->mainPlot->yAxis->setRange(find_axis_range(lsg0,lsg1,lsg2));
    }
}

// Logic to take 2 ranges and find the minimum and maximum of the two, and return one range that encompasses both
QCPRange MainWindow::find_axis_range_logic(const QCPRange &range1, const QCPRange &range2){
    double max, min;

    // Find the max of both
    if(range1.upper>range2.upper){
        max=range1.upper;
    } else {
        max=range2.upper;
    }

    // Find the min of both
    if(range1.lower<range2.lower){
        min=range1.lower;
    } else {
        min=range2.lower;
    }

    return QCPRange(min,max);
}

// Given a vector of data return the range
QCPRange MainWindow::find_axis_range(QVector<double> data1){
    // Find the max and min using iterators
    QVector<double>::iterator it = std::max_element(data1.begin(), data1.end());
    QVector<double>::iterator it2 = std::min_element(data1.begin(), data1.end());

    // Return the min and max as a range with 5% extra space on top and bottom of screen
    return QCPRange(*it2-0.05*(*it-*it2)/2,*it+0.05*(*it-*it2)/2);
}

// Performs same function as find_axis_range with 1 vector, just finds the min and max of both so the window shows all
QCPRange MainWindow::find_axis_range(const QVector<double>& data1,const QVector<double>& data2){
    QCPRange range1, range2;

    // Min and max of both vectors
    range1=find_axis_range(data1);
    range2=find_axis_range(data2);

    // Min and max of both ranges
    return find_axis_range_logic(range1,range2);
}

// Performs same function as find_axis_range with 1 and 2 vectors, just finds the min and max of each so the window shows all
QCPRange MainWindow::find_axis_range(const QVector<double>& data1,const QVector<double>& data2,const QVector<double>& data3){
    QCPRange range1, range2;

    // Min and max of all 3
    range1 = find_axis_range(data1,data2);
    range2 = find_axis_range(data3);

    // Min and max of each range
    return find_axis_range_logic(range1,range2);
}

// Set the xAxis scale
void MainWindow::on_horizontalSliderTScale_valueChanged(int value)
{
    ui->spinBoxTime->setValue(value);
    ui->mainPlot->xAxis->setScaleRatio(refPlot->yAxis,value);
    if(ui->horizontalSliderScale->value()==0){
        refPlot->xAxis = ui->mainPlot->xAxis;
    }
    ui->mainPlot->replot();
}

void MainWindow::on_spinBoxTime_valueChanged(int arg1)
{
    ui->horizontalSliderTScale->setValue(arg1);
}

// Scale the yaxis with respect to the xaxis
void MainWindow::on_horizontalSliderScale_valueChanged(int value)
{
    ui->spinBoxData->setValue(value);
    ui->mainPlot->yAxis->setScaleRatio(refPlot->xAxis,value*5);
    if(ui->horizontalSliderTScale->value()==10){
        refPlot->yAxis = ui->mainPlot->yAxis;
    }
    ui->mainPlot->replot();
}

void MainWindow::on_spinBoxData_valueChanged(int arg1)
{
    ui->horizontalSliderScale->setValue(arg1);
}

// Change the sample speed
void MainWindow::on_horizontalSliderSpeed_valueChanged(int value)
{
    ui->spinBoxSpeed->setValue(value*10);
    if(timer->isActive())
        timer->stop();
    timer->start(value*10);
}

void MainWindow::on_spinBoxSpeed_valueChanged(int arg1)
{
    ui->horizontalSliderSpeed->setValue(arg1);
}
