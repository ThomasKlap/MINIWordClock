# MINI-Word Clock, by Thomas Klapper

WordClock, german language using Wemos D1 mini and MAX7219 driven 8x8 LED Dot-Matrix
-WLAN AP configuration portal
-automatic NTP Time syn after succesfull WLAN connection

Connect LED Module as follwowing:
    VCC -> 5V
    GND -> GND
    DIN -> D6
    CLK -> D7
    CS  -> D8


## ChangeLog

20240615: changing basics from MAX7219 to LedControl libary
20240617: changing text selection and split masseges, minutes first, then full hours; 
        reason ist to use separate control of each digit to provide overlaping "halb" and "vier" in the same row
