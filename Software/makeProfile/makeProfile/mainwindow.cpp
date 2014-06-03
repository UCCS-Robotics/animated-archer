#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initialize GUI
    ui->setupUi(this);
    mainPlot = new Plotter(this);
    ui->statusBar->showMessage(QString("Initializing."),1000);
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonPauseResume->show();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonRecord->setDisabled(true);
    QWidget::setWindowTitle("Live Data");

    colors.insert(0,QPen(Qt::blue));
    colors.insert(1,QPen(Qt::red));
    colors.insert(2,QPen(Qt::green));
    colors.insert(3,QPen(Qt::gray));
    colors.insert(4,QPen(Qt::black));
    colors.insert(5,QPen(Qt::cyan));
    colors.insert(6,QPen(Qt::magenta));
    colors.insert(7,QPen(Qt::darkYellow));
    colors.insert(8,QPen(Qt::darkCyan));

    // Initialize pointers
    timer = new QTimer(this);
    device = new sensors(this);

    elapsedTime = 0;
    limitSamples = false;
    usedAxes = 0;

    plot(); // Initialize plot

    // The following slider options must be initialized after starting the timer
    ui->horizontalSliderTScale->setValue(10);
    ui->horizontalSliderTScale->setRange(1,100);
    ui->spinBoxTime->setRange(1,100);
    ui->horizontalSliderSpeed->setRange(1,100);
    ui->horizontalSliderSpeed->setValue(100);
    ui->spinBoxNumSample->setRange(1,1000);
    ui->spinBoxSampleDelay->setRange(1,10000);
    ui->mainToolBar->hide();

    ui->statusBar->showMessage(QString("Starting sensor monitoring."),1000);
    numSamples = 0;
        on_actionFake_Sensor_triggered();
    //    on_actionLight_Sensor_triggered();
//    device->select_sudo_sensor();
//    device->select_ads1015();
    connect(device,SIGNAL(raw_data_ready(QVector<QVector<qint32> >)),this,SLOT(plotSensor(QVector<QVector<qint32> >)));

    mainPlot->clear_all_graph_data();
    on_actionFake_Sensor_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

QCustomPlot *MainWindow::get_qplot(){
    return ui->mainPlot;
}

// Option to take samples instead of streaming live data
void MainWindow::on_radioSample_clicked()
{
    // Stop incoming data, clear aquired data
    timer->stop();
    // device.clear_data()
    device->clear_data();
    mainPlot->clear_all_graph_data();
    mainPlot->update_plot();

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
    if(!timer->isActive())
        timer->start(ui->spinBoxSpeed->value());
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
    if(!timer->isActive())
        timer->start(ui->spinBoxSpeed->value());
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
    if(!timer->isActive())
        timer->start(ui->spinBoxSpeed->value());
    ui->spinBoxNumSample->hide();
    ui->spinBoxSampleDelay->hide();
    ui->pushButtonSample->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButtonPauseResume->show();
}


void MainWindow::stop_all_sensors(){
    device->stop_all_sensors();
}


//Ultrasonic Sensor
void MainWindow::on_actionUS_Sensor_triggered()
{
    device->select_ads1015();
    device->set_device_name("UltraSonic");
    mainPlot->remove_all_graphs();
    for(int i = 1; i < 5; i++){
        mainPlot->create_graph(ADC+i);
        mainPlot->set_graph_name(ADC+i,device->get_device_name()+ " "+QString::number(i));
    }
    mainPlot->set_graph_pen(ADC+1, QPen(Qt::blue));
    mainPlot->set_graph_pen(ADC+2, QPen(Qt::red));
    mainPlot->set_graph_pen(ADC+3, QPen(Qt::green));
    mainPlot->set_graph_pen(ADC+4, QPen(Qt::yellow));
    usedAxes = device->get_used_graphs();
    sensor = (char)device->get_sensor_type();
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
    mainPlot->set_title("Ultrasonic Live Data");
}

void MainWindow::on_action9_DOF_triggered()
{
    device->select_lsm9ds0();
    usedAxes = device->get_used_graphs();
    sensor = (char)device->get_sensor_type();
    sensor_switched();
    //...
}

// Global Positioning System
void MainWindow::on_actionGPS_triggered()
{
    device->select_ls20031();
    usedAxes = device->get_used_graphs();
    sensor = (char)device->get_sensor_type();
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
    ui->mainPlot->plotLayout()->removeAt(0);
    ui->mainPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->mainPlot, "GPS Live Data"));
}

