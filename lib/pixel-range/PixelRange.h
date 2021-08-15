#pragma once
#include <cstdint>

class PixelRange
{
public:
  PixelRange()
  {
    _iterateInReverse = false;
    _iteratorIndex = 0;
  }
  PixelRange(int rows, int startingIndex, int endingIndex);

  void resetIterator();
  void setReverseIteration(bool reverse);
  uint8_t getNextIndex();
  uint8_t getCurrentIndex();

  int getRowCount();
  int getStart();
  int getEnd();

private:
  uint8_t _iteratorIndex;
  bool _iterateInReverse;
  int _rowCount;
  int _start;
  int _end;
  int _indexSpacing;

  void setIteratorIndex(uint8_t index);
  uint8_t forwardIteration();
  uint8_t reverseIteration();
};