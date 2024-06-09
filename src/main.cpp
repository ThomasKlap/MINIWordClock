#include <Arduino.h>
#include "MATRIX7219.h"
#include <ESP8266WiFi.h>
#include <WiFiManager.h> //WIFI Manager and Accespoint
#include <time.h>                       // time() ctime()
#include <TimeLib.h> 
#include <TZ.h> // aditional for DST 
//
//    FILE: MINI WordClock
//  AUTHOR: Thomas KLapper
// PURPOSE: WordClock, using MAX 7219, 8x8 LED Matrix
//     URL: https://github.com/ThomasKlap/MINIWordClock

extern "C" int clock_gettime(clockid_t unused, struct timespec *tp); // this line is necessary for first TimeGet
static time_t now2; // An object which can store a time

uint8_t dataPin   = D2;
uint8_t selectPin = D3;
uint8_t clockPin  = D4;
uint8_t count     = 1;
int sekunden = 45 ;
int minuten = 24 ;
int stunden = 14 ;
#define MYTZ TZ_Europe_Berlin // set timezone
MATRIX7219 mx(dataPin, selectPin, clockPin, count);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MATRIX7219_LIB_VERSION: ");
  Serial.println(MATRIX7219_LIB_VERSION);
  Serial.println();

  // start network with WiFi-Manager
  WiFiManager wifiManager; // wifi configuration wizard
  wifiManager.autoConnect("BIG7_Clock", "12345678"); // configuration for the access point, set your own secret.
  // This is where your time zone is set
 
  configTime(MYTZ, "pool.ntp.org");
  setTime(19,06,00,28,11,2023);

  mx.begin();
  mx.clear();
  mx.setBrightness(10);
  mx.setReverse(true);

 

}


void loop()
{

  now2 = time(nullptr);      // Updates the 'now2' variable to the current time value
  //convert to simple values for shift-out
  stunden = (localtime(&now2)->tm_hour);
  minuten = (localtime(&now2)->tm_min);
  sekunden = (localtime(&now2)->tm_sec);
 
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