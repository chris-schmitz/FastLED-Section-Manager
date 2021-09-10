#include "SectionManager.h"

void SectionManager::_initalize()
{
  _sectionCount = 0;
}

void SectionManager::addSections(int count)
{
  if (_sectionCount + count <= SECTION_UPPER_LIMIT)
  {
    for (int i = 0; i < count; i++)
    {
      Section s = Section(_leds);
      _sections[_sectionCount] = s;
      _sectionCount++;
    }
  }
}

Section &SectionManager::getSection(int sectionIndex)
{
  return _sections[sectionIndex];
}

int SectionManager::getSectionCount()
{
  return _sectionCount;
}

void SectionManager::addRangeToSection(int sectionIndex, int rangeStart, int rangeEnd)
{
  addRangeToSection(sectionIndex, rangeStart, rangeEnd, false);
}

void SectionManager::addRangeToSection(int sectionIndex, int rangeStart, int rangeEnd, bool reverseRange)
{
  getSection(sectionIndex).addPixelRange(rangeStart, rangeEnd, reverseRange);
  _maxLevelPerSection[sectionIndex] = getSection(sectionIndex).getLargestLevelCount();
  _calculateTotalLevels();
}

int SectionManager::getTotalLevels()
{
  return _totalLevels;
}
void SectionManager::_calculateTotalLevels()
{
  int total = 0;
  for (int i = 0; i < SECTION_UPPER_LIMIT; i++)
  {
    total += _sections[i].getTotalLevels();
  }
  _totalLevels = total;
  // return total;
}

void SectionManager::setColorAtGlobalIndex(int globalIndex, uint32_t color)
{
  Pair<int> globalPosition = _findSectionFromGlobalIndex(globalIndex);

  int sectionIndex = globalPosition.getFirst();
  int relativeOffset = globalPosition.getSecond();
  int levelIndex = globalIndex - relativeOffset;
  // char buffer[100];
  // sprintf(buffer, "Section: %d, offset: %d, level: %d, color: %d", sectionIndex, relativeOffset, levelIndex, color);
  // Serial.println(buffer);

  getSection(sectionIndex).setColorAtLevel(levelIndex, color);
}

Pair<int> SectionManager::_findSectionFromGlobalIndex(int globalIndex)
{
  int accumulator = 0;
  for (int i = 0; i < _sectionCount; i++)
  {
    accumulator += _maxLevelPerSection[i];
    if (globalIndex < accumulator)
    {
      return Pair<int>(i, accumulator - _maxLevelPerSection[i]);
    }
  }
}

void SectionManager::fillSectionWithColor(int sectionIndex, uint32_t color, FillStyle style)
{
  getSection(sectionIndex).fillWithColor(color, style);
}