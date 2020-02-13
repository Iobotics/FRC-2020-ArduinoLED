#include <Wire.h>
#include <FastLED.h>

const int ledStrip;
const int I2CAddress = 5;

int I2CValues[50];

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2CAddress);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
}

void receiveEvent() {
  for (int i = 0; i < 50; i++) {
    I2CValues[i] = ' ';
  }
  int i = 0;
  while (Wire.available()) {
    int RGBValues = Wire.read();
    I2CValues[i] = RGBValues;
    i++;
  }
}