// Barometer
void MainWindow::on_actionAltimiter_triggered()
{
    device->select_mpl3115a2();
    usedAxes = device->get_used_graphs();
    sensor = device->get_sensor_type();
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
    ui->mainPlot->plotLayout()->removeAt(0);
    ui->mainPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->mainPlot, "Altimiter Live Data"));
}

// Infrared Sensor
void MainWindow::on_actionIR_Sensor_triggered()
{
    device->select_infrared();
    usedAxes = device->get_used_graphs();
    sensor = device->get_sensor_type();
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
    ui->mainPlot->plotLayout()->removeAt(0);
    ui->mainPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->mainPlot, "Infra-Red Live Data"));
}

void MainWindow::on_actionFake_Sensor_triggered()
{
    device->select_sudo_sensor();
    device->set_sample_period(100);
    device->set_device_name("Sudo");
    device->set_device_id(0);
    mainPlot->remove_all_graphs();
    for(int i = 1; i < 10; i++){
        mainPlot->create_graph(FAKE+i);
        mainPlot->set_graph_name(FAKE+i,device->get_device_name()+ " "+QString::number(i));
        mainPlot->set_graph_pen(FAKE+i,colors.value(i-1));
    }
    usedAxes = device->get_used_graphs();
    sensor = device->get_sensor_type();
    if(device->get_sensor_type() != FAKE){
        device->clear_data();
    }
    //device->set_sensor_type(FAKE);
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->show();
    ui->labelRed->show();
    ui->checkBoxData3->show();
    ui->labelGreen->show();
    mainPlot->set_title("Fake Live Data");
    ui->statusBar->showMessage(QString("Plotting Fake Sensor."),2000);
}

void MainWindow::on_actionLight_Sensor_triggered()
{
    device->select_light_sensor();
    device->set_device_name("Light");
    mainPlot->remove_all_graphs();

    mainPlot->create_graph(LIGHT+1);
    mainPlot->set_graph_name(LIGHT+1,"Light 1");
    mainPlot->set_graph_pen(LIGHT+1, QPen(Qt::blue));
    usedAxes = device->get_used_graphs();
    sensor = device->get_sensor_type();
    if(device->get_sensor_type() != LIGHT){
        device->clear_data();
    }
    //device->set_sensor_type(LIGHT);
    sensor_switched();
    ui->checkBoxData1->show();
    ui->labelBlue->show();
    ui->checkBoxData2->hide();
    ui->labelRed->hide();
    ui->checkBoxData3->hide();
    ui->labelGreen->hide();
    mainPlot->set_title("Light Live Data");
    ui->statusBar->showMessage(QString("Plotting Light Sensor."),2000);
}

// Raw data (not passed through transfer function)
void MainWindow::on_radioRaw_clicked()
{
    switch(device->get_sensor_type()){
    case ADC:
        ui->mainPlot->yAxis->setLabel("ADC Voltage");
        break;
    case ACCELEROMETER:
        ui->mainPlot->yAxis->setLabel("Reg Values");
        break;
    case GYROSCOPE:
        ui->mainPlot->yAxis->setLabel("Reg Values");
        break;
    case GPS:
        ui->mainPlot->yAxis->setLabel("Reg Values");
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
    case FAKE:
        ui->mainPlot->yAxis->setLabel("Fake Raw");
        break;
    case LIGHT:
        ui->mainPlot->yAxis->setLabel("Light Raw");
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
    switch(device->get_sensor_type()){
    case ADC:
        ui->mainPlot->yAxis->setLabel("Distance (mm)");
        break;
    case ACCELEROMETER:
        ui->mainPlot->yAxis->setLabel("Acceleration (mm/s^2)");
        break;
    case GYROSCOPE:
        ui->mainPlot->yAxis->setLabel("Angular Velocity (rad/s)");
        break;
    case GPS:
        ui->mainPlot->yAxis->setLabel("Coordinates (unit unknown at the moment");
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
    case FAKE:
        ui->mainPlot->yAxis->setLabel("Fake Converted Data");
        break;
    case LIGHT:
        ui->mainPlot->yAxis->setLabel("Lux");
    default:
        if(!ui->radioRaw->isChecked())
            ui->radioRaw->click();
    }

    ui->mainPlot->replot();
}

// Import light sensor data (for testing purposes)
void MainWindow::processLightSensorData(const QDateTime& stamp, quint16 data){
    recordSensor(stamp,data);
}

// Import light sensor data (for testing purposes)
void MainWindow::processADCData(const QDateTime& stamp, quint8 chan, quint16 data){
    recordSensor(stamp,data);
}

void MainWindow::processAxisX(const QDateTime& stamp, quint16 data){
    elapsedTime += stamp.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    currentTime = QDateTime::currentDateTime();
    globalData.push_back(elapsedTime/1000.0);
    globalData1.push_back(data);


    ui->mainPlot->graph(0)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data);
    ui->mainPlot->graph(0)->selectedPen().isSolid();

    set_xscreen(globalData1);

    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(elapsedTime/1000.0) + " " + QString::number(data)+"\n");
    ui->plainTextOutput->ensureCursorVisible();
}

