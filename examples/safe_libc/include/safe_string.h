#ifndef SAFE_STRING_H
#define SAFE_STRING_H

#include <stddef.h> /* cheat */
#include <return.h>

typedef struct {
  void *addr;
  size_t size;
} mem_t;

ret_t safe_memcpy(mem_t *dest, const mem_t *src, size_t n);
ret_t safe_memset(mem_t *s, int c, size_t n);
ret_t safe_memcmp(const mem_t *s1, const mem_t *s2, size_t n, int *ret);

/* str ops */

#define STR_MAX 256

typedef struct {
  char c_str[STR_MAX];
} str_t;

ret_t safe_strnlen(str_t *s, size_t n, size_t *ret);
ret_t safe_strncpy(str_t *dst, const str_t *src, size_t n);
ret_t safe_strncat(str_t *dst, const str_t *src, size_t n);
ret_t safe_strncmp(const str_t *s1, const str_t *s2, size_t n, int *ret);


/* lazy shortcuts */
#define safe_strlen(a, b) safe_strnlen(a, STR_MAX, b)
#define safe_strcpy(a, b) safe_strncpy(a, b, STR_MAX)
#define safe_strcat(a, b) safe_strncat(a, b, STR_MAX)
#define safe_strcmp(a, b, c) safe_strncmp(a, b, STR_MAX, c)

#endif
