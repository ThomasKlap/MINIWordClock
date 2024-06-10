
#include <Wire.h>
unsigned char displaybuffer[8] = {};

#define MAX7219_CS 13
#define MAX7219_CLK 14
#define MAX7219_DAT 12


unsigned char i2cbuffer[20] = {};
unsigned char i2cbuffer_last[20] = {};
#define RTC_I2C_ADDRESS 0x68

void setup(void)
{
  Wire.begin();
  //Power
  pinMode(8, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(9, OUTPUT);

  //Max7219
  digitalWrite(MAX7219_CS, HIGH);
  pinMode(MAX7219_CS, OUTPUT);
  pinMode(MAX7219_CLK, OUTPUT);
  pinMode(MAX7219_DAT, OUTPUT);

  //Init all displays on bus with same settings
  for (int _k = 0; _k < 1; _k++) {
    SPI_transmit(0x0C, 0x01, 1); //Shutdown off (turn on)
    SPI_transmit(0x0A, 0x0F, 1); //Intensity
    SPI_transmit(0x0B, 0x07, 1); //Scan limit on 8 digits (max)
    SPI_transmit(0x0F, 0x00, 1); //No test mode (normal operation)
    SPI_transmit(0x09, 0x00, 1); //No decode on all digits (pixel mode)
  }
  clearDisplay();
  updateDisplay();
  testDisplay();

   //CLOCK SET, RUN ONCE ONLY, THEN COMMENT OUT
  /*
    Wire.beginTransmission(RTC_I2C_ADDRESS);
    Wire.write((uint8_t)0x00); //Point to 0x00 (time)
    Wire.write((uint8_t)0x00); //Seconds
    Wire.write((uint8_t)0x29); //Minutes
    Wire.write((uint8_t)0x19); //Hours
    Wire.endTransmission();

    /*
    Wire.beginTransmission(RTC_I2C_ADDRESS);
    Wire.write((uint8_t)0x03); //Point to 0x03 (date)
    Wire.write((uint8_t)0x03); //Weekday
    Wire.write((uint8_t)0x17); //Day
    Wire.write((uint8_t)0x05); //Month
    Wire.write((uint8_t)0x18); //Year
    Wire.endTransmission();
  */
}
int minutes=0;
int hours=0;
unsigned char blinker=0;
  int temp_hours;
void loop(void)
{

  //Set up RTC by pointing to address 0x00
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();

  //Read 6 bytes from RTC
  Wire.requestFrom(RTC_I2C_ADDRESS, 7);
  for (int _i = 0; _i < 7; _i++) {
    i2cbuffer[_i] = Wire.read();
  }


  hours=(((i2cbuffer[2] & 0xF0) >> 4) * 10) + (i2cbuffer[2] & 0x0F);
  if (hours>=12) hours-=12;
  minutes=(((i2cbuffer[1] & 0xF0) >> 4) * 10) + (i2cbuffer[1] & 0x0F);
  
  
  delay(500);

  
  clearDisplay();
  //setPixel(7,1,blinker);
  blinker^=0x01;
  
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

  updateDisplay();
}

void SPI_transmit(unsigned char _addr, unsigned char _data, unsigned char _mode) {
  if (_mode) {
    digitalWrite(MAX7219_CS, LOW);
  }
  for (int _i = 7; _i >= 0; _i--) {

    digitalWrite(MAX7219_CLK, LOW);
    digitalWrite(MAX7219_DAT, (_addr & (1 << _i)));
    digitalWrite(MAX7219_CLK, HIGH);
  }
  for (int _i = 7; _i >= 0; _i--) {

    digitalWrite(MAX7219_CLK, LOW);
    digitalWrite(MAX7219_DAT, (_data & (1 << _i)));
    digitalWrite(MAX7219_CLK, HIGH);
  }
  digitalWrite(MAX7219_CLK, LOW);

  if (_mode) {
    digitalWrite(MAX7219_CS, HIGH);
  }
}

void updateDisplay() {
  for (int _a = 0; _a < 8; _a++) {
    digitalWrite(MAX7219_CS, LOW);
    SPI_transmit((_a + 1), displaybuffer[_a], 0);
    digitalWrite(MAX7219_CS, HIGH);
  }
}

void setPixel(unsigned char _x, unsigned char _y, unsigned char _colour) {
  if (_colour) {
    displaybuffer[(_y) + (_x / 8)] |= (128 >> (_x % 8));
  } else {
    displaybuffer[(_y) + (_x / 8)] &=  ~(128 >> (_x % 8));
  }
}
void clearDisplay() {
  for (int _a = 0; _a < 8; _a++) {
    displaybuffer[_a] = 0;
  }
}

void text_fuenf1() {
  setPixel(0, 0, 1);
  setPixel(1, 0, 1);
  setPixel(2, 0, 1);
  setPixel(3, 0, 1);
}
void text_zehn1() {
  setPixel(4, 0, 1);
  setPixel(5, 0, 1);
  setPixel(6, 0, 1);
  setPixel(7, 0, 1);
}
void text_vor() {
  setPixel(0, 1, 1);
  setPixel(1, 1, 1);
  setPixel(2, 1, 1);
}
void text_nach() {
  setPixel(3, 1, 1);
  setPixel(4, 1, 1);
  setPixel(5, 1, 1);
  setPixel(6, 1, 1);
}
void text_halb() {
  setPixel(0, 2, 1);
  setPixel(1, 2, 1);
  setPixel(2, 2, 1);
  setPixel(3, 2, 1);
}
void text_eins() {
  setPixel(0, 3, 1);
  setPixel(1, 3, 1);
  setPixel(2, 3, 1);
  setPixel(3, 3, 1);
}
void text_zwei() {
  setPixel(3, 4, 1);
  setPixel(4, 4, 1);
  setPixel(5, 5, 1);
  setPixel(6, 5, 1);
}
void text_drei() {
  setPixel(3, 5, 1);
  setPixel(4, 5, 1);
  setPixel(5, 5, 1);
  setPixel(6, 5, 1);
}
void text_vier() {
  setPixel(4, 2, 1);
  setPixel(5, 2, 1);
  setPixel(6, 2, 1);
  setPixel(7, 2, 1);
}
void text_fuenf() {
  setPixel(7, 4, 1);
  setPixel(7, 5, 1);
  setPixel(7, 6, 1);
  setPixel(7, 7, 1);
}
void text_sechs() {
  setPixel(3, 3, 1);
  setPixel(4, 3, 1);
  setPixel(5, 3, 1);
  setPixel(6, 3, 1);
  setPixel(7, 3, 1);
}
void text_sieben() {
  setPixel(0, 4, 1);
  setPixel(1, 4, 1);
  setPixel(2, 4, 1);
  setPixel(0, 5, 1);
  setPixel(1, 5, 1);
  setPixel(2, 5, 1);
}
void text_acht() {
  setPixel(0, 7, 1);
  setPixel(1, 7, 1);
  setPixel(2, 7, 1);
  setPixel(3, 7, 1);
}
void text_neun() {
  setPixel(4, 6, 1);
  setPixel(5, 6, 1);
  setPixel(6, 6, 1);
  setPixel(7, 6, 1);
}
void text_zehn() {
  setPixel(1, 6, 1);
  setPixel(2, 6, 1);
  setPixel(3, 6, 1);
  setPixel(4, 6, 1);
}
void text_elf() {
  setPixel(5, 7, 1);
  setPixel(6, 7, 1);
  setPixel(7, 7, 1);
}
void text_zwoelf() {
  setPixel(3, 4, 1);
  setPixel(4, 4, 1);
  setPixel(5, 4, 1);
  setPixel(6, 4, 1);
  setPixel(7, 4, 1);
}

void testDisplay(){
    for (int i = 0; i < 8; i++) {
    //Seconds
    for (int t = 0; t < 8; t++) {
      setPixel(t, i, 1);
      updateDisplay();
      delay(10);
    }
    for (int t = 0; t < 8; t++) {
      setPixel(t, i, 0);
      updateDisplay();
      delay(10);
    }
   }
}

