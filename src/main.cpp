#include "../lib/section-manager/Section.h"
#include <iostream>

using namespace std;

#define TOTAL_LEDS 30

CRGB strip[TOTAL_LEDS];

int main()
{

  Section s = Section(strip, TOTAL_LEDS);

  s.addPixelRange(PixelRange(0, 9));
  s.addPixelRange(PixelRange(10, 19));
  s.addPixelRange(PixelRange(20, 29));

  // s.fillSectionWithSingleColor(0x010101, FillStyle(ALL_AT_ONCE));
  s.fillSectionWithSingleColor(0x010203, FillStyle(ALL_AT_ONCE));

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