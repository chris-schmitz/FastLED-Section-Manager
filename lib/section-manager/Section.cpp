#include "Section.h"
#include <FastLED.h>

void Section::addPixelRange(PixelRange range)
{
  if (_totalRanges <= SECTION_UPPER_LIMIT)
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
    // TODO: ripout test logs
    // std::cout << std::endl;
    for (int pixelRangeIndex = 0; pixelRangeIndex < getTotalRanges(); pixelRangeIndex++)
    {
      try
      {
        int index = _pixelRanges[pixelRangeIndex].getIndexAtLevel(level);

        // TODO: ripout test logs
        // std::cout << "pixelRangeIndex: " << pixelRangeIndex;
        // std::cout << ", led index: " << index;
        // std::cout << ", set color: " << color << std::endl;

        _leds[index] = CRGB(color);
      }
      catch (ExceptionCodes code)
      {
        if (code == INDEX_OUT_OF_RANGE)
        {
          // * Do nothing, we expect some indexes to be out of range
        }
      }
    }
    if (style.type == ONE_AT_A_TIME)
    {
      show();
      delay(style.pauseDuration);
      // std::cout << "pause for " << style.pauseDuration << " seconds" << std::endl;
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
    try
    {
      int index = _pixelRanges[pixelRangeIndex].getIndexAtLevel(levelIndex);
      // std::cout << "level: " << levelIndex << ", Pixel Range: " << pixelRangeIndex << ", index: " << index << std::endl;
      _leds[index] = CRGB(color);
    }
    catch (ExceptionCodes code)
    {
      if (code == INDEX_OUT_OF_RANGE)
      {
        // << " index out of range" << std::endl;
        // * Do nothing, we expect some indexes to be out of range
      }
    }
  }
  FastLED.show();
}

void Section::show()
{
  FastLED.show();
  // std::cout << "--> write to strip" << std::endl;
}