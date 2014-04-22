#include <i2c_t3.h>

#define I2C_CMD_READ  ('R')
#define I2C_CMD_WRITE ('W')

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{        
  if(Serial.available() > 0)
  {
    switch(Serial.read())
    {
      case I2C_CMD_READ:
      {
        uint8_t addr = Serial.read();
        uint8_t sz = Serial.read();
        Wire.requestFrom(addr, (size_t)sz);
        if(Wire.available() < sz)
        {
          while(sz--)
            Serial.println(0, HEX);
        }
        else
        {
          while(sz--)
            Serial.println(Wire.receive(), HEX);
        }
        break;
      }
      case I2C_CMD_WRITE:
      {
        uint8_t addr = Serial.read();
        uint8_t sz = Serial.read();
        Wire.beginTransmission(addr);
        while(sz--)
          Wire.send(Serial.read());
        Wire.endTransmission();
        break;
      }
      default:
      {
        break;
      }
    }
  }
}

