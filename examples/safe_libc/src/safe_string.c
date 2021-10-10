#include "e_assert.h"
#include "safe_string.h"

#include <stdbool.h>

/* suspicious shortcut */
static ret_t mem_valid(const mem_t *s, size_t n)
{
  /* args */
  if(!e_assert(s != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;
  
  if(s->addr == NULL)
    return MEM_NULL_PTR;
  
  if(n > s->size)
    return MEM_TOO_SMALL;
  
  return SUCCESS;
}

static ret_t no_overlap(const mem_t *s1, const mem_t *s2, size_t n)
{
  if(!e_assert(s1 != NULL)) return ARG_INVALID;
  if(!e_assert(s2 != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;

  /* internals */
  if(!e_assert(mem_valid(s1, n) == 0)) return MEM_INVALID;
  if(!e_assert(mem_valid(s2, n) == 0)) return MEM_INVALID;
  
  /* check overlap of 2 mem zones */
  char *s1_min = (char*)s1->addr;
  char *s1_max = (char*)s1->addr + n;
  char *s2_min = (char*)s2->addr;
  char *s2_max = (char*)s2->addr + n;

  if(s1_min >= s2_min && s1_min < s2_max) return FAILURE;
  if(s2_min >= s1_min && s2_min < s1_max) return FAILURE;
  return SUCCESS;
}

ret_t safe_memcpy(mem_t *dest, const mem_t *src, size_t n)
{
  if(!e_assert(dest != NULL)) return ARG_INVALID;
  if(!e_assert(src != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;
  
  /* internals */
  if(!e_assert(mem_valid(dest, n) == 0)) return MEM_INVALID;
  if(!e_assert(mem_valid(src, n) == 0)) return MEM_INVALID;
  if(!e_assert(no_overlap(dest, src, n) == 0)) return MEM_OVERLAP;

  /* dirty copy */
  size_t i;
  char *pdest = (char*)dest->addr;
  const char *psrc = (const char*)src->addr;

  for(i = 0; i < n; i++)
    pdest[i] = psrc[i];
  
  return SUCCESS;
}

ret_t safe_memset(mem_t *s, int c, size_t n)
{
  if(!e_assert(s != NULL)) return ARG_INVALID;
  if(!e_assert(c >= 0)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;

  /* internals checking */
  if(!e_assert(mem_valid(s, n) == 0)) return MEM_INVALID;
  
  /* dirty set */
  size_t i;
  char *ps = (char*)s->addr;

  for(i = 0; i < n; i++)
    ps[i] = (char)0xff & c;

  return SUCCESS;
}

ret_t safe_memcmp(const mem_t *s1, const mem_t *s2, size_t n, int *ret)
{
  if(!e_assert(s1 != NULL)) return ARG_INVALID;
  if(!e_assert(s2 != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;
  if(!e_assert(ret != NULL)) return ARG_INVALID;

  /* internals checking */
  if(!e_assert(mem_valid(s1, n) == 0)) return MEM_INVALID;
  if(!e_assert(mem_valid(s2, n) == 0)) return MEM_INVALID;
  
  /* dirty cmp */
  size_t i;
  const char *ps1 = (const char*)s1->addr;
  const char *ps2 = (const char*)s2->addr;

  for(i = 0; i < n; i++){
    *ret = (int)(ps1[i] - ps2[i]);
    if(*ret != 0) break;
  }
  
  return SUCCESS;
}

/* str ops */

ret_t safe_strnlen(str_t *s, size_t n, size_t *ret)
{
  if(!e_assert(s != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;
  if(!e_assert(n <= STR_MAX)) return ARG_INVALID;
  if(!e_assert(ret != NULL)) return ARG_INVALID;
  
  size_t i;
  for(i = 0; i < n; i++){
    if(s->c_str[i] == (char)0)
      break;
  }

  *ret = i;
  return SUCCESS;
}

ret_t safe_strncpy(str_t *dst, const str_t *src, size_t n)
{
  if(!e_assert(dst != NULL)) return ARG_INVALID;
  if(!e_assert(src != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;
  if(!e_assert(n <= STR_MAX)) return ARG_INVALID;
  /* overlap */
  if(!e_assert(dst != src)) return MEM_OVERLAP;
  
  /* dirty copy */
  size_t i;
  for(i = 0; i < n; i++){
    dst->c_str[i] = src->c_str[i];
    if(dst->c_str[i] == (char)0)
      break;
  }

  return SUCCESS;
}

ret_t safe_strncat(str_t *dst, const str_t *src, size_t n)
{
  /* args */
  if(!e_assert(dst != NULL)) return ARG_INVALID;
  if(!e_assert(src != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;
  if(!e_assert(n <= STR_MAX)) return ARG_INVALID;
  /* overlap */
  if(!e_assert(dst != src)) return MEM_OVERLAP;

  ret_t res;
  size_t dst_len = 0;
  
  /* got to the end of the dst str */
  if((res = safe_strnlen(dst, n, &dst_len)) != SUCCESS)
    return res;

  /* abnormal condition */
  if(!e_assert(n > dst_len))
    return STR_TOO_LONG;
  
  /* append */
  size_t i;
  int j = 0;
  
  for(i = dst_len; i < n; i++){
    dst->c_str[i] = src->c_str[j++];
    if(dst->c_str[j] == (char)0)
      break;
  }

  return SUCCESS;
}

ret_t safe_strncmp(const str_t *s1, const str_t *s2, size_t n, int *ret)
{
  /* args */
  if(!e_assert(s1 != NULL)) return ARG_INVALID;
  if(!e_assert(s2 != NULL)) return ARG_INVALID;
  if(!e_assert(n > 0)) return ARG_INVALID;
  if(!e_assert(n <= STR_MAX)) return ARG_INVALID;
  if(!e_assert(ret != NULL)) return ARG_INVALID;
  /* overlap */
  if(!e_assert(s1 != s2)) return MEM_OVERLAP;
  
  /* dirty compare */
  size_t i;
  for(i = 0; i < n; i++){
    *ret = (int)(s1->c_str[i] - s2->c_str[i]);
    if(*ret != 0) break;
    /* other out conditions */
    if(s1->c_str[i] == (char)0) break;
    if(s2->c_str[i] == (char)0) break;
  }

  return SUCCESS;
}
