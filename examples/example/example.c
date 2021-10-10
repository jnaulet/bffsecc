#include <errno.h>
#include <stdio.h>

#include "e_assert.h"

static ssize_t example(size_t size)
{
  /* vars */
  int n;
  size_t i;
  
  /* asserts */
  if(!e_assert(size > 0)) return (ssize_t)-EINVAL;
  
  n = printf("ex");
  for(i = 0; i < size; i++) n += printf("a");
  n += printf("mple\n");
  
  return (ssize_t)n;
}

static void usage(char *argv0)
{
  (void)fprintf(stderr, "usage: %s number\n", argv0);
}

#ifndef UNIT_TESTS

/*
 * main
 */
int main(int argc, char **argv)
{
  /* vars */
  int val = 0;

  /* asserts */
  if(!e_assert(argc > 1)){
    usage(argv[0]);
    return -1;
  }
  
  (void)sscanf(argv[1], "%d", &val);
  return (int)example((size_t)val);
}

#endif
