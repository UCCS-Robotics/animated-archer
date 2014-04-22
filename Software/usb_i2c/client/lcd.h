#ifndef __lcd_h__
#define __lcd_h__

#include <stdint.h>

// I2C Slave Address of the LCD
#define LCD_ADDR          (0x28)

#define LCD_PREFIX        (0xFE)
#define LCD_ON            (0x41)
#define LCD_OFF           (0x42)
#define LCD_SETCUR        (0x45)
#define LCD_HOME          (0x46)
#define LCD_UNDERLINE_ON  (0x47)
#define LCD_UNDERLINE_OFF (0x48)
#define LCD_CURSOR_LEFT   (0x49)
#define LCD_CURSOR_RIGHT  (0x4A)
#define LCD_BLINK_ON      (0x4B)
#define LCD_BLINK_OFF     (0x4C)
#define LCD_BACKSPACE     (0x4E)
#define LCD_CLEAR         (0x51)
#define LCD_CONTRAST      (0x52)
#define LCD_BACKLIGHT     (0x53)
#define LCD_CUSTOMCHAR    (0x54)
#define LCD_DISPLAY_LEFT  (0x55)
#define LCD_DISPLAY_RIGHT (0x56)
#define LCD_VER           (0x70)

void lcdSendCommand(uint8_t cmd);
void lcdSendString(const char *str);

#endif // __lcd_h__
