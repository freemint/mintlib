/* dummy implementations for strcoll and strxfrm, that doesn't know about
   locales */

#include <string.h>

size_t
strxfrm (to, from, maxsize)
     char *to;
     const char *from;
     size_t maxsize;
{
  (void)strncpy (to, from, maxsize - 1);
  to[maxsize] = '\0';
  return strlen (to);
}