void MainWindow::sampleData(){
    if(limitSamples == true && globalData.size()==numSamples){
        if(timer->isActive())
            timer->stop();
        limitSamples = false;
        QVector<double>::size_type size = globalData.size();
        double sum0 = 0;
        double sum1 = 0;
        double sum2 = 0;

        if(usedAxes>=1)
            for(QVector<double>::const_iterator i = globalData1.begin(); i != globalData1.end(); ++i)
                sum0 += *i;
        if(usedAxes>=2)
            for(QVector<double>::const_iterator i = globalData2.begin(); i != globalData2.end(); ++i)
                sum1 += *i;
        if(usedAxes>=3)
            for(QVector<double>::const_iterator i = globalData3.begin(); i != globalData3.end(); ++i)
                sum2 += *i;
        if(usedAxes>=1)
            ui->plainTextOutput->insertPlainText(QString("\nMean:\n%1) '%2'\n").arg(ui->checkBoxData1->text(), QString::number((float)sum0/size)));
        if(usedAxes>=2)
            ui->plainTextOutput->insertPlainText(QString("%1) '%2'\n").arg(ui->checkBoxData2->text(), QString::number((float)sum1/size)));
        if(usedAxes>=3)
            ui->plainTextOutput->insertPlainText(QString("%1) '%2'\n").arg(ui->checkBoxData3->text(), QString::number((float)sum2/size)));
        ui->plainTextOutput->insertPlainText("\n");
    }
    ui->plainTextOutput->ensureCursorVisible();
}

void MainWindow::plotSensor(const QVector <QVector <qint32> > &data){
    //mainPlot->add_graph_data(FAKE+1, data.at(data.size()-1).at(0)/1000.0, data.at(data.size()-1).at(1));
    for(int i = 1; i < data.at(data.size()-1).size(); i++){
        mainPlot->add_graph_data(FAKE+i, data.at(data.size()-1).at(0)/1000.0, data.at(data.size()-1).at(i));
    }
    mainPlot->set_xWindow_range(10);
    mainPlot->set_number_xData_points(10/0.1);
    mainPlot->set_auto_range_scale(true);
    mainPlot->update_plot();
//    double et = data.at(data.size()-1).at(0)/1000.0;
//    qint32 da = data.at(data.size()-1).at(1);

//    ui->mainPlot->graph(0)->addData(QVector<double>() << et, QVector<double>() << da);
////    //    set_xscreen(data.at(1));
//    int tmp = 100*ui->horizontalSliderTScale->value()/ui->horizontalSliderSpeed->value();
//    int j =0;

//    if(data.size()-tmp-2 > 0){
//        lsg0.resize(tmp+1);
//        for(int i = data.size()-1; i > data.size()-2-tmp;i--){
//            lsg0[j++]=data.at(i).at(1);
//        }
//    }
//    else{
//        //lsg0 = data.at(1);
//        lsg0.resize(data.size());
//        for(int i = 0; i < data.size(); i++){
//            lsg0[i] = data.at(i).at(1);
//        }
//    }

//    ui->mainPlot->rescaleAxes();

//    if(!autoScale)
//        ui->mainPlot->yAxis->setScaleRatio(refPlot->xAxis,ui->spinBoxData->value()*5);

//    if(elapsedTime/1000.0 > ui->horizontalSliderTScale->value())
//        ui->mainPlot->xAxis->setRange(elapsedTime/1000.0 - ui->horizontalSliderTScale->value(), elapsedTime/1000.0);

//    if(autoScale){
//        ui->mainPlot->yAxis->setRange(find_axis_range(lsg0));
//    }
//    ///////
//    ui->mainPlot->replot();
//    ui->plainTextOutput->insertPlainText(QString::number(et) + QString(":\n%1)\t").arg(ui->checkBoxData1->text()) + QString::number(da)+"\n\n");
//    ui->plainTextOutput->ensureCursorVisible();
}

