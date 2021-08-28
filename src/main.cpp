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

void rainbow(Section *s, uint8_t pauseDuration);

void addPixelRanges()
{
  // ? so how do we organize this into a manager?
  s1.addPixelRange(PixelRange(0, 3));
  s2.addPixelRange(PixelRange(4, 7, true));
  s3.addPixelRange(PixelRange(8, 11));
  s4.addPixelRange(PixelRange(12, 15, true));
  s5.addPixelRange(PixelRange(16, 19));
  s6.addPixelRange(PixelRange(20, 23, true));

  s7.addPixelRange(PixelRange(24, 27));
  s7.addPixelRange(PixelRange(28, 31, true));

  s8.addPixelRange(PixelRange(32, 33));
  s8.addPixelRange(PixelRange(34, 35, true));

  s9.addPixelRange(PixelRange(36, 38));
  s9.addPixelRange(PixelRange(39, 41, true));
}

void setup()
{
  addPixelRanges();
  FastLED.addLeds<NEOPIXEL, LED_PIN>(strip, TOTAL_LEDS);
  Serial.begin(9600);
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

  s8.fillWithColor(0xFFFF00, FillStyle(ONE_AT_A_TIME, 500));
  s9.fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 500));
  s7.fillWithColor(0xFF00FF, FillStyle(ONE_AT_A_TIME, 500));
  delay(500);
  FastLED.clear(true);

  // * fill level by level
  // for (uint8_t i = 0; i <= s1.getTotalLevels(); i++)
  // {
  //   s1.setLevelColor(i, 0xFFFF00);
  //   s1.show();
  //   delay(100);
  // }
  // delay(500);

  // rainbow(&s1, 10);
  delay(500);
}

void rainbow(Section *s, uint8_t pauseDuration)
{
  uint16_t level, wheelPosition;

  for (wheelPosition = 0; wheelPosition < 256; wheelPosition++)
  {
    for (level = 0; level <= s->getTotalLevels(); level++)
    {
      s->setLevelColor(level, Wheel(level + wheelPosition) & 255);
    }
    s->show();
    delay(pauseDuration);
  }
}