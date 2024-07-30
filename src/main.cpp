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


LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
// LedControl lc=LedControl(D6,D8,D7,1);
int lastMilis;
int temp;
int secounds;
int minutes;
int hours;
int temp_hours;
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
  lc.setIntensity(0,4);
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

void text_fuenf1() {
  lc.setLed(0, 0, 0, 1);
  lc.setLed(0, 0, 1, 1);
  lc.setLed(0, 0, 2, 1);
  lc.setLed(0, 0, 3, 1);
  Serial.print(" Fünf ");  
}
void text_zehn1() {
  lc.setLed(0, 0, 4, 1);
  lc.setLed(0, 0, 5, 1);
  lc.setLed(0, 0, 6, 1);
  lc.setLed(0, 0, 7, 1);
  Serial.print(" Zehn ");  
}
void text_vor() {
  lc.setLed(0, 1, 0, 1);
  lc.setLed(0, 1, 1, 1);
  lc.setLed(0, 1, 2, 1);
  Serial.print(" vor ");  
}
void text_nach() {
  lc.setLed(0, 1, 4, 1);
  lc.setLed(0, 1, 5, 1);
  lc.setLed(0, 1, 6, 1);
  lc.setLed(0, 1, 7, 1);
  Serial.print(" nach "); 
}
void text_halb() {
  lc.setLed(0, 2, 0, 1);
  lc.setLed(0, 2, 1, 1);
  lc.setLed(0, 2, 2, 1);
  lc.setLed(0, 2, 3, 1);
  Serial.print(" halb "); 
}
void text_eins() {
  lc.setLed(0, 4, 0, 1);
  lc.setLed(0, 4, 1, 1);
  lc.setLed(0, 4, 2, 1);
  lc.setLed(0, 4, 3, 1);
  Serial.print(" Eins "); 
}
void text_zwei() {
  lc.setLed(0, 3, 0, 1);
  lc.setLed(0, 3, 1, 1);
  lc.setLed(0, 4, 0, 1);
  lc.setLed(0, 4, 1, 1);
  Serial.print(" Zwei "); 
}
void text_drei() {
  lc.setLed(0, 7, 4, 1);
  lc.setLed(0, 7, 5, 1);
  lc.setLed(0, 7, 6, 1);
  lc.setLed(0, 7, 7, 1);
  Serial.print(" Drei "); 
}
void text_vier() {
  lc.setLed(0, 2, 4, 1);
  lc.setLed(0, 2, 5, 1);
  lc.setLed(0, 2, 6, 1);
  lc.setLed(0, 2, 7, 1);
  Serial.print(" Vier "); 
}
void text_fuenf() {
  lc.setLed(0, 3, 4, 1);
  lc.setLed(0, 3, 5, 1);
  lc.setLed(0, 3, 6, 1);
  lc.setLed(0, 3, 7, 1);
  Serial.print(" Fünf "); 
}
void text_sechs() {
  lc.setLed(0, 4, 3, 1);
  lc.setLed(0, 4, 4, 1);
  lc.setLed(0, 4, 5, 1);
  lc.setLed(0, 4, 6, 1);
  lc.setLed(0, 4, 7, 1);
  Serial.print(" Sechs "); 
}
void text_sieben() {
  lc.setLed(0, 6, 1, 1);
  lc.setLed(0, 6, 2, 1);
  lc.setLed(0, 6, 3, 1);
  lc.setLed(0, 6, 4, 1);
  lc.setLed(0, 6, 5, 1);
  lc.setLed(0, 6, 6, 1);
  Serial.print(" Sieben "); 
}
void text_acht() {
  lc.setLed(0, 7, 0, 1);
  lc.setLed(0, 7, 1, 1);
  lc.setLed(0, 7, 2, 1);
  lc.setLed(0, 7, 3, 1);
  Serial.print(" Acht "); 
}
void text_neun() {
  lc.setLed(0, 5, 4, 1);
  lc.setLed(0, 5, 5, 1);
  lc.setLed(0, 5, 6, 1);
  lc.setLed(0, 5, 7, 1);
  Serial.print(" Neun "); 
}
void text_zehn() {
  lc.setLed(0, 5, 1, 1);
  lc.setLed(0, 5, 2, 1);
  lc.setLed(0, 5, 3, 1);
  lc.setLed(0, 5, 4, 1);
  Serial.print(" Zehn "); 
}
void text_elf() {
  lc.setLed(0, 4, 0, 1);
  lc.setLed(0, 5, 0, 1);
  lc.setLed(0, 6, 0, 1);
  Serial.print(" Elf "); 
}
void text_zwoelf() {
  lc.setLed(0, 3, 1, 1);
  lc.setLed(0, 3, 2, 1);
  lc.setLed(0, 3, 3, 1);
  lc.setLed(0, 3, 4, 1);
  lc.setLed(0, 3, 5, 1);
  Serial.print(" Zwölf "); 
}   

void matrix_out() {
    lc.clearDisplay(0); // clear all pixels

    if ((minutes >= 3 && minutes < 8) || (minutes >= 33 && minutes < 38)) {
    text_fuenf1();
    text_nach();
  } else if ((minutes >= 8 && minutes < 13) || (minutes >= 38 && minutes < 43)) {
    text_zehn1();
    text_nach();
  } else if (minutes >= 13 && minutes < 18) {
    text_fuenf1();
    text_zehn1();
    text_nach();
  } else if (minutes >= 43 && minutes < 48) {
    text_fuenf1();
    text_zehn1();
    text_vor();
  } else if ((minutes >= 23 && minutes < 28) || (minutes >= 53&& minutes < 58)) {
    text_fuenf1();
    text_vor();
  } else if ((minutes >= 48 && minutes < 53) || (minutes >= 18 && minutes < 23)) {
    text_zehn1();
    text_vor();
  }
  
  if (minutes >= 18 && minutes < 43) {
    text_halb();
  }

  if (minutes<18){
    temp_hours=hours;
  } else {
    temp_hours=hours+1;
  }
      switch (temp_hours) {
      case 0:
      case 12:
        text_zwoelf();
        break;
      case 1:
        text_eins();
        break;
      case 2:
        text_zwei();
        break;
      case 3:
        text_drei();
        break;
      case 4:
        text_vier();
        break;
      case 5:
        text_fuenf();
        break;
      case 6:
        text_sechs();
        break;
      case 7:
        text_sieben();
        break;
      case 8:
        text_acht();
        break;
      case 9:
        text_neun();
        break;
      case 10:
        text_zehn();
        break;
      case 11:
        text_elf();
        break;
    }

  }

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