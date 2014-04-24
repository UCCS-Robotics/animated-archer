#ifndef ACCELSENSOR_H
#define ACCELSENSOR_H

#include <QObject>

class AccelSensor : public QObject
{
    Q_OBJECT
public:
    explicit AccelSensor(QObject *parent = 0);

private slots:
    void updateSensor();

signals:
    void sentLightSensorData(quint16);

private:
    void enable();
    void disable();

    uint16_t read16(uint8_t reg);
    void write8(uint8_t reg, uint8_t value);

    QTextEdit *mEditor;
    QTimer mTimer;

};

#endif // ACCELSENSOR_H
