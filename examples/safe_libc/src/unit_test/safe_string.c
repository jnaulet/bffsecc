#include "u_test.h"
#include "../safe_string.c"

INIT_U_TESTS(safe_string);

U_TEST(test_mem_valid)
{
  u_assert(mem_valid(NULL, 1) == ARG_INVALID);
  u_assert(mem_valid(NOT_NULL, 0) == ARG_INVALID);

  mem_t mem1 = { NULL, 1 };
  u_assert(mem_valid(&mem1, 1) == MEM_NULL_PTR);
  mem_t mem2 = { NOT_NULL, 5 };
  u_assert(mem_valid(&mem2, 10) == MEM_TOO_SMALL);
  mem_t mem3 = { NOT_NULL, 10 };
  u_assert(mem_valid(&mem3, 10) == SUCCESS);
}

U_TEST(test_no_overlap)
{
  /* args */
  u_assert(no_overlap(NULL, NOT_NULL, 1) == ARG_INVALID);
  u_assert(no_overlap(NOT_NULL, NULL, 1) == ARG_INVALID);
  u_assert(no_overlap(NOT_NULL, NOT_NULL, 0) == ARG_INVALID);
  /* internals */
  mem_t mem1 = { NULL, 1 };
  mem_t mem2 = { NOT_NULL, 1 };
  u_assert(no_overlap(&mem1, &mem2, 1) == MEM_INVALID);
  u_assert(no_overlap(&mem2, &mem1, 1) == MEM_INVALID);
  /* overlap */
  mem_t mem3 = { (void*)1000, 2000 };
  mem_t mem4 = { (void*)2000, 2000 };
  u_assert(no_overlap(&mem3, &mem4, 2000) == FAILURE);
  u_assert(no_overlap(&mem3, &mem4, 1000) == SUCCESS);
}

U_TEST(test_safe_memcpy)
{
  /* args */
  u_assert(safe_memcpy(NULL, NOT_NULL, 1) == ARG_INVALID);
  u_assert(safe_memcpy(NOT_NULL, NULL, 1) == ARG_INVALID);
  u_assert(safe_memcpy(NOT_NULL, NOT_NULL, 0) == ARG_INVALID);
  /* internals */
  mem_t mem1 = { NULL, 1 };
  mem_t mem2 = { NOT_NULL, 1 };
  u_assert(safe_memcpy(&mem1, &mem2, 1) == MEM_INVALID);
  u_assert(safe_memcpy(&mem2, &mem1, 1) == MEM_INVALID);
  /* overlap */
  char c0[512];
  mem_t mem3 = { c0, sizeof(c0) };
  mem_t mem4 = { c0 + 128, 256 };
  u_assert(safe_memcpy(&mem3, &mem4, 200) == MEM_OVERLAP);
  u_assert(safe_memcpy(&mem3, &mem4, 128) == SUCCESS);
  /* normal use */
  char c1[256], c2[512] = { "0123456789abcdef" };
  mem_t mem5 = { c1, sizeof(c1) };
  mem_t mem6 = { c2, sizeof(c2) };
  u_assert(safe_memcpy(&mem5, &mem6, 17) == SUCCESS);
  u_assert_str_eq(c1, "0123456789abcdef");
}

U_TEST(test_safe_memset)
{
  /* args */
  u_assert(safe_memset(NULL, 0, 1) == ARG_INVALID);
  u_assert(safe_memset(NOT_NULL, -1, 1) == ARG_INVALID);
  u_assert(safe_memset(NOT_NULL, 0, 0) == ARG_INVALID);
  /* internals */
  mem_t mem1 = { NULL, 1 };
  u_assert(safe_memset(&mem1, 0, 1) == MEM_INVALID);
  /* memset */
  char c[512];
  mem_t mem2 = { c, sizeof(c) };
  u_assert(safe_memset(&mem2, 0xc, 129) == SUCCESS);
  u_assert_eq(c[128], 0xc);
}

U_TEST(test_safe_memcmp)
{
  /* args */
  u_assert(safe_memcmp(NULL, NOT_NULL, 1, NOT_NULL) == ARG_INVALID);
  u_assert(safe_memcmp(NOT_NULL, NULL, 1, NOT_NULL) == ARG_INVALID);
  u_assert(safe_memcmp(NOT_NULL, NOT_NULL, 0, NOT_NULL) == ARG_INVALID);
  u_assert(safe_memcmp(NOT_NULL, NOT_NULL, 1, NULL) == ARG_INVALID);
  /* internals */
  mem_t mema = { NULL, 1 };
  mem_t memb = { NOT_NULL, 1 };
  u_assert(safe_memcmp(&mema, &memb, 1, NOT_NULL) == MEM_INVALID);
  u_assert(safe_memcmp(&memb, &mema, 1, NOT_NULL) == MEM_INVALID);
  /* success */
  int ret;
  char c1[256] = { "0123456789abcdef" };
  char c2[256] = { "0123456789abcdefg" };
  mem_t mem1 = { c1, sizeof(c1) };
  mem_t mem2 = { c2, sizeof(c2) };
  u_assert(safe_memcmp(&mem1, &mem2, 16, &ret) == SUCCESS);
  u_assert_eq(ret, 0);
  u_assert(safe_memcmp(&mem1, &mem2, 17, &ret) == SUCCESS);
  u_assert_eq(ret, -'g');
}

/* str ops */

#define STR_256						\
  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"			\
  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"			\
  "cccccccccccccccccccccccccccccccc"			\
  "dddddddddddddddddddddddddddddddd"			\
  "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"			\
  "ffffffffffffffffffffffffffffffff"			\
  "gggggggggggggggggggggggggggggggg"			\
  "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
