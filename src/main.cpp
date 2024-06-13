#include <Arduino.h>
#include <WiFiManager.h>
#include <time.h>
#include "LedControl.h"

//
//    FILE: MINI WordClock
//  AUTHOR: Thomas KLapper
// PURPOSE: WordClock, using MAX 7219, 8x8 LED Matrix
//     URL: https://github.com/ThomasKlap/MINIWordClock
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin D2 is connected to the DataIn 
 pin D4 is connected to the CLK 
 pin D3 is connected to LOAD 
 We have only a single MAX72XX.
*/
LedControl lc=LedControl(D2,D4,D3,1);

int lastMilis;
int temp;
int secounds;
int minutes;
int hours;
unsigned long CycleMillis = 0; // speichert den Zeitpunkt des Letzten Zyklus
const char *NTP_SERVER = "de.pool.ntp.org";
const char *TZ_INFO = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";

char wochentage[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
String monat[12] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};

time_t now;
tm tm;

void matrix_start()
{
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}


void matrix_out()
{


if (secounds == 0) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Null");
}
else if (secounds == 1) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 15, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Eins");
}
else if (secounds == 2) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 3, 1);
    lc.setRow(5, 3, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Zwei");
}
else if (secounds == 3) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 240, 1);
    Serial.println("Drei");
}
else if (secounds == 4) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 240, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Vier");
}
else if (secounds == 5) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 240, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Fünfl");
}
else if (secounds == 6) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 248, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Sechs");
}
else if (secounds == 7) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 126, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Sieben");
}
else if (secounds == 8) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 15, 1);
    Serial.println("Acht");
}
else if (secounds == 9) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 240, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Neun");
}
else if (secounds == 10) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 30, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Zehn");
}
else if (secounds == 11) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 0, 1);
    lc.setRow(5, 1, 1);
    lc.setRow(6, 1, 1);
    lc.setRow(7, 1, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Elf");
}
else if (secounds == 12) {
    lc.setRow(1, 0, 1);
    lc.setRow(2, 0, 1);
    lc.setRow(3, 0, 1);
    lc.setRow(4, 31, 1);
    lc.setRow(5, 0, 1);
    lc.setRow(6, 0, 1);
    lc.setRow(7, 0, 1);
    lc.setRow(8, 0, 1);
    Serial.println("Zwölf");
}
else { Serial.println("Mehr als Zwölf");}
};


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

matrix_start();
 }


void loop()
{
  time(&now);             // Liest die aktuelle Zeit
  localtime_r(&now, &tm); // Beschreibt tm mit der aktuelle Zeit
  // Serial.printf("%02d-%02d-%04d \t", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  // Serial.printf("%02d %s %04d \t", tm.tm_mday, monat[tm.tm_mon], tm.tm_year + 1900);  // Monat ausgeschrieben

  // Serial.print(wochentage[tm.tm_wday]);
  // Serial.print(tm.tm_wday);         // Wochentag als Zahl, 0 = Sonntag
  //Serial.print("\tder ");
  //Serial.print(tm.tm_mday);
  //Serial.print(" " + monat[tm.tm_mon] + " ");
  //Serial.print(tm.tm_year + 1900);

  //Serial.printf(" \tUhrzeit: %02d:%02d:%02d \n", tm.tm_hour, tm.tm_min, tm.tm_sec);
  secounds =  tm.tm_sec;
  Serial.println(tm.tm_sec);
  Serial.println(secounds);
    delay(100);
    matrix_out();
} 

//  -- END OF FILE --