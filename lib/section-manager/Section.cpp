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
  if (_totalRanges <= PIXEL_RANGE_UPPER_LIMIT)
  {
    _pixelRanges[_totalRanges] = range;
    _totalRanges++;
    updateLongestRange(range.getTotalIndexes());
  }
}

PixelRange Section::getPixelRange(int index)
{
  return _pixelRanges[index];
}

int Section::getTotalLevels()
{
  return _totalLevelsInSection;
}

void Section::fillWithColor(uint32_t color, FillStyle style)
{
  for (int level = 0; level <= _totalLevelsInSection; level++)
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
  return _totalRanges;
}

void Section::updateLongestRange(uint8_t numberOfIndexesInRange)
{
  if (numberOfIndexesInRange > _totalLevelsInSection)
  {
    _totalLevelsInSection = numberOfIndexesInRange;
  }
}

void Section::setLevelColor(int levelIndex, uint32_t color)
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
  show();
}

void Section::show()
{
  FastLED.show();
}