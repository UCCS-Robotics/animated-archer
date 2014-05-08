#ifndef FAKESENSOR_H
#define FAKESENSOR_H

#include <QThread>
#include <QtCore/QDateTime>
#include <stdint.h>

class MainWindow;

class FakeSensor : public QThread
{
    Q_OBJECT
public:
    explicit FakeSensor(MainWindow *,QObject *parent = 0);

signals:
    void sensorData(const QVector<float> &data);
public slots:
    void update();
private:
    void run();
    uint32_t mFirstStamp;
    QDateTime mConnectTime;
    MainWindow *mainwindow;

};

#endif // FAKESENSOR_H
