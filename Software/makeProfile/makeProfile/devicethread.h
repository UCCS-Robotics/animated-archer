#ifndef DEVICETHREAD_H
#define DEVICETHREAD_H

#include <QThread>

class DeviceConnection;

class DeviceThread : public QThread
{
    Q_OBJECT
public:
    explicit DeviceThread(QObject *parent = 0);

    static DeviceConnection* getConnection();

protected:
    virtual void run();

private:
    DeviceConnection *mConnection;
};

#endif // DEVICETHREAD_H
