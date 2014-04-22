#include "Sensor.h"
#include "lcd.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Sensor sensor;

	lcdSendCommand(LCD_CLEAR);
	lcdSendString("Test text!!!");

	return app.exec();
}
