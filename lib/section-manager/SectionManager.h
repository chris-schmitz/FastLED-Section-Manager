#pragma once
#include "Pair.h"
#include "Section.h"

#define SECTION_UPPER_LIMIT 20

class SectionManager
{
public:
  SectionManager(CRGB *leds) : _leds(leds)
  {
    _initalize();
  }

  void addSection(Section section); // ? keep? cut?
  void addSections(int sectionCount);
  Section &getSection(int sectionIndex);

  void addRangeToSection(int sectionIndex, int rangeStart, int rangeEnd);
  void addRangeToSection(int sectionIndex, int rangeStart, int rangeEnd, bool reverseRange);

  int getSectionCount();
  int getTotalLevels();

  void setColorAtGlobalIndex(int globalIndex, uint32_t color);
  void fillSectionWithColor(int sectionIndex, uint32_t color, FillStyle style);

private:
  CRGB *_leds;
  uint8_t _sectionCount;
  int _totalLevels;
  Section _sections[SECTION_UPPER_LIMIT];
  int _maxLevelPerSection[SECTION_UPPER_LIMIT];

  int _relativeIteration_sectionIndex = 0;
  int _relativeIteration_levelIndex = 0;

  void _initalize();
  Pair<int> _findSectionFromGlobalIndex(int globalIndex);
  void _calculateTotalLevels();
};
