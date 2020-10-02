/*
 * The FRC Robot code is programmed to send three bytes (representing red, green, and blue color values--in that order) over I2C to the Arduino.
 * This code processes the values and writes the respective color values to the LED strip.
 */

//TODO: Add programable "sectors" for LEDs in multiple locations

#include <Wire.h> //For communicating over I2C.
#include <FastLED.h> //For writing to the LED strip.

const int I2CAddress = 21;

unsigned int I2CValues[10]; //Array to hold the three RGB values sent over I2C.
unsigned int RGBValues; //Temporary storage variable to hold the value of Wire.Read(); before being placed in I2CValues[]
unsigned int ledNum[2] = {0, 179};

//These booleans verify that the recieved bytes are processed correctly.
bool receive[5] = {false, false, false, false, false};

#define CHIPSET WS2812B
#define PIN     12
#define COLOR_ORDER GRB

//Individual numbers define the length of each strand
const unsigned int LED_COUNT = 122+28+29;

CRGB leds[LED_COUNT];

void setup() {
  // put your setup code here, to run once
  Wire.begin(I2CAddress);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  FastLED.addLeds<CHIPSET, PIN, COLOR_ORDER>(leds, LED_COUNT);
}

void loop() {
  if (receive[4]) {
    FastLED.clear();
    for (int i = ledNum[0]; i < (ledNum[1] + 1); i++) leds[i] = CRGB(I2CValues[0], I2CValues[1], I2CValues[2]);
    FastLED.show();
    for (int i = 0; i < 5; i++) receive[i] = false;
  }
}

//Runs when data is received.
void receiveEvent() {
  while (Wire.available()) {
    if (receive[0] == false)
    {
      receive[0] = true;
      RGBValues = Wire.read();
      I2CValues[0] = RGBValues;
    }
    else if (receive[0] == true && receive[1] == false)
    {
      receive[1] = true;
      RGBValues = Wire.read();
      I2CValues[1] = RGBValues;
    } else if (receive[1] == true && receive[2] == false)
    {
      receive[2] = true;
      RGBValues = Wire.read();
      I2CValues[2] = RGBValues;
    } else if (receive[2] == true && receive[3] == false)
    {
      receive[3] = true;
      ledNum[0] = Wire.read();
    }
    else
    {
      receive[4] = true;
      ledNum[1] = Wire.read();
    }
  }
}
