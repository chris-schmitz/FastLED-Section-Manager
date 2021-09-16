#include "Section.h"
#include <FastLED.h>

void Section::addPixelRange(int startingIndex, int endingIndex)
{
  addPixelRange(PixelRange(startingIndex, endingIndex));
}

void Section::addPixelRange(int startingIndex, int endingIndex, bool reverse)
{
  addPixelRange(PixelRange(startingIndex, endingIndex, reverse));
}

void Section::addPixelRange(PixelRange range)
{
  if (_rangeCount <= TOTAL_RANGES)
  {
    _pixelRanges[_rangeCount] = range;
    _rangeCount++;
    _updateLongestRange(range.getTotalLevels());
  }
}

PixelRange &Section::getPixelRange(int index)
{
  return _pixelRanges[index];
}
PixelRange *Section::getPixelRanges()
{
  return _pixelRanges;
}

int Section::getRangeCount()
{
  return _rangeCount;
}

int Section::getLargestLevelCount()
{
  return _largestLevelCount;
}

int Section::getTotalLevels()
{
  return _largestLevelCount;
}

int *Section::getIndexesAtLevel(int level)
{
  int indexes[getTotalRanges()];

  for (int i = 0; i < getTotalRanges(); i++)
  { //? <= ??
    indexes[i] = _pixelRanges[i].getIndexAtLevel(level);
  }
  return indexes;
}

void Section::fillWithColor(uint32_t color, FillStyle style)
{
  for (int level = 0; level <= _largestLevelCount; level++)
  {
    for (int pixelRangeIndex = 0; pixelRangeIndex < getTotalRanges(); pixelRangeIndex++)
    {
      int index = _pixelRanges[pixelRangeIndex].getIndexAtLevel(level);
      if (index == -1)
      {
        return;
      }

      _leds[index] = CRGB(color);
    }
    if (style.type == ONE_AT_A_TIME)
    {
      show();
      delay(style.pauseDuration);
    }
  }
  if (style.type == ALL_AT_ONCE)
  {
    show();
  }
}

int Section::getTotalRanges()
{
  return _rangeCount;
}

void Section::_updateLongestRange(uint8_t levelCount)
{
  if (levelCount > _largestLevelCount)
  {
    _largestLevelCount = levelCount;
  }
}

void Section::setColorAtLevel(int levelIndex, uint32_t color)
{
  setColorAtLevel(levelIndex, color, false);
}
void Section::setColorAtLevel(int levelIndex, uint32_t color, bool showColor)
{
  for (int pixelRangeIndex = 0; pixelRangeIndex < getTotalRanges(); pixelRangeIndex++)
  {
    int index = _pixelRanges[pixelRangeIndex].getIndexAtLevel(levelIndex);
    if (index == -1)
    {
      return;
    }
    _leds[index] = CRGB(color);
  }
  if (showColor)
  {
    show();
  }
}

void Section::show()
{
  FastLED.show();
}

void Section::clear()
{
  fillWithColor(CRGB::Black, FillStyle(ALL_AT_ONCE));
}