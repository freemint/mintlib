/* ctermid() emulation by entropy@terminator.rs.itd.umich.edu
   Public domain.
   DO NOT USE THIS FUNCTION!
   It is provided for System V compatibility only.
*/

#define _POSIX_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *
cuserid(s)
  char *s;
{
  static char name[L_cuserid];
  char *t;

  if (!s)
    s = name;
  t = getlogin();
  if (t)
    strncpy(s, t, L_cuserid);
  else
    s[0] = '\0';
  s[L_cuserid - 1] = '\0';
  return s;
}
