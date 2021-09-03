#pragma once
#include "Section.h"

#define SECTION_UPPER_LIMIT 20

class SectionManager
{
public:
  SectionManager(CRGB *leds) : _leds(leds)
  {
    _initalize();
  }

  void addSection(Section section);
  void addSections(int sectionCount);
  Section &getSection(int sectionIndex);
  int getTotalSections();

  int getTotalLevels();

  int *getIndexesAtRelativeLevel(int level);

private:
  CRGB *_leds;
  uint8_t _totalSections;
  Section _sections[SECTION_UPPER_LIMIT];

  int _relativeIteration_sectionIndex = 0;
  int _relativeIteration_levelIndex = 0;

  void _initalize();
};
