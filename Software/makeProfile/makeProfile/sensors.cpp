#include "sensors.h"
#include "mainwindow.h"
#include <QDateTime>

sensors::sensors(MainWindow *mainwindowin, QObject *parent) :
    QObject(parent)
{
    mainwindow = mainwindowin;
    usb = new Device;   // Used to indicate device errors
    timer = new QTimer(this);
    elapsedTime = 0;    // Always start record time at 0ms
    connect(usb, SIGNAL(deviceError(QString)),
            this, SLOT(on_device_error(QString)));  // Relay error
    set_sample_period(500); // Temporary, remove later
    set_number_samples(0);
    set_conversion_flag(false);
}

sensors::~sensors(){
    stop_all_sensors();
}

/********************************************************************
 * Slots                                                            *
 *******************************************************************/

void sensors::on_device_error(QString error){
    emit device_error(error);
    //    connect(usb, SIGNAL(deviceError(QString)),
    //            mainwindow, SLOT(on_deviceError(QString))); // Device error connection
}

void sensors::on_record_sensor(const QDateTime &time_cast, const QVector<qint32> &data){
    // Format: [stamp.ms,graph0,graph1,...]
    if(globalRawData.size() == get_number_samples() && // if num samples defined and reached
            get_number_samples() != 0){
        stop_all_sensors();
        return;
    }

    // Stop giving that damn negative time, instead, make up a new time
    if(time_cast.toMSecsSinceEpoch() - currentTime.toMSecsSinceEpoch() >= 0)
        elapsedTime += time_cast.toMSecsSinceEpoch() -
                currentTime.toMSecsSinceEpoch(); // Add time since last sample to elapsed time
    else
        elapsedTime += get_sample_period(); // Just keep the ball rolling

    globalRawData.push_back(QVector<qint32>() << elapsedTime << data);
    currentTime = QDateTime::currentDateTime();
    if(get_conversion_flag())
        globalData.push_back(convert_immediate_data(
                                 globalRawData.at(globalRawData.size()-1)));
    emit raw_data_ready(get_data_raw());
}

/********************************************************************
 * Sensor Select                                                    *
 *******************************************************************/

void sensors::select_ads1015(){
    switch_sensor();    // Notify sensor change
    adcsensor = new ADS1015;    // Init sensor
    set_used_graphs(4); //Number of US connected
    set_sensor_type(ADC);
    connect(adcsensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
            this, SLOT(on_record_sensor(QDateTime,QVector<qint32>)));
    connect(this, SIGNAL(sample_period_update(quint16)), adcsensor,
            SLOT(program(qint16)));
}

void sensors::select_infrared(){
    switch_sensor();    // Notify sensor change
    set_used_graphs(1); //Number of IR connected
    set_sensor_type(INFRARED);  // Self explanitory
}

void sensors::select_light_sensor(){
    switch_sensor();    // Notify sensor change
    lightsensor = new LightSensor;  // Init sensor
    set_used_graphs(1); //Number of light connected
    set_sensor_type(LIGHT);
    connect(lightsensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
            this, SLOT(on_record_sensor(QDateTime,QVector<qint32>)));
    connect(this, SIGNAL(sample_period_update(quint16)), lightsensor,
            SLOT(program(quint16)));
}

void sensors::select_ls20031(){
    switch_sensor();    // Notify sensor change
    set_used_graphs(1); //Number of GPS connected
    set_sensor_type(GPS);   // Self explanitory
}

void sensors::select_lsm9ds0(){
    switch_sensor();    // Notify sensor change
    set_used_graphs(9); //Number of sensors on the 9DOF IMU
    set_sensor_type(NINEDOF);   // Self explanitory
}

void sensors::select_mpl3115a2(){
    switch_sensor();    // Notify sensor change
    set_used_graphs(1); //Number of altimiters connected
    set_sensor_type(ALTIMITER); // Self explanitory
}

void sensors::select_sudo_sensor(){
    switch_sensor();    // Notify sensor change
    fakesensor = new FakeSensor(mainwindow);    // Init sensor
    set_used_graphs(9); //Number of fake sensors connected
    set_sensor_type(FAKE);  // Self explanitory
    connect(fakesensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
            this,SLOT(on_record_sensor(QDateTime,QVector<qint32>)));
    timer->start(get_sample_period());  // Sample period
    connect(timer, SIGNAL(timeout()), fakesensor, SLOT(update()));
}

/********************************************************************
 * Helper Methods                                                   *
 *******************************************************************/

void sensors::clear_data(){
    globalRawData.resize(0);    // A vector of size 0 is empty (obviously)
    globalData.resize(0);   // A vector of size 0 is empty (obviously)
}

void sensors::convert_data(){
    stop_all_sensors(); // Since this will be converting all data, kill all ongoing actions
    globalData.resize(globalRawData.size());
    for(qint32 i = 0; i < globalRawData.size(); i++){
        globalData[i] = convert_immediate_data(globalRawData.at(i));
    }
}

QVector<float> sensors::convert_immediate_data(QVector<qint32> data){
    switch(get_sensor_type()){
    case LIGHT:
        break;
    case FAKE:
        break;
    case ADC:
        break;
    default:
        break;
    }
}

void sensors::stop_all_sensors(){
    if(timer->isActive())
        timer->stop();
    switch(get_sensor_type()){
    case LIGHT:
        disconnect(lightsensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
                   this, SLOT(on_record_sensor(QDateTime,QVector<qint32>)));
        disconnect(this, SIGNAL(sample_period_update(quint16)), lightsensor, SLOT(program(quint16)));
        delete lightsensor;
        set_sensor_type(NONE);
        break;
    case ADC:
        disconnect(adcsensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
                   this, SLOT(on_record_sensor(QDateTime,QVector<qint32>)));
        disconnect(this, SIGNAL(sample_period_update(quint16)), adcsensor, SLOT(program(quint16)));
        delete adcsensor;
        set_sensor_type(NONE);
        break;
    case FAKE:
        disconnect(fakesensor, SIGNAL(sensorData(QDateTime,QVector<qint32>)),
                   this,SLOT(on_record_sensor(QDateTime,QVector<qint32>)));
        disconnect(timer, SIGNAL(timeout()), fakesensor, SLOT(update()));
        if(fakesensor->isRunning())
            fakesensor->exit();
        while(fakesensor->isRunning());
        delete fakesensor;
        set_sensor_type(NONE);
        break;
    case NONE:
        break;
    default:
        emit device_error(QString("Invalid device: '%1'").arg(QString::number(get_sensor_type())));
        break;
    }
}

void sensors::switch_sensor(){
    elapsedTime = 0;    // Reset time
    stop_all_sensors(); // Make sure slate is clean
    currentTime = QDateTime::currentDateTime(); // Reset current time
}

/********************************************************************
 * Setters                                                          *
 *******************************************************************/

void sensors::set_device_id(char device_id){
    if(deviceID.contains(sensorType))
        deviceID.remove(sensorType);
    deviceID.insert(sensorType,device_id);
}

void sensors::set_device_name(QString device_name){
    if(deviceName.contains(sensorType))
        deviceID.remove(sensorType);
    deviceName.insert(sensorType, device_name);
}

void sensors::set_sample_period(const quint16 sample){
    samplePeriod = sample;
    if(sensorType == FAKE){
        if(timer->isActive())
            timer->stop();
        timer->start(samplePeriod);
    } else {
        emit sample_period_update(sample);
    }
}

void sensors::set_sensor_type(uchar sensor_type){
    sensorType = sensor_type;
    clear_data();   // Clean slate
}
