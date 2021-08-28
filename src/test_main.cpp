#include "../lib/helpers.h"
#include "../lib/section-manager/Section.h"
#include <iostream>

using namespace std;

#define TOTAL_LEDS 30

CRGB strip[TOTAL_LEDS];

void rainbow(Section *s, uint8_t pauseDuration)
{
  uint16_t level, wheelPosition;

  for (wheelPosition = 0; wheelPosition < 256; wheelPosition++)
  {
    for (level = 0; level <= s->getTotalLevels(); level++)
    {
      cout << "level: " << level << ", color: " << (Wheel(level + wheelPosition) & 255) << endl;
      s->setLevelColor(level, Wheel(level + wheelPosition) & 255);
    }
    s->show();
    // delay(pauseDuration);
  }
}

int main()
{

  Section s = Section(strip);

  PixelRange r2 = PixelRange(10, 19);
  r2.setReverseIteration(true);

  s.addPixelRange(PixelRange(0, 9));
  s.addPixelRange(r2);
  // s.addPixelRange(PixelRange(10, 19));
  s.addPixelRange(PixelRange(20, 29));

  // * all at once
  // s.fillWithColor(0x010101, FillStyle(ALL_AT_ONCE));

  // * one at a time
  // s.fillWithColor(0x010203, FillStyle(ONE_AT_A_TIME, 10));

  // * fill level by level
  // for (uint8_t i = 0; i <= s.getTotalLevels(); i++)
  // {
  //   s.setLevelColor(i, 0x010203);
  //   // s.show();
  // }

  // * rainbow
  rainbow(&s, 50);

  /*
  uint16_t level, wheelPosition;

  for (wheelPosition = 0; wheelPosition < 256; wheelPosition++)
  {
    for (level = 0; level <= 10; level++)
    {
      cout << ", level: " << level << ", wheel: " << wheelPosition << ", color: " << (level + wheelPosition) << ", wheel: " << Wheel(level + wheelPosition & 255) << endl;
      // cout << ", color: " << (level + wheelPosition) << endl;
      // cout << ", color: " << Wheel(level + wheelPosition) << endl;
      // cout << ", color: " << (Wheel(level + wheelPosition) & 255) << endl;
    }
    cout << "---" << endl;
  }
  */

  // // ^ Test - get led values
  // for (int i = 0; i < TOTAL_LEDS; i++)
  // {
  //   cout << (char)(0x31 + strip[i].r) << ", "
  //        << (char)(0x31 + strip[i].g) << ", "
  //        << (char)(0x31 + strip[i].b) << ", ";
  //   cout << endl;
  // }
}