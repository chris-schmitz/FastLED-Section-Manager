#pragma once
#include "PixelRange.h"
#include <FastLED.h>
// #include <cstdint>

// * Used to set the array size for sections
// ! it worth considering switching this out with a vector type (external libary)
// ! or a linked list, but for the current use case a simple array is fine
#define SECTION_UPPER_LIMIT 10

// TODO: ripout when you add in to the actual code
// struct CRGB
// {
//   union
//   {
//     struct
//     {
//       union
//       {
//         uint8_t r;
//         uint8_t red;
//       };
//       union
//       {
//         uint8_t g;
//         uint8_t green;
//       };
//       union
//       {
//         uint8_t b;
//         uint8_t blue;
//       };
//     };
//     uint8_t raw[3];
//   };

//   /// Array access operator to index into the crgb object
//   inline uint8_t &operator[](uint8_t x) __attribute__((always_inline))
//   {
//     return raw[x];
//   }

//   /// Array access operator to index into the crgb object
//   inline const uint8_t &operator[](uint8_t x) const __attribute__((always_inline))
//   {
//     return raw[x];
//   }

//   // default values are UNINITIALIZED
//   inline CRGB() __attribute__((always_inline)) = default;

//   /// allow construction from R, G, B
//   inline CRGB(uint8_t ir, uint8_t ig, uint8_t ib) __attribute__((always_inline))
//   : r(ir), g(ig), b(ib)
//   {
//   }

//   /// allow construction from 32-bit (really 24-bit) bit 0xRRGGBB color code
//   inline CRGB(uint32_t colorcode) __attribute__((always_inline))
//   : r((colorcode >> 16) & 0xFF), g((colorcode >> 8) & 0xFF), b((colorcode >> 0) & 0xFF)
//   {
//   }
// };

enum FillType
{
  ALL_AT_ONCE,
  ONE_AT_A_TIME
};

// TODO: consider
// ? do we like this OO approach? if we do, is this the right shape??
struct FillStyle
{
  FillType type;
  int pauseDuration;

  FillStyle(FillType newType)
  {
    type = newType;
  }
  FillStyle(FillType newType, int newPauseDuration)
  {
    type = newType;
    pauseDuration = newPauseDuration;
  }
};

class Section
{
public:
  Section()
  {
    initialize();
  };
  Section(CRGB *leds) : _leds(leds)
  {
    initialize();
  };

  int getTotalRanges();
  // TODO: consider reactor
  // * getTotalLevels is referrings to the count of levels which is a 1 based concept, but we access the levels
  // * via a 0 based index. This approach works ane makes sense, but the DX feels awkward. Consider:
  // ^ - change the name to refer to a "highest Index" so that devs can use a (i = 0; i < highestIndex; i++) approach
  // ^ - update documentation to say "iteration needs to happen with a 1 based range"
  int getTotalLevels();

  void addPixelRange(PixelRange range);
  PixelRange getPixelRange(int index);

  void setLevelColor(int levelIndex, uint32_t color);

  void fillWithColor(uint32_t color, FillStyle style);
  void fillSectionWithGradient(uint32_t color, FillStyle style);

  void show();

private:
  int _totalRanges;
  int _totalLevelsInSection;
  CRGB *_leds;
  PixelRange _pixelRanges[SECTION_UPPER_LIMIT];

  void initialize()
  {
    _totalRanges = 0;
    _totalLevelsInSection = 0;
  }

  void updateLongestRange(uint8_t pixelCount);
};