void MainWindow::recordSensor(const QDateTime &stamp, quint16 data1){
    elapsedTime += stamp.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    currentTime = QDateTime::currentDateTime();
    if(limitSamples == true && globalData.size()==numSamples){
        if(timer->isActive())
            timer->stop();
    }
    globalData.push_back(elapsedTime/1000.0);
    globalData1.push_back(data1);

    ui->mainPlot->graph(0)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data1);

    set_xscreen(globalData1);


    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(elapsedTime/1000.0) + QString(":\n%1)\t").arg(ui->checkBoxData1->text()) + QString::number(data1)+"\n\n");
    ui->plainTextOutput->ensureCursorVisible();
    sampleData();
}

void MainWindow::recordSensor(const QDateTime &stamp, quint16 data1, quint16 data2){
    elapsedTime += stamp.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    currentTime = QDateTime::currentDateTime();
    if(limitSamples == true && globalData.size()==numSamples){
        if(timer->isActive())
            timer->stop();
    }
    globalData.push_back(elapsedTime/1000.0);
    globalData1.push_back(data1);
    globalData2.push_back(data2);


    ui->mainPlot->graph(0)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data1);
    ui->mainPlot->graph(1)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data2);

    set_xscreen(globalData1, globalData2);


    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(elapsedTime/1000.0) + QString(":\n%1)\t").arg(ui->checkBoxData1->text()) + QString::number(data1)+QString(":\n%1)\t").arg(ui->checkBoxData2->text()) + QString::number(data2)+"\n\n");
    ui->plainTextOutput->ensureCursorVisible();
    sampleData();
}

void MainWindow::recordSensor(const QDateTime &stamp, quint16 data1, quint16 data2, quint16 data3){
    elapsedTime += stamp.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch();
    currentTime = QDateTime::currentDateTime();
    if(limitSamples == true && globalData.size()==numSamples){
        if(timer->isActive())
            timer->stop();
    }
    globalData.push_back(elapsedTime/1000.0);
    globalData1.push_back(data1);
    globalData2.push_back(data2);
    globalData3.push_back(data3);


    ui->mainPlot->graph(0)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data1);
    ui->mainPlot->graph(1)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data2);
    ui->mainPlot->graph(2)->addData(QVector<double>() << elapsedTime/1000.0, QVector<double>() << data3);

    set_xscreen(globalData1, globalData2, globalData3);


    ui->mainPlot->replot();
    ui->plainTextOutput->insertPlainText(QString::number(elapsedTime/1000.0) + QString(":\n%1)\t").arg(ui->checkBoxData1->text()) + QString::number(data1)+QString("\n%1)\t").arg(ui->checkBoxData2->text())+ QString::number(data2) + QString("\n%1)\t").arg(ui->checkBoxData3->text()) + QString::number(data3)+ "\n\n" );
    ui->plainTextOutput->ensureCursorVisible();
    sampleData();
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

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->mainPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));
    connect(mainPlot, SIGNAL(copy_graph_data()), this, SLOT(graphCopy()));
    connect(mainPlot, SIGNAL(copy_plot_image()), this, SLOT(windowCopy()));

    // Used for scaling
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
        ui->pushButtonPauseResume->setText("Resume");
        ui->pushButtonRecord->setEnabled(true);
    } else {
        timer->start(ui->spinBoxSpeed->value());
        currentTime = QDateTime::currentDateTime();
        ui->pushButtonPauseResume->setText("Pause");
        ui->pushButtonRecord->setDisabled(true);
    }
}

// Emit timer expiration to sensors to sample and update plot
void MainWindow::on_timerExpire(){
    emit send_timer();
}

// Enable or disable autoscale
void MainWindow::on_checkBoxAutoScale_clicked(bool checked)
{
    autoScale = checked;
    ui->mainPlot->yAxis->setScaleRatio(refPlot->xAxis,ui->spinBoxData->value()*5);
    ui->mainPlot->replot();
}

// Setup the window for easy viewing (one axis)
void MainWindow::set_xscreen(const QVector <double> &data1){
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

    ui->mainPlot->rescaleAxes();

    if(!autoScale)
        ui->mainPlot->yAxis->setScaleRatio(refPlot->xAxis,ui->spinBoxData->value()*5);

    if(elapsedTime/1000.0 > ui->horizontalSliderTScale->value())
        ui->mainPlot->xAxis->setRange(elapsedTime/1000.0 - ui->horizontalSliderTScale->value(), elapsedTime/1000.0);

    if(autoScale){
        ui->mainPlot->yAxis->setRange(find_axis_range(lsg0));
    }
}

// Setup the window for easy viewing (two axis')
void MainWindow::set_xscreen(const QVector <double> &data1,const QVector <double> &data2){
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

    ui->mainPlot->rescaleAxes();

    if(!autoScale)
        ui->mainPlot->yAxis->setScaleRatio(refPlot->xAxis,ui->spinBoxData->value()*5);

    if(elapsedTime/1000.0 > ui->horizontalSliderTScale->value())
        ui->mainPlot->xAxis->setRange(elapsedTime/1000.0 - ui->horizontalSliderTScale->value(), elapsedTime/1000.0);

    if(autoScale){
        ui->mainPlot->yAxis->setRange(find_axis_range(lsg0,lsg1,lsg2));
    }
}

// Setup the window for easy viewing (three axis)
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
    if(!ui->pushButtonPauseResume->isChecked())
        timer->start(value*10);
    emit time_changed(value*10);
    //    device->get_ads1015()->program(value*10);
}

void MainWindow::on_spinBoxSpeed_valueChanged(int arg1)
{
    ui->horizontalSliderSpeed->setValue(arg1/10);
}

// Hide/show axis1
void MainWindow::on_checkBoxData1_clicked(bool checked)
{
//    if(checked){
//        ui->mainPlot->graph(0)->setVisible(true);
//        ui->mainPlot->graph(0)->addToLegend();
//    } else {
//        ui->mainPlot->graph(0)->setVisible(false);
//        ui->mainPlot->graph(0)->removeFromLegend();
//    }
//    ui->mainPlot->replot();
}

// Hide/show axis2
void MainWindow::on_checkBoxData2_clicked(bool checked)
{
//    if(checked){
//        ui->mainPlot->graph(1)->setVisible(true);
//        ui->mainPlot->graph(1)->addToLegend();
//    } else {
//        ui->mainPlot->graph(1)->setVisible(false);
//        ui->mainPlot->graph(1)->removeFromLegend();
//    }
//    ui->mainPlot->replot();
}

// Hide/show axis3
void MainWindow::on_checkBoxData3_clicked(bool checked)
{
//    if(checked){
//        ui->mainPlot->graph(2)->setVisible(true);
//        ui->mainPlot->graph(2)->addToLegend();
//    } else {
//        ui->mainPlot->graph(2)->setVisible(false);
//        ui->mainPlot->graph(2)->removeFromLegend();
//    }
//    ui->mainPlot->replot();
}

// Copy graph data to clipboard in a format compatable with pasting into spreadsheets
void MainWindow::graphCopy(){
}

// Copy current plot window to clipboard
void MainWindow::windowCopy()
{
    ui->statusBar->showMessage(QString("Current window copied to clipboard."),2000);
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable){

}

void MainWindow::on_pushButtonRecord_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "DialogTitle", "filename.csv", "CSV files (*.csv);;Zip files (*.zip, *.7z)", 0, 0); // getting the filename (full path)
    QFile data(filename);
    if(data.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream output(&data);
        output << "time,";
        if(!ui->checkBoxData1->isHidden())
            output << ui->checkBoxData1->text();
        if(!ui->checkBoxData2->isHidden())
            output << "," << ui->checkBoxData2->text();
        if(!ui->checkBoxData3->isHidden())
            output << "," << ui->checkBoxData3->text();
        output << "\n";

        for(int i = 0; i < globalData.size(); i++){
            output << globalData.at(i);
            if(!ui->checkBoxData1->isHidden())
                output << "," << globalData1.at(i);
            if(!ui->checkBoxData2->isHidden())
                output << "," << globalData2.at(i);
            if(!ui->checkBoxData3->isHidden())
                output << "," << globalData3.at(i);
            output << "\n";
        }
        data.close();
    }
}

void MainWindow::on_pushButtonSample_clicked()
{
    limitSamples = true;
    numSamples = ui->spinBoxNumSample->value();

    globalData.resize(0);
    globalData1.resize(0);
    globalData2.resize(0);
    globalData3.resize(0);
    ui->mainPlot->graph(0)->clearData();
    ui->mainPlot->graph(1)->clearData();
    ui->mainPlot->graph(2)->clearData();
    ui->mainPlot->replot();

    if(!timer->isActive())
        timer->start(ui->spinBoxSampleDelay->value());
    elapsedTime = 0;
    currentTime = QDateTime::currentDateTime();
}
