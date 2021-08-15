#include <PixelRange.h>
#include <unity.h>

PixelRange range;

int rows = 1;
int start = 5;
int end = 10;

void setUp(void)
{
  // set stuff up here
  range = PixelRange(rows, start, end);
}

// void tearDown(void) {
// // clean stuff up here
// }

void currentIndex_can_get_index(void)
{
  int currentIndex = range.getCurrentIndex();
  TEST_ASSERT_EQUAL(start, currentIndex);
}

void getNextIndex_can_iterate_through_indexes(void)
{
  int nextIndex1 = range.getNextIndex();
  int nextIndex2 = range.getNextIndex();
  int nextIndex3 = range.getNextIndex();

  TEST_ASSERT_EQUAL(start + 1, nextIndex1);
  TEST_ASSERT_EQUAL(start + 2, nextIndex2);
  TEST_ASSERT_EQUAL(start + 3, nextIndex3);
}

void getNextIndex_iteration_does_not_go_past_end(void)
{
  for (int i = 0; i < end - start; i++)
  {
    range.getNextIndex();
  }

  TEST_ASSERT_EQUAL(end, range.getCurrentIndex());
  TEST_ASSERT_EQUAL(end, range.getNextIndex());
}

void resetIterator_can_reset_iterator_after_iteration(void)
{
  for (int i = 0; i < end - start; i++)
  {
    range.getNextIndex();
  }

  range.resetIterator();
  TEST_ASSERT_EQUAL(start, range.getCurrentIndex());
}

void reverseIteration_reversing_iteration_start_at_end(void)
{
  range.setReverseIteration(true);

  int currentIndex = range.getCurrentIndex();

  TEST_ASSERT_EQUAL(end, currentIndex);
}

void reverseIteration_can_iterate_backwards_through_indexes(void)
{
  range.setReverseIteration(true);

  for (int i = 1; i < end - start; i++)
  {
    int index = range.getNextIndex();

    TEST_ASSERT_EQUAL(end - i, index);
  }
}

void getters_all_getters_work(void)
{
  TEST_ASSERT_EQUAL(start, range.getStart());
  TEST_ASSERT_EQUAL(end, range.getEnd());
  TEST_ASSERT_EQUAL(rows, range.getRowCount());
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();

  RUN_TEST(getters_all_getters_work);

  // ^ Single row tests
  RUN_TEST(currentIndex_can_get_index);
  RUN_TEST(getNextIndex_can_iterate_through_indexes);
  RUN_TEST(getNextIndex_iteration_does_not_go_past_end);
  RUN_TEST(resetIterator_can_reset_iterator_after_iteration);
  RUN_TEST(reverseIteration_reversing_iteration_start_at_end);
  RUN_TEST(reverseIteration_can_iterate_backwards_through_indexes);
  UNITY_END();

  return 0;
}
