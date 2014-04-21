#ifndef DEVICE_H
#define DEVICE_H

#include <QDialog>
#include<libusb-1.0/libusb.h>

namespace Ui {
class Device;
}

class Device : public QDialog
{
    Q_OBJECT

public:
    explicit Device(QWidget *parent = 0);
    ~Device();
    int identify();
private:
    void printdev(libusb_device *dev);

private:
    Ui::Device *ui;
};

#endif // DEVICE_H
