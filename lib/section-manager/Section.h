#pragma once
#include "PixelRange.h"
#include <FastLED.h>
// #include <cstdint>

// * Used to set the array size for sections
// ! it worth considering switching this out with a vector type (external libary)
// ! or a linked list, but for the current use case a simple array is fine
#define TOTAL_RANGES 10

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
    _initialize();
  };
  Section(CRGB *leds) : _leds(leds)
  {
    _initialize();
  };

  int getTotalRanges();
  // TODO: consider reactor
  // * getTotalLevels is referrings to the count of levels which is a 1 based concept, but we access the levels
  // * via a 0 based index. This approach works ane makes sense, but the DX feels awkward. Consider:
  // ^ - change the name to refer to a "highest Index" so that devs can use a (i = 0; i < highestIndex; i++) approach
  // ^ - update documentation to say "iteration needs to happen with a 1 based range"
  int getTotalLevels();

  void addPixelRange(int startingIndex, int endingIndex);
  void addPixelRange(int startingIndex, int endingIndex, bool reverse);
  void addPixelRange(PixelRange range);
  PixelRange &getPixelRange(int index);
  PixelRange *getPixelRanges();

  int getRangeCount();
  int getLargestLevelCount();

  int *getIndexesAtLevel(int level); // ? keep?

  void setColorAtLevel(int levelIndex, uint32_t color);

  void fillWithColor(uint32_t color, FillStyle style);
  void fillSectionWithGradient(uint32_t color, FillStyle style);

  void show();

private:
  int _rangeCount;
  int _largestLevelCount;
  CRGB *_leds;
  PixelRange _pixelRanges[TOTAL_RANGES];

  void _initialize()
  {
    _rangeCount = 0;
    _largestLevelCount = 0;
  }

  void _updateLongestRange(uint8_t pixelCount);
};
