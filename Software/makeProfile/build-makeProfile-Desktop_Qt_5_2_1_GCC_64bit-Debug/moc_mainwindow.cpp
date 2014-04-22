/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../makeProfile/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata[453];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 22),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 22),
QT_MOC_LITERAL(4, 58, 30),
QT_MOC_LITERAL(5, 89, 22),
QT_MOC_LITERAL(6, 112, 28),
QT_MOC_LITERAL(7, 141, 32),
QT_MOC_LITERAL(8, 174, 28),
QT_MOC_LITERAL(9, 203, 22),
QT_MOC_LITERAL(10, 226, 26),
QT_MOC_LITERAL(11, 253, 28),
QT_MOC_LITERAL(12, 282, 28),
QT_MOC_LITERAL(13, 311, 19),
QT_MOC_LITERAL(14, 331, 23),
QT_MOC_LITERAL(15, 355, 33),
QT_MOC_LITERAL(16, 389, 14),
QT_MOC_LITERAL(17, 404, 15),
QT_MOC_LITERAL(18, 420, 22),
QT_MOC_LITERAL(19, 443, 8)
    },
    "MainWindow\0on_radioSample_clicked\0\0"
    "on_radioFilter_clicked\0"
    "on_radioRunningAverage_clicked\0"
    "on_radioKalman_clicked\0"
    "on_actionUS_Sensor_triggered\0"
    "on_actionAccelerometer_triggered\0"
    "on_actionGyroscope_triggered\0"
    "on_actionGPS_triggered\0"
    "on_actionCompass_triggered\0"
    "on_actionAltimiter_triggered\0"
    "on_actionIR_Sensor_triggered\0"
    "on_radioRaw_clicked\0on_radioConvert_clicked\0"
    "on_actionConnect_Device_triggered\0"
    "on_updateChart\0processOneThing\0"
    "processLightSensorData\0uint16_t\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08,
       3,    0,  100,    2, 0x08,
       4,    0,  101,    2, 0x08,
       5,    0,  102,    2, 0x08,
       6,    0,  103,    2, 0x08,
       7,    0,  104,    2, 0x08,
       8,    0,  105,    2, 0x08,
       9,    0,  106,    2, 0x08,
      10,    0,  107,    2, 0x08,
      11,    0,  108,    2, 0x08,
      12,    0,  109,    2, 0x08,
      13,    0,  110,    2, 0x08,
      14,    0,  111,    2, 0x08,
      15,    0,  112,    2, 0x08,
      16,    1,  113,    2, 0x08,
      17,    0,  116,    2, 0x08,
      18,    1,  117,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_radioSample_clicked(); break;
        case 1: _t->on_radioFilter_clicked(); break;
        case 2: _t->on_radioRunningAverage_clicked(); break;
        case 3: _t->on_radioKalman_clicked(); break;
        case 4: _t->on_actionUS_Sensor_triggered(); break;
        case 5: _t->on_actionAccelerometer_triggered(); break;
        case 6: _t->on_actionGyroscope_triggered(); break;
        case 7: _t->on_actionGPS_triggered(); break;
        case 8: _t->on_actionCompass_triggered(); break;
        case 9: _t->on_actionAltimiter_triggered(); break;
        case 10: _t->on_actionIR_Sensor_triggered(); break;
        case 11: _t->on_radioRaw_clicked(); break;
        case 12: _t->on_radioConvert_clicked(); break;
        case 13: _t->on_actionConnect_Device_triggered(); break;
        case 14: _t->on_updateChart((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->processOneThing(); break;
        case 16: _t->processLightSensorData((*reinterpret_cast< uint16_t(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
