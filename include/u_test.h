#ifndef U_TEST_H
#define U_TEST_H

#define U_TEST(x)                                       \
  do {                                                  \
    fprintf(stderr, "Running %s...\n", #x);             \
    x();                                                \
  } while(0)

/* Usage:
 * UNIT_TESTS {
 *   U_TEST(a);
 *   U_TEST(b);
 *   U_TEST(c);
 * } 
 */
#define UNIT_TESTS                              \
  void main(void)

#endif
