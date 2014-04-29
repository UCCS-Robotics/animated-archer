#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T23:13:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = makeProfile
TEMPLATE = app
LIBS += -lusb


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    device.cpp \
    LightSensor.cpp \
    sensorthread.cpp \
    deviceconnection.cpp \
    hid.c \
    crc32.c \
    devicethread.cpp \
    devicetransaction.cpp \
    fakesensor.cpp \
    burstprogram.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    device.h \
    LightSensor.h \
    sensorthread.h \
    deviceconnection.h \
    hid.h \
    crc32.h \
    devicethread.h \
    devicetransaction.h \
    fakesensor.h /
    burstprogram.h

FORMS    += mainwindow.ui
