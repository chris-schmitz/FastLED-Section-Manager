#include "../lib/helpers.h"
#include "Section.h"
#include "SectionManager.h"
#include <Arduino.h>
#include <FastLED.h>

#define TOTAL_LEDS 42
#define LED_PIN 3
CRGB strip[TOTAL_LEDS];

SectionManager sectionManager = SectionManager(strip);

void rainbow(uint8_t pauseDuration);

void addSectionsAndRanges()
{
  // * Creating each section of the light
  sectionManager.addSections(9);
  // * Specifying what led ranges make up each section
  // * and whether the range should iterate forward or in reverse.
  // * Assuming you're wiring the strip in a zig zag pattern you'll
  // * want to flip the direction on every other row with the third boolean argument
  sectionManager.getSection(0).addPixelRange(0, 3, true);
  sectionManager.getSection(1).addPixelRange(4, 7, false); // * you can explicitly tell the range not to reverse if you'd like
  sectionManager.getSection(2).addPixelRange(8, 11, true);
  sectionManager.getSection(3).addPixelRange(12, 15);
  sectionManager.getSection(4).addPixelRange(16, 19, true);
  sectionManager.getSection(5).addPixelRange(20, 23);

  // * Notice that for sections of the light that are made of multiple
  // * rows of LEDs I'm adding a range per row
  sectionManager.getSection(6).addPixelRange(24, 27);
  sectionManager.getSection(6).addPixelRange(28, 31, true);

  sectionManager.getSection(7).addPixelRange(32, 33);
  sectionManager.getSection(7).addPixelRange(34, 35, true);

  sectionManager.getSection(8).addPixelRange(36, 38);
  sectionManager.getSection(8).addPixelRange(39, 41, true);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");

  addSectionsAndRanges();

  // * Note that the SectionManager's main goal is to manage index grouping, you still
  // * need to setup the FastLED strip externally and you can still control the strip outside
  // * of the SectionManager
  FastLED.addLeds<NEOPIXEL, LED_PIN>(strip, TOTAL_LEDS);
  FastLED.clear(true);
}

void loop()
{
  // * all at once
  sectionManager.getSection(0).fillWithColor(0x51F0FF, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.getSection(1).fillWithColor(0x51F0AA, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.getSection(2).fillWithColor(0x51F0BB, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.getSection(3).fillWithColor(0x51F0CC, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.getSection(4).fillWithColor(0x51F0DD, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.getSection(5).fillWithColor(0x51F0EE, FillStyle(ALL_AT_ONCE));
  delay(100);

  sectionManager.getSection(6).fillWithColor(0xFF00FF, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.getSection(7).fillWithColor(0xFFFF00, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.getSection(8).fillWithColor(0x00FFFF, FillStyle(ALL_AT_ONCE));
  delay(500);

  FastLED.clear(true);
  delay(500);

  // * one at a time
  sectionManager.getSection(0).fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.getSection(1).fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.getSection(2).fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.getSection(3).fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.getSection(4).fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.getSection(5).fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));

  sectionManager.getSection(6).fillWithColor(0xFFFF00, FillStyle(ONE_AT_A_TIME, 150));
  sectionManager.getSection(7).fillWithColor(0x00FFFF, FillStyle(ONE_AT_A_TIME, 150));
  sectionManager.getSection(8).fillWithColor(0xFF00FF, FillStyle(ONE_AT_A_TIME, 150));
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
      for (uint8_t i = 0; i < sectionManager.getTotalSections(); i++)
      {
        sectionManager.getSection(i).setLevelColor(level, color);
      }

      delay(pauseDuration);
    }
  }
}