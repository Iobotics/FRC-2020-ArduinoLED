#include <Wire.h>
#include <FastLED.h>

const int ledStrip;
const int I2CAddress = 5;

unsigned int I2CValues[50];
unsigned int RGBValues;
bool receiveAll1 = false;
bool receiveAll2 = false;
bool receiveAll3 = false;

// SETTINGS FOR LEDS
#define DATA_PIN    2
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    26
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  Wire.begin(I2CAddress);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  FastLED.
}

void loop() {
  if (recieveAll3) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(I2CValues[0], I2CValues[1], I2CValues[2]);
      bool receiveAll1 = false;
      bool receiveAll2 = false;
      bool receiveAll3 = false;
    }
  }
}

void receiveEvent() {
  //while (Wire.available()) {
    if (receiveAll1 == false)
    {
      receiveAll1 = true;
      RGBValues = Wire.read();
      I2CValues[0] = RGBValues;
    }
    else if (receiveAll1 == true && receiveAll2 == false)
    {
      receiveAll2 = true;
      RGBValues = Wire.read();
      I2CValues[1] = RGBValues;
    }
    else
    {
      receiveAll3 = true;
      RGBValues = Wire.read();
      I2CValues[2] = RGBValues;
    }
  //}
}
