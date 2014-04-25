#include "devicethread.h"
#include "deviceconnection.h"

static DeviceThread *g_device_thread_inst = 0;

DeviceThread::DeviceThread(QObject *parent) :
    QThread(parent), mConnection(0)
{
}

DeviceConnection* DeviceThread::getConnection()
{
    if(!g_device_thread_inst)
    {
        g_device_thread_inst = new DeviceThread;
        g_device_thread_inst->start();

        // Wait for the device connection the be made.
        while(!g_device_thread_inst->mConnection);
    }

    return g_device_thread_inst->mConnection;
}

void DeviceThread::run()
{
    // Create the device connection.
    mConnection = new DeviceConnection;

    // Run the thread.
    exec();
}
