#pragma once
#include <Arduino.h>

// ! IMPORTANT NOTE!
// * This Wheel class and rgbToUint32 is an adaptation of Adafruit's functions in their
// * strand_test example:
// ? https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest_wheel/strandtest_wheel.ino
// * I adjusted it here to be more generic -> fastled friendly, but it functions the same

uint32_t rgbToUint32(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

uint32_t Wheel(uint8_t WheelPosition)
{
  WheelPosition = 255 - WheelPosition; // flip the number

  if (WheelPosition < 85)
  {
    return rgbToUint32(255 - WheelPosition * 3, 0, WheelPosition * 3);
  }

  if (WheelPosition < 170)
  {
    WheelPosition -= 85;
    return rgbToUint32(0, WheelPosition * 3, 255 - WheelPosition * 3);
  }

  WheelPosition -= 170;
  return rgbToUint32(WheelPosition * 3, 255 - WheelPosition * 3, 0);
}
