#include "../lib/section-manager/Section.h"
#include <iostream>

using namespace std;

#define TOTAL_LEDS 30

CRGB strip[TOTAL_LEDS];

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
  s.fillSectionWithSingleColor(0x010101, FillStyle(ALL_AT_ONCE));

  // * one at a time
  s.fillSectionWithSingleColor(0x010203, FillStyle(ONE_AT_A_TIME, 10));

  for (uint8_t i = 0; i <= s.getTotalLevels(); i++)
  {
    s.setLevelColor(i, 0x010203);
    // s.show();
  }

  // s.fillSectionWithGradient(0x000000, )

  // ^ Test - get led values
  for (int i = 0; i < TOTAL_LEDS; i++)
  {
    cout << (char)(0x31 + strip[i].r) << ", "
         << (char)(0x31 + strip[i].g) << ", "
         << (char)(0x31 + strip[i].b) << ", ";
    cout << endl;
  }

  // cout << (char)0x31 << endl;

  // cout << endl
  //      << endl;
  // for (int i = 32; i < 128; i++)
  // {
  //   cout << i << ": " << (char)i << endl;
  // }
}