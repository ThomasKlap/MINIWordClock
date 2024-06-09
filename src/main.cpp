#include <Arduino.h>
//
//    FILE: MATRIX7219_VU_METER.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MATRIX7219 8x8 LED MATRIX MAX7219
//     URL: https://github.com/RobTillaart/MATRIX7219


#include "MATRIX7219.h"

uint8_t dataPin   = D2;
uint8_t selectPin = D3;
uint8_t clockPin  = D4;
uint8_t count     = 1;

MATRIX7219 mx(dataPin, selectPin, clockPin, count);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MATRIX7219_LIB_VERSION: ");
  Serial.println(MATRIX7219_LIB_VERSION);
  Serial.println();

  mx.begin();
  mx.clear();
  mx.setBrightness(3);
  mx.setReverse(true);
}


void loop()
{
 
    mx.setRow(1, 1, 1);
    mx.setRow(2, 2, 1);
    mx.setRow(3, 3, 1);
    mx.setRow(4, 4, 1);
    mx.setRow(5, 5, 1);
    mx.setRow(6, 6, 1);
    mx.setRow(7, 7, 1);
    mx.setRow(8, 8, 1);
    Serial.println("BILD ");
    delay(100);
    mx.displayOff();
    delay(100);
    mx.displayOn();
} 

//  -- END OF FILE --