#ifndef DEVICE_H
#define DEVICE_H

#include <QDialog>
#include "lcd.h"

#define CONVERT 0
#define RAW 1

namespace Ui {
class Device;
}

class Device : public QDialog
{
    Q_OBJECT

public:
    explicit Device(QWidget *parent = 0);
    ~Device();
    void write_LCD(QString);
private:

signals:
    void finishedRead(char);

private slots:
    void on_write(QString);
    void on_read();

private:
    Ui::Device *ui;
    bool convertState;
};

#endif // DEVICE_H