#define STR_255						\
  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"			\
  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"			\
  "cccccccccccccccccccccccccccccccc"			\
  "dddddddddddddddddddddddddddddddd"			\
  "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"			\
  "ffffffffffffffffffffffffffffffff"			\
  "gggggggggggggggggggggggggggggggg"			\
  "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"

U_TEST(test_safe_strnlen)
{
  /* args */
  u_assert(safe_strnlen(NULL, 1, NOT_NULL) == ARG_INVALID);
  u_assert(safe_strnlen(NOT_NULL, 0, NOT_NULL) == ARG_INVALID);
  u_assert(safe_strnlen(NOT_NULL, STR_MAX + 1, NOT_NULL) == ARG_INVALID);
  u_assert(safe_strnlen(NOT_NULL, 1, NULL) == ARG_INVALID);
  /* normal op */
  size_t ret;
  str_t str0 = { "" };
  str_t str1 = { "0123456789abcdef" };
  str_t str2 = { STR_256 };
  /* str is 0 */
  u_assert(safe_strnlen(&str0, 1, &ret) == SUCCESS);
  u_assert_eq(ret, 0);
  /* str is 8 */
  u_assert(safe_strnlen(&str1, 8, &ret) == SUCCESS);
  u_assert_eq(ret, 8);
  /* str is 16 */
  u_assert(safe_strnlen(&str1, 24, &ret) == SUCCESS);
  u_assert_eq(ret, 16);  
  /* str is max */
  u_assert(safe_strnlen(&str2, STR_MAX, &ret) == SUCCESS);
  u_assert_eq(ret, STR_MAX);
}

U_TEST(test_safe_strncpy)
{
  /* args */
  u_assert(safe_strncpy(NULL, NOT_NULL, 1) == ARG_INVALID);
  u_assert(safe_strncpy(NOT_NULL, NULL, 1) == ARG_INVALID);
  u_assert(safe_strncpy(NOT_NULL, NOT_NULL, 0) == ARG_INVALID);
  u_assert(safe_strncpy(NOT_NULL, NOT_NULL, STR_MAX + 1) == ARG_INVALID);
  /* overlap */
  u_assert(safe_strncpy(NOT_NULL, NOT_NULL, 1) == MEM_OVERLAP);
  /* success */
  str_t str0 = { "" };
  str_t str1 = { "" };
  str_t str2 = { "0123456789abcdef" };
  str_t str3 = { STR_256 };
  u_assert(safe_strncpy(&str0, &str1, STR_MAX) == SUCCESS);
  u_assert(safe_strncpy(&str0, &str2, STR_MAX) == SUCCESS);
  u_assert(safe_strncpy(&str0, &str3, STR_MAX) == SUCCESS);
}

U_TEST(test_safe_strncat)
{
  /* args */
  u_assert(safe_strncat(NULL, NOT_NULL, 1) == ARG_INVALID);
  u_assert(safe_strncat(NOT_NULL, NULL, 1) == ARG_INVALID);
  u_assert(safe_strncat(NOT_NULL, NOT_NULL, 0) == ARG_INVALID);
  u_assert(safe_strncat(NOT_NULL, NOT_NULL, STR_MAX + 1) == ARG_INVALID);
  /* internals */
  str_t str0 = { "0123456789" };
  str_t str1 = { "abcdef" };
  u_assert(safe_strncat(&str0, &str1, 8) == STR_TOO_LONG);
  /* success */
  u_assert(safe_strncat(&str0, &str1, 16) == SUCCESS);
  u_assert_str_eq(str0.c_str, "0123456789abcdef");
  /* TODO: max */
}

U_TEST(test_safe_strncmp)
{
  /* args */
  u_assert(safe_strncmp(NULL, NOT_NULL, 1, NOT_NULL) == ARG_INVALID);
  u_assert(safe_strncmp(NOT_NULL, NULL, 1, NOT_NULL) == ARG_INVALID);
  u_assert(safe_strncmp(NOT_NULL, NOT_NULL, 0, NOT_NULL) == ARG_INVALID);
  u_assert(safe_strncmp(NOT_NULL, NOT_NULL, STR_MAX + 1, NOT_NULL) == ARG_INVALID);
  u_assert(safe_strncmp(NOT_NULL, NOT_NULL, 1, NULL) == ARG_INVALID);
  /* overlap */
  u_assert(safe_strncmp(NOT_NULL, NOT_NULL, 1, NOT_NULL) == MEM_OVERLAP);
  /* success */
  int ret;
  str_t str0 = { "0123456789" };
  str_t str1 = { "abcdef" };
  str_t str2 = { "0123456789" };
  u_assert(safe_strcmp(&str0, &str1, &ret) == SUCCESS);
  u_assert_eq(ret, ('0' - 'a'));
  u_assert(safe_strcmp(&str0, &str2, &ret) == SUCCESS);
  u_assert_eq(ret, 0);
}

U_TESTS {
  /* mem ops */
  RUN_U_TEST(test_mem_valid);
  RUN_U_TEST(test_no_overlap);
  RUN_U_TEST(test_safe_memcpy);
  RUN_U_TEST(test_safe_memset);
  RUN_U_TEST(test_safe_memcmp);
  /* str ops */
  RUN_U_TEST(test_safe_strnlen);
  RUN_U_TEST(test_safe_strncpy);
  RUN_U_TEST(test_safe_strncat);
  RUN_U_TEST(test_safe_strncmp);
  END_U_TESTS;
}
