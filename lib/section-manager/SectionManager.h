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

private:
  CRGB *_leds;
  uint8_t _totalSections;
  Section _sections[SECTION_UPPER_LIMIT];

  void _initalize();
};
