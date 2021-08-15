#include "PixelRange.h"

int getIndexSpacing(int rows, int start, int end)
{
  int totalIndexes = end - start;
  return totalIndexes / rows;
}

PixelRange::PixelRange(int rows, int startingIndex, int endingIndex)
{
  _rowCount = rows;
  _start = startingIndex;
  _end = endingIndex;
  _indexSpacing = getIndexSpacing(rows, _start, _end);
  resetIterator();
};

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

int PixelRange::getRowCount()
{
  return _rowCount;
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

uint8_t PixelRange::forwardIteration()
{
  if (_iteratorIndex < _end)
  {
    return ++_iteratorIndex;
  }
  return _iteratorIndex;
}

uint8_t PixelRange::reverseIteration()
{
  if (_iteratorIndex > _start)
  {
    return --_iteratorIndex;
  }
  return _iteratorIndex;
}