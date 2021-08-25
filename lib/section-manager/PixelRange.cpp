#include "PixelRange.h"

// int getIndexSpacing(int rows, int start, int end)
// {
//   int totalIndexes = end - start;
//   return totalIndexes / rows;
// }

PixelRange::PixelRange(int startingIndex, int endingIndex)
{
  _start = startingIndex;
  _end = endingIndex;
  resetIterator();
};

// TODO: ripout
// PixelRange::PixelRange(int rows, int startingIndex, int endingIndex)
// {
//   _rowCount = rows;
//   _start = startingIndex;
//   _end = endingIndex;
//   _indexSpacing = getIndexSpacing(rows, _start, _end);
//   resetIterator();
// };

void PixelRange::setIteratorIndex(uint8_t index)
{
  _iteratorIndex = index;
}

void PixelRange::resetIterator()
{
  if (_iterateInReverse)
  {
    setIteratorIndex(_end);
    // _iteratorIndex[0] = _end;
  }
  else
  {
    setIteratorIndex(_start);
    // _iteratorIndex[0] = _start;
  }
}

// int PixelRange::getRowCount()
// {
//   return _rowCount;
// }
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
  resetIterator();
}

uint8_t PixelRange::getCurrentIndex()
{
  return _iteratorIndex;
}

uint8_t PixelRange::getNextIndex()
{
  if (_iterateInReverse == false)
  {
    return forwardIteration();
  }
  else
  {
    return reverseIteration();
  }
}

// TODO: consider
// ? is throwing an exception the best way of handling this?
// ? we're throwing an exception, but really requesting an index outside of the range is
// ? expected behavior in some circumstances, so maybe throwing isn't hte best way to handle
// ? this.
// ? That said, the details on what makes that an expected circumstance are determined outside
// ? of the bound of this object, so maybe it's the perfect use case for an exception :P
uint8_t PixelRange::forwardIteration()
{
  if (_iteratorIndex <= _end)
  {
    return _iteratorIndex++;
  }
  throw INDEX_OUT_OF_RANGE;
  // return _iteratorIndex;
}

uint8_t PixelRange::reverseIteration()
{
  if (_iteratorIndex > _start)
  {
    return _iteratorIndex--;
  }

  throw INDEX_OUT_OF_RANGE;
  // return _iteratorIndex;
}

uint8_t PixelRange::getTotalPixels()
{
  return _end - _start + 1; // * +1 to convert from base 0 to base 1
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
