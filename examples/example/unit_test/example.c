#include "u_test.h"
#include "../example.c"

INIT_U_TESTS(example.c);

U_TEST(test_example_0)
{
  ssize_t res = example(0);
  u_assert_var_equals(res, -EINVAL);
}

U_TEST(test_example_other)
{
  ssize_t res;

  res = example(1);
  u_assert_var_equals(res, 8);

  res = example(20);
  u_assert_var_equals(res, 27);
}

U_TEST(test_example_fail)
{
  ssize_t res = example(1);
  u_assert_var_equals(res, 10);
}

U_TESTS {
  RUN_U_TEST(test_example_0);
  RUN_U_TEST(test_example_other);
  RUN_U_TEST(test_example_fail);
  END_U_TESTS;
}

