#define _GNU_SOURCE 1
#include <stdio.h>
#include <string.h>
#ifndef __MINT__
#include <wctype.h>
#include <wchar.h>
#else
#include <sys/types.h>
#include <stdlib.h>
#endif

int
main (void)
{
  wchar_t tmp[3];
  tmp[0] = '8';
  tmp[1] = '1';
  tmp[2] = 0;

  printf ("Test for wide character output with printf\n");

  printf ("with %%S: %S\n", tmp);

  printf ("with %%C: %C\n", tmp[0]);

  return 0;
}
