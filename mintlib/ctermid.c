#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *
ctermid(s)
  char *s;
{
  static char name[L_ctermid];
  char *t;

  if (!s)
    s = name;
  t = ttyname(-1);
  if (t)
    strncpy(s, t, L_ctermid);
  else
    s[0] = '\0';
  s[L_ctermid - 1] = '\0';
  return s;
}
