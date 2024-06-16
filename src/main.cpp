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
 pin D2/GPIO4 is connected to the DataIn 
 pin D4/GPIO2 is connected to the CLK 
 pin D3/GPIO0 is connected to LOAD 
 We have only a single MAX72XX.
*/

#define DIN_PIN D6  //pin D8
#define CS_PIN  D7  //pin D7
#define CLK_PIN D8  //pin D6


// LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
LedControl lc=LedControl(D6,D7,D8,1);
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
  lc.setRow(0,0,B10101010); 
  lc.setRow(0,1,B01010101);
  lc.setRow(0,2,B10101010); 
  lc.setRow(0,3,B01010101);
  lc.setRow(0,4,B10101010); 
  lc.setRow(0,5,B01010101);
  lc.setRow(0,6,B10101010); 
  lc.setRow(0,7,B01010101);
  delay(200);
  lc.setRow(0,0,B01010101);
  lc.setRow(0,1,B10101010); 
  lc.setRow(0,2,B01010101);
  lc.setRow(0,3,B10101010); 
  lc.setRow(0,4,B01010101);
  lc.setRow(0,5,B10101010); 
  lc.setRow(0,6,B01010101);
  lc.setRow(0,7,B10101010);
  delay(200); 
  lc.setRow(0,0,B10101010); 
  lc.setRow(0,1,B01010101);
  lc.setRow(0,2,B10101010); 
  lc.setRow(0,3,B01010101);
  lc.setRow(0,4,B10101010); 
  lc.setRow(0,5,B01010101);
  lc.setRow(0,6,B10101010); 
  lc.setRow(0,7,B01010101);
  delay(200);
  lc.setRow(0,0,B01010101);
  lc.setRow(0,1,B10101010); 
  lc.setRow(0,2,B01010101);
  lc.setRow(0,3,B10101010); 
  lc.setRow(0,4,B01010101);
  lc.setRow(0,5,B10101010); 
  lc.setRow(0,6,B01010101);
  lc.setRow(0,7,B10101010);
  delay(200); 
  lc.clearDisplay(0);
}


void matrix_out()
{


if (hours == 0) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B11110000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Null");
}
else if (hours == 1) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B11110000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Eins");
}
else if (hours == 2) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B11000000);
    lc.setRow(0,4,B11000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Zwei");
}
else if (hours == 3) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00001111);
    Serial.println("Drei");
}
else if (hours == 4) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00001111);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Vier");
}
else if (hours == 5) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00001111);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Fünfl");
}
else if (hours == 6) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B00011111);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Sechs");
}
else if (hours == 7) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B01111110);
    lc.setRow(0,7,B00000000);
    Serial.println("Sieben");
}
else if (hours == 8) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B11110000);
    Serial.println("Acht");
}
else if (hours == 9) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00001111);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Neun");
}
else if (hours == 10) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B01111000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Zehn");
}
else if (hours == 11) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B00000000);
    lc.setRow(0,4,B10000000);
    lc.setRow(0,5,B10000000);
    lc.setRow(0,6,B10000000);
    lc.setRow(0,7,B00000000);
    Serial.println("Elf");
}
else if (hours == 12) {
    lc.setRow(0,0,B00000000);
    lc.setRow(0,1,B00000000);
    lc.setRow(0,2,B00000000);
    lc.setRow(0,3,B11110000);
    lc.setRow(0,4,B00000000);
    lc.setRow(0,5,B00000000);
    lc.setRow(0,6,B00000000);
    lc.setRow(0,7,B00000000);
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
  matrix_start(); // start the LED Matrix Driver and run test-screens
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
  minutes =  tm.tm_min;
  hours =  tm.tm_hour ;
  if (hours>=12) hours-=12;

  Serial.print(tm.tm_hour);
  Serial.print(" : ");
  Serial.print(tm.tm_min);
  Serial.print(" : ");  
  Serial.println(tm.tm_sec);
    delay(500);
    matrix_out();
} 

//  -- END OF FILE --