#ifndef FAKESENSOR_H
#define FAKESENSOR_H

#include <QThread>
class MainWindow;

class FakeSensor : public QThread
{
    Q_OBJECT
public:
    explicit FakeSensor(MainWindow *,QObject *parent = 0);

signals:
    void fakeSensorOutput(quint16);
public slots:
    void update();
private:
    void run();
    MainWindow *mainwindow;

};

#endif // FAKESENSOR_H
