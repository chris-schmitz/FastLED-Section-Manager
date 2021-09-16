#include <Arduino.h>
#include <FastLED.h>
#include <SectionManager.h>
#include <helpers.h>

#define TOTAL_LEDS 42
#define LED_PIN 3
CRGB strip[TOTAL_LEDS];

SectionManager sectionManager = SectionManager(strip);

void rainbowMiddleIn(uint8_t pauseDuration);

void addSectionsAndRanges()
{
  // * Creating each section of the light
  sectionManager.addSections(9);
  // * Specifying what led ranges make up each section
  // * and whether the range should iterate forward or in reverse.
  // * Assuming you're wiring the strip in a zig zag pattern you'll
  // * want to flip the direction on every other row with the third boolean argument
  sectionManager.addRangeToSection(0, 0, 3, true);
  sectionManager.addRangeToSection(1, 4, 7, false); // * you can explicitly tell the range not to reverse if you'd like
  sectionManager.addRangeToSection(2, 8, 11, true);
  sectionManager.addRangeToSection(3, 12, 15);
  sectionManager.addRangeToSection(4, 16, 19, true);
  sectionManager.addRangeToSection(5, 20, 23);

  // * Notice that for sections of the light that are made of multiple
  // * rows of LEDs I'm adding a range per row
  sectionManager.addRangeToSection(6, 24, 27);
  sectionManager.addRangeToSection(6, 28, 31, true);

  sectionManager.addRangeToSection(7, 32, 33);
  sectionManager.addRangeToSection(7, 34, 35, true);

  sectionManager.addRangeToSection(8, 36, 38);
  sectionManager.addRangeToSection(8, 39, 41, true);
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

void rainbowAllSections(uint8_t pauseDuration);

void loop()
{
  rainbowAllSections(0);
  delay(1000);
  FastLED.clear(true);

  // * all at once
  sectionManager.fillSectionWithColor(0, 0x51F0FF, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.fillSectionWithColor(1, 0x51F0AA, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.fillSectionWithColor(2, 0x51F0BB, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.fillSectionWithColor(3, 0x51F0CC, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.fillSectionWithColor(4, 0x51F0DD, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.fillSectionWithColor(5, 0x51F0EE, FillStyle(ALL_AT_ONCE));
  delay(100);

  sectionManager.fillSectionWithColor(6, 0xFF00FF, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.fillSectionWithColor(7, 0xFFFF00, FillStyle(ALL_AT_ONCE));
  delay(100);
  sectionManager.fillSectionWithColor(8, 0x00FFFF, FillStyle(ALL_AT_ONCE));
  delay(500);

  FastLED.clear(true);
  delay(500);

  // * one at a time
  sectionManager.fillSectionWithColor(0, 0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.fillSectionWithColor(1, 0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.fillSectionWithColor(2, 0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.fillSectionWithColor(3, 0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.fillSectionWithColor(4, 0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));
  sectionManager.fillSectionWithColor(5, 0x00FFFF, FillStyle(ONE_AT_A_TIME, 100));

  sectionManager.fillSectionWithColor(6, 0xFFFF00, FillStyle(ONE_AT_A_TIME, 150));
  sectionManager.fillSectionWithColor(7, 0xFFFF00, FillStyle(ONE_AT_A_TIME, 150));
  sectionManager.fillSectionWithColor(8, 0xFF00FF, FillStyle(ONE_AT_A_TIME, 150));
  delay(500);
  FastLED.clear(true);

  rainbowMiddleIn(10);
  delay(500);
  FastLED.clear(true);
}

void rainbowAllSections(uint8_t pauseDuration)
{
  uint16_t level, wheelPosition;

  for (wheelPosition = 0; wheelPosition < 256; wheelPosition++)
  {
    for (level = 0; level < sectionManager.getTotalLevels(); level++)
    {

      uint32_t color = Wheel((level * 5 + wheelPosition) & 255);

      for (uint8_t i = 0; i < sectionManager.getTotalLevels(); i++)
      {
        sectionManager.setColorAtGlobalIndex(level, color);
      }
      FastLED.show();
      delay(pauseDuration);
    }
  }
}

void rainbowMiddleIn(uint8_t pauseDuration)
{
  uint16_t level, wheelPosition;

  for (wheelPosition = 0; wheelPosition < 256; wheelPosition++)
  {
    for (level = 0; level < 4; level++)
    {

      uint32_t color = Wheel((level * 20 + wheelPosition) & 255);
      for (uint8_t i = 0; i < sectionManager.getSectionCount(); i++)
      {
        sectionManager.getSection(i).setColorAtLevel(level, color, true);
      }

      delay(pauseDuration);
    }
  }
}