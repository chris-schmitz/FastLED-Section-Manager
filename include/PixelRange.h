#pragma once
#include <cstdint>

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
  uint8_t getTotalLevels();

  int getIndexAtLevel(int level);
  int getStart();
  int getEnd();

  void setReverseIteration(bool reverse);

private:
  bool _iterateInReverse;
  int _start;
  int _end;

  int _getIndexAtLevel(int level);
};