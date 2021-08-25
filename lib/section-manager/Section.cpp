#include "Section.h"
#include <iostream>

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

void Section::fillSectionWithSingleColor(uint32_t color, FillStyle style)
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
        std::cout << "pixelRangeIndex: " << pixelRangeIndex;
        std::cout << ", led index: " << index;
        std::cout << ", set color: " << color << std::endl;

        _leds[index] = CRGB(color);
        if (style.type == ONE_AT_A_TIME)
        {
          // FastLed.show();
          // delay(style.pauseDuration)
          std::cout << "pause for " << style.pauseDuration << " seconds" << std::endl;
        }
        // std::cout << _leds[index].r << std::endl;
      }
      catch (ExceptionCodes code)
      {
        if (code == INDEX_OUT_OF_RANGE)
        {
          std::cout << std::endl;
          // << " index out of range" << std::endl;
          // * Do nothing, we expect some indexes to be out of range
        }
      }
    }
    std::cout << "---" << std::endl;
  }
  if (style.type == ALL_AT_ONCE)
  {
    // FastLed.show();
    std::cout << "Show at end" << std::endl
              << std::endl;
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
      std::cout << "level: " << levelIndex << ", Pixel Range: " << pixelRangeIndex << ", index: " << index << std::endl;
      _leds[index] = CRGB(color);
    }
    catch (ExceptionCodes code)
    {
      if (code == INDEX_OUT_OF_RANGE)
      {
        std::cout << std::endl;
        // << " index out of range" << std::endl;
        // * Do nothing, we expect some indexes to be out of range
      }
    }
  }
  std::cout << "-----------------------------------" << std::endl;
  // FastLed.show();
}