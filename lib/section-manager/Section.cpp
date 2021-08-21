#include "Section.h"
#include <iostream>

void Section::addPixelRange(PixelRange range)
{
  if (_totalRanges <= SECTION_UPPER_LIMIT)
  {
    _pixelRanges[_totalRanges] = range;
    _totalRanges++;
    updateLongestRange(range.getTotalPixels());
  }
}

PixelRange Section::getPixelRange(int index)
{
  return _pixelRanges[index];
}

int Section::getTotalLeds()
{
  return _totalLeds;
}

void Section::fillSectionWithSingleColor(uint32_t color, FillStyle style)
{
  for (int pixelRangeIndex = 0; pixelRangeIndex < getTotalRanges(); pixelRangeIndex++)
  {
    // TODO: ripout test logs
    // std::cout << std::endl;
    for (int i = 0; i < _longestRangeLength; i++)
    {
      try
      {
        int index = _pixelRanges[pixelRangeIndex].getNextIndex();

        // TODO: ripout test logs
        // std::cout << "pixelRangeIndex: " << pixelRangeIndex;
        // std::cout << ", led index: " << index;
        // std::cout << ", set color: " << color << std::endl;

        _leds[index] = CRGB(color);
        // std::cout << _leds[index].r << std::endl;
      }
      catch (ExceptionCodes code)
      {
        if (code == INDEX_OUT_OF_RANGE)
        {
          std::cout << std::endl
                    << " index out of range" << std::endl;
          // * Do nothing, we expect some indexes to be out of range
        }
      }
    }
  }
}

int Section::getTotalRanges()
{
  return _totalRanges;
}

void Section::resetAllRanges()
{
  for (int i = 0; i < getTotalRanges(); i++)
  {
    _pixelRanges[i].resetIterator();
  }
}

void Section::updateLongestRange(uint8_t pixelCount)
{
  if (pixelCount > _longestRangeLength)
  {
    _longestRangeLength = pixelCount;
  }
}