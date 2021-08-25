#pragma once
#include <cstdint>

enum ExceptionCodes
{
  INDEX_OUT_OF_RANGE
};

class PixelRange
{
public:
  PixelRange()
  {
    _iterateInReverse = false;
    _levelIterator = 0;
  }
  PixelRange(int startingIndex, int endingIndex);
  // TODO ripout

  void setReverseIteration(bool reverse);
  uint8_t getTotalPixels();
  uint8_t getTotalIndexes();

  int getIndexAtLevel(int level);

  int getStart();
  int getEnd();

private:
  uint8_t _levelIterator;
  bool _iterateInReverse;
  int _rowCount;
  int _start;
  int _end;

  void setLevelIterator(uint8_t index);
  uint8_t forwardIteration();
  uint8_t reverseIteration();

  // TODO: rename
  int getIndexAtLevelAccordingToIterationDirection(int level);
};