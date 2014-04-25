#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T23:13:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = makeProfile
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    device.cpp \
    i2c.cpp \
    lcd.cpp \
    LightSensor.cpp \
    sensorthread.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    device.h \
    i2c.h \
    lcd.h \
    LightSensor.h \
    sensorthread.h

FORMS    += mainwindow.ui \
    device.ui
