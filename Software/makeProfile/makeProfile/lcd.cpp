#include "lcd.h"
#include "i2c.h"

#include <cstring>

void lcdSendCommand(uint8_t cmd)
{
	uint8_t cmdData[2] = { LCD_PREFIX, cmd };

	i2cWrite(LCD_ADDR, cmdData, 2);
}

void lcdSendString(const char *str)
{
	i2cWrite(LCD_ADDR, (uint8_t*)str, strlen(str));
}
