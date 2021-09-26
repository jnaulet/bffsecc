#include "u_test.h"
#include "u_assert.h"

#include "../example.c"

static void test_example_0(void)
{
  ssize_t res = example(0);
  u_assert_var_equals(res, -EINVAL);
}

static void test_example_other(void)
{
  ssize_t res;

  res = example(1);
  u_assert_var_equals(res, 8);

  res = example(20);
  u_assert_var_equals(res, 27);
}

static void test_example_fail(void)
{
  ssize_t res = example(1);
  u_assert_var_equals(res, 10);
}

UNIT_TESTS {
  U_TEST(test_example_0);
  U_TEST(test_example_other);
  U_TEST(test_example_fail);
}
