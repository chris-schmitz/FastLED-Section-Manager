// #include <FastLED.h>
#include "PixelRange.h"
#include "SectionManager.h"
#include <unity.h>

void setUp(void)
{
}

// * PixelRange tests ======================================= * //

PixelRange range;

int rows = 1;
int start = 5;
int end = 10;

void setupPixelRange()
{
  range = PixelRange(rows, start, end);
}

void currentIndex_can_get_index(void)
{

  setupPixelRange();
  int currentIndex = range.getCurrentIndex();
  TEST_ASSERT_EQUAL(start, currentIndex);
}

void getNextIndex_can_iterate_through_indexes(void)
{
  setupPixelRange();
  int nextIndex1 = range.getNextIndex();
  int nextIndex2 = range.getNextIndex();
  int nextIndex3 = range.getNextIndex();

  TEST_ASSERT_EQUAL(start + 1, nextIndex1);
  TEST_ASSERT_EQUAL(start + 2, nextIndex2);
  TEST_ASSERT_EQUAL(start + 3, nextIndex3);
}

void getNextIndex_iteration_does_not_go_past_end(void)
{
  setupPixelRange();
  for (int i = 0; i < end - start; i++)
  {
    range.getNextIndex();
  }

  TEST_ASSERT_EQUAL(end, range.getCurrentIndex());
  TEST_ASSERT_EQUAL(end, range.getNextIndex());
}

void resetIterator_can_reset_iterator_after_iteration(void)
{
  setupPixelRange();
  for (int i = 0; i < end - start; i++)
  {
    range.getNextIndex();
  }

  range.resetIterator();
  TEST_ASSERT_EQUAL(start, range.getCurrentIndex());
}

void reverseIteration_reversing_iteration_start_at_end(void)
{
  setupPixelRange();
  range.setReverseIteration(true);

  int currentIndex = range.getCurrentIndex();

  TEST_ASSERT_EQUAL(end, currentIndex);
}

void reverseIteration_can_iterate_backwards_through_indexes(void)
{
  setupPixelRange();
  range.setReverseIteration(true);

  for (int i = 1; i < end - start; i++)
  {
    int index = range.getNextIndex();

    TEST_ASSERT_EQUAL(end - i, index);
  }
}

void getters_all_getters_work(void)
{
  setupPixelRange();
  TEST_ASSERT_EQUAL(start, range.getStart());
  TEST_ASSERT_EQUAL(end, range.getEnd());
  TEST_ASSERT_EQUAL(rows, range.getRowCount());
}

// * ======================================================== * //

// * SectionManager tests =================================== * //

CRGB leds[60];

SectionManager manager;
const int totalLeds = 20;

void setupSectionManager()
{
  manager = SectionManager(leds, totalLeds);
}

void sectionManager_can_get_total_leds(void)
{
  setupSectionManager();
  TEST_ASSERT_EQUAL(totalLeds, manager.getTotalLeds());
}

void sectionManager_can_add_a_section()
{
  setupSectionManager();
  PixelRange range = PixelRange(1, 5, 10);

  manager.addSection(range);

  TEST_ASSERT_EQUAL(range.getRowCount(), manager.getSection(0).getRowCount());
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  // * SectionManager Tests
  RUN_TEST(sectionManager_can_get_total_leds);

  // * PixelRange Tests
  RUN_TEST(getters_all_getters_work);

  // ^ Single row tests
  RUN_TEST(currentIndex_can_get_index);
  RUN_TEST(getNextIndex_can_iterate_through_indexes);
  RUN_TEST(getNextIndex_iteration_does_not_go_past_end);
  RUN_TEST(resetIterator_can_reset_iterator_after_iteration);
  RUN_TEST(reverseIteration_reversing_iteration_start_at_end);
  RUN_TEST(reverseIteration_can_iterate_backwards_through_indexes);
  RUN_TEST(sectionManager_can_add_a_section);
  UNITY_END();
  return 0;
}