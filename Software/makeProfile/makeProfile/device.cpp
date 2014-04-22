#include "device.h"
#include "ui_device.h"


Device::Device(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Device)
{
    ui->setupUi(this);
}

Device::~Device()
{
    delete ui;
}

void Device::on_read(){
    char ByteRead;
    // Read byte from USB, save into ByteRead
    emit finished(ByteRead);
}

void Device::write_LCD(QString stringer){
    QByteArray ba = stringer.toLocal8Bit();
    const char *c_str2 = ba.data();
    lcdSendCommand(LCD_HOME);
    lcdSendString(c_str2);
}

void Device::on_write(QString WriteByte){
    // Write WriteByte to USB device

}
