#include <Arduino.h>
#include <MATRIX7219.h>
#include <WiFiManager.h>
#include <time.h>
#include <matrix.h>

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

int lastMilis;
int temp;
unsigned long CycleMillis = 0; // speichert den Zeitpunkt des Letzten Zyklus
const char *NTP_SERVER = "de.pool.ntp.org";
const char *TZ_INFO = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";

char wochentage[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
String monat[12] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};

time_t now;
tm tm;




void setup()
{
  Serial.begin(115200);
  
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("MiniWordClock", "123456789"); // password protected ap
  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  configTime(0, 0, NTP_SERVER);
  setenv("TZ", TZ_INFO, 1);

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
 
  
   time(&now);             // Liest die aktuelle Zeit
  localtime_r(&now, &tm); // Beschreibt tm mit der aktuelle Zeit
  Serial.printf("%02d-%02d-%04d \t", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  // Serial.printf("%02d %s %04d \t", tm.tm_mday, monat[tm.tm_mon], tm.tm_year + 1900);  // Monat ausgeschrieben

  Serial.print(wochentage[tm.tm_wday]);
  // Serial.print(tm.tm_wday);         // Wochentag als Zahl, 0 = Sonntag
  Serial.print("\tder ");
  Serial.print(tm.tm_mday);
  Serial.print(" " + monat[tm.tm_mon] + " ");
  Serial.print(tm.tm_year + 1900);

  Serial.printf(" \tUhrzeit: %02d:%02d:%02d \n", tm.tm_hour, tm.tm_min, tm.tm_sec);


    delay(100);
    mx.displayOff();
    delay(100);
    mx.displayOn();
} 

//  -- END OF FILE --