/*
 * The FRC Robot code is programmed to send three bytes (representing red, green, and blue color values--in that order) over I2C to the Arduino.
 * This code processes the values and writes the respective color values to the LED strip.
 */

#include <Wire.h> //For communicating over I2C.
#include <FastLED.h> //For writing to the LED strip.

const int ledStrip; //TBD which pin this will be on.
const int I2CAddress = 5;

unsigned int I2CValues[50]; //Array to hold the three RGB values sent over I2C.
unsigned int RGBValues; //Temporary storage variable to hold the value of Wire.Read(); before being placed in I2CValues[]

//These booleans verify that the recieved bytes are processed correctly.
bool receiveAll1 = false;
bool receiveAll2 = false;
bool receiveAll3 = false;

// SETTINGS FOR LEDS -- Reminder: Revise these values later. It is not yet certain if these are correct.
#define DATA_PIN    2
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB //Note: The color order here is GRB, but below in the loop the CRGB write function orders the values in RGB. Should the order be changed here or in the write function? Or does it automatically accommodate for this issue? -Braden.
#define NUM_LEDS    26
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050); //Reminder: Revise these values later. It is not yet certain if these are correct.
  Wire.begin(I2CAddress);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  FastLED. //Note: This was just left hanging here? Is it unfinished code or can I delete it. -Braden.
}

void loop() {
  if (recieveAll3) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(I2CValues[0], I2CValues[1], I2CValues[2]); //Turns on the LEDs at the specified colors.
      bool receiveAll1 = false;
      bool receiveAll2 = false;
      bool receiveAll3 = false;
    }
  }
}

//Runs when data is received.
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
