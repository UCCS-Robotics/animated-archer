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
<<<<<<< HEAD
    fakesensor.cpp
=======
    burstprogram.cpp
>>>>>>> cd76d846993eebd419134ab171803f63da060a0b

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
<<<<<<< HEAD
    fakesensor.h
=======
    burstprogram.h
>>>>>>> cd76d846993eebd419134ab171803f63da060a0b

FORMS    += mainwindow.ui

LIBS += -lusb-1.0
