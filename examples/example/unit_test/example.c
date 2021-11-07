#include "u_test.h"
#include "../example.c"

INIT_U_TESTS(example.c);

U_TEST(test_example_0)
{
  ssize_t res = example(0);
  U_ASSERT_EQ(res, -EINVAL);
}

U_TEST(test_example_other)
{
  ssize_t res;

  res = example(1);
  U_ASSERT_EQ(res, 8);

  res = example(20);
  U_ASSERT_EQ(res, 27);
}

U_TEST(test_example_fail)
{
  ssize_t res = example(1);
  U_ASSERT_EQ(res, 10);
}

U_TESTS {
  RUN_U_TEST(test_example_0);
  RUN_U_TEST(test_example_other);
  RUN_U_TEST(test_example_fail);
  END_U_TESTS;
}

