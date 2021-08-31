#include "SectionManager.h"

void SectionManager::_initalize()
{
  _totalSections = 0;
}

void SectionManager::addSections(int sectionCount)
{
  if (_totalSections <= SECTION_UPPER_LIMIT)
  {
    for (int i = 0; i < sectionCount; i++)
    {
      Section s = Section(_leds);
      _sections[_totalSections] = s;
      _totalSections++;
    }
  }
}

Section &SectionManager::getSection(int sectionIndex)
{
  return _sections[sectionIndex];
}

int SectionManager::getTotalSections()
{
  return _totalSections;
}