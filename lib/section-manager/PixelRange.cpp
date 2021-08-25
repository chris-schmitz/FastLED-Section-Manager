#include "PixelRange.h"

PixelRange::PixelRange(int startingIndex, int endingIndex)
{
  _start = startingIndex;
  _end = endingIndex;
};

int PixelRange::getStart()
{
  return _start;
}
int PixelRange::getEnd()
{
  return _end;
}

void PixelRange::setReverseIteration(bool reverse)
{
  _iterateInReverse = reverse;
}

uint8_t PixelRange::getTotalPixels()
{
  return _end - _start + 1; // * +1 to convert from base 0 to base 1
}

uint8_t PixelRange::getTotalIndexes()
{
  return _end - _start;
}

int PixelRange::getIndexAtLevel(int level)
{
  if (level < getTotalPixels())
  {
    return getIndexAtLevelAccordingToIterationDirection(level);
  }

  throw INDEX_OUT_OF_RANGE;
}

int PixelRange::getIndexAtLevelAccordingToIterationDirection(int level)
{
  if (_iterateInReverse)
  {
    return _end - level;
  }
  return _start + level;
}
