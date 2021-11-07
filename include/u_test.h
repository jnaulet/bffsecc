#ifndef U_TEST_H
#define U_TEST_H

#include <stdio.h>
#include <string.h>

#define INIT_U_TESTS(name)                      \
  int __result__ = 0

#define U_TEST(name)                            \
  void name(void)

#define RUN_U_TEST(x)                           \
  do {                                          \
    fprintf(stderr, "### Running %s...\n", #x);	\
    x();                                        \
  } while(0)

/* Usage:
 * U_TESTS {
 *   RUN_U_TEST(a);
 *   RUN_U_TEST(b);
 *   RUN_U_TEST(c);
 *   END_U_TESTS;
 * } 
 */
#define U_TESTS                                 \
  int main(int argc, char **argv)

#define END_U_TESTS                             \
  return __result__

/* asserts */

#define U_ASSERT(x)                                     \
  ((x) ? __u_assert_passed(x) : __u_assert_failed(x))

#define U_ASSERT_EQ(a, b)			\
  ((a) == (b) ? __u_assert_eq_passed(a, b)	\
   : __u_assert_eq_failed(a, b))

#define U_ASSERT_STR_EQ(a, b)			\
  (!strcmp((a), (b)) ?				\
   __u_assert_str_eq_passed(a, b) :		\
   __u_assert_str_eq_failed(a, b))

/* useful stuff */

#define NOT_NULL ((void*)1)
  
/* internals */

#define __u_assert_output(x, status, ret)               \
  ({ fprintf(stdout, "%s:%d assertion \'%s\' %s.\n",    \
             __FILE__, __LINE__, #x, #status);          \
    __result__ |= ret; })

#define __u_assert_passed(x) __u_assert_output(x, passed, 0)
#define __u_assert_failed(x) __u_assert_output(x, failed, -1)

#define __u_assert_eq_output(a, b, status, ret)				\
  ({ fprintf(stdout, "%s:%d \'%s(%ld) == %s(%ld)\' %s.\n",              \
             __FILE__, __LINE__, #a, (long)a, #b, (long)b, #status);    \
    __result__ |= ret; })

#define __u_assert_eq_passed(a, b)		\
  __u_assert_eq_output(a, b, passed, 0)
#define __u_assert_eq_failed(a, b)		\
  __u_assert_eq_output(a, b, failed, -1)

#define __u_assert_str_eq_output(a, b, status, ret)		\
  ({ fprintf(stdout, "%s:%d \'%s(%s) == %s(%s)\' %s.\n",        \
             __FILE__, __LINE__, #a, a, #b, b, #status);        \
    __result__ |= ret; })

#define __u_assert_str_eq_passed(a, b)		\
  __u_assert_str_eq_output(a, b, passed, 0)
#define __u_assert_str_eq_failed(a, b)		\
  __u_assert_str_eq_output(a, b, failed, -1)

#endif
