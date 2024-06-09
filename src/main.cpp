#include <Arduino.h>
#include "MATRIX7219.h"

//
//    FILE: MINI WordClock
//  AUTHOR: Thomas KLapper
// PURPOSE: WordClock, using MAX 7219, 8x8 LED Matrix
//     URL: https://github.com/ThomasKlap/MINIWordClock

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
  mx.setBrightness(10);
  mx.setReverse(true);
 }


void loop()
{
    mx.setRow(1, 15, 1);
    mx.setRow(2, 240, 1);
    mx.setRow(3, 255, 1);
    mx.setRow(4, 14, 1);
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