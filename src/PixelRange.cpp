#include "PixelRange.h"

PixelRange::PixelRange(int startingIndex, int endingIndex)
{
  _start = startingIndex;
  _end = endingIndex;
  _iterateInReverse = false;
}

PixelRange::PixelRange(int startingIndex, int endingIndex, bool reverse)
{
  _start = startingIndex;
  _end = endingIndex;
  _iterateInReverse = reverse;
}

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

uint8_t PixelRange::getTotalIndexes()
{
  return _end - _start;
}

uint8_t PixelRange::getTotalLevels()
{
  return getTotalIndexes() + 1; // * convert from base 0 index to base 1 levels
}

int PixelRange::getIndexAtLevel(int level)
{
  if (level <= getTotalIndexes())
  {
    return _getIndexAtLevel(level);
  }
  else
  {
    return -1;
  }
}

int PixelRange::_getIndexAtLevel(int level)
{
  if (level > getTotalIndexes())
  {
    return -1;
  }

  if (_iterateInReverse)
  {
    return _end - level;
  }

  return _start + level;
}
