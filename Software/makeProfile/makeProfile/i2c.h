#ifndef __i2c_h__
#define __i2c_h__

#include <stdint.h>

void i2cWriteSingle(uint8_t addr, uint8_t byte);
void i2cWrite(uint8_t addr, const uint8_t *data, uint8_t sz);

uint8_t i2cReadSingle(uint8_t addr);
void i2cRead(uint8_t addr, uint8_t *data, uint8_t sz);

#endif // __i2c_h__
