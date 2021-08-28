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
  }
  PixelRange(int startingIndex, int endingIndex);
  PixelRange(int startingIndex, int endingIndex, bool reverse);

  uint8_t getTotalIndexes();
  int getIndexAtLevel(int level);
  int getStart();
  int getEnd();

  void setReverseIteration(bool reverse);

private:
  bool _iterateInReverse;
  int _start;
  int _end;

  int getIndexAtLevelAccordingToIterationDirection(int level);
};