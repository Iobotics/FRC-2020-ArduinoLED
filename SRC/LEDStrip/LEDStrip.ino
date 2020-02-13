#include <Wire.h>

const int ledStrip;
const int I2CAddress = 5;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2CAddress);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.onReceive(receiveEvent);
}

void receiveEvent() {
  
}
