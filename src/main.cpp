#include "../lib/helpers.h"
#include "Section.h"
#include <Arduino.h>
#include <FastLED.h>

#define TOTAL_LEDS 42
#define LED_PIN 3
CRGB strip[TOTAL_LEDS];
Section s1 = Section(strip);
Section s2 = Section(strip);
Section s3 = Section(strip);
Section s4 = Section(strip);
Section s5 = Section(strip);
Section s6 = Section(strip);

Section s7 = Section(strip);
Section s8 = Section(strip);
Section s9 = Section(strip);

Section *sectionArray[9] = {&s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9};

void rainbow(uint8_t pauseDuration);

void addPixelRanges()
{
  // ? so how do we organize this into a manager?
  // ? or do we want to leave it unorganized like this?
  s1.addPixelRange(0, 3);
  s2.addPixelRange(4, 7, true);
  s3.addPixelRange(8, 11);
  s4.addPixelRange(12, 15, true);
  s5.addPixelRange(16, 19);
  s6.addPixelRange(20, 23, true);

  s7.addPixelRange(24, 27);
  s7.addPixelRange(28, 31, true);

  s8.addPixelRange(32, 33);
  s8.addPixelRange(34, 35, true);

  s9.addPixelRange(36, 38);
  s9.addPixelRange(39, 41, true);
}

void setup()
{
  addPixelRanges();
  FastLED.addLeds<NEOPIXEL, LED_PIN>(strip, TOTAL_LEDS);
  FastLED.clear(true);
}

void loop()
{

  // * all at once
  s1.fillWithColor(0x51F0FF, FillStyle(ALL_AT_ONCE));
  delay(100);
  s2.fillWithColor(0x51F0AA, FillStyle(ALL_AT_ONCE));
  delay(100);
  s3.fillWithColor(0x51F0BB, FillStyle(ALL_AT_ONCE));
  delay(100);
  s4.fillWithColor(0x51F0CC, FillStyle(ALL_AT_ONCE));
  delay(100);
  s5.fillWithColor(0x51F0DD, FillStyle(ALL_AT_ONCE));
  delay(100);
  s6.fillWithColor(0x51F0EE, FillStyle(ALL_AT_ONCE));
  delay(100);

  s7.fillWithColor(0xFF00FF, FillStyle(ALL_AT_ONCE));
  delay(100);
  s8.fillWithColor(0xFFFF00, FillStyle(ALL_AT_ONCE));
  delay(100);
  s9.fillWithColor(0x00FFFF, FillStyle(ALL_AT_ONCE));
  delay(500);

  FastLED.clear(true);
  delay(500);

  // * one at a time
  s1.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  s2.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  s3.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  s4.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  s5.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  s6.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));

  s8.fillWithColor(0xFFFF00, FillStyle(ONE_AT_A_TIME, 150));
  s9.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 150));
  s7.fillWithColor(0xFF00FF, FillStyle(ONE_AT_A_TIME, 150));
  delay(500);
  FastLED.clear(true);

  rainbow(10);
  delay(500);
  FastLED.clear(true);
}

void rainbow(uint8_t pauseDuration)
{
  uint16_t level, wheelPosition;

  for (wheelPosition = 0; wheelPosition < 256; wheelPosition++)
  {
    for (level = 0; level < 4; level++)
    {

      uint32_t color = Wheel((level * 20 + wheelPosition) & 255);
      for (uint8_t i = 0; i < sizeof(sectionArray) / sizeof(sectionArray[0]); i++)
      {
        (*sectionArray[i]).setLevelColor(level, color);
      }

      delay(pauseDuration);
    }
  }
}