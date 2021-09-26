#ifndef U_ASSERT_H
#define U_ASSERT_H

#include <stdio.h>

#define u_assert(x)                                                     \
  ((x)                                                                  \
   ? (void)fprintf(stderr, "%s:%d assertion \'%s\' passed.\n",          \
                   __FILE__, __LINE__, #x)                              \
   : (void)fprintf(stderr, "%s:%d assertion \'%s\' failed.\n",          \
                   __FILE__, __LINE__, #x))

#define u_assert_var_equals(a, b)                                       \
  (((a) == (b))                                                         \
   ? (void)fprintf(stderr, "%s:%d %s(%ld) == %s(%ld) passed.\n",          \
                   __FILE__, __LINE__, #a, (long)a, #b, (long)b)        \
   : (void)fprintf(stderr, "%s:%d %s(%ld) == %s(%ld) failed.\n",          \
                   __FILE__, __LINE__, #a, (long)a, #b, (long)b))

#define u_assert_str_equals(a, b)                                  \
  (strcmp((a), (b))                                                \
   ? (void)fprintf(stderr, "%s:%d %s(%s) == %s(%s) passed.\n",     \
                   __FILE__, __LINE__, #a, a, #b, b)               \
   : (void)fprintf(stderr, "%s:%d %s(%s) == %s(%s) failed.\n",     \
                   __FILE__, __LINE__, #a, a, #b, b))

#endif
