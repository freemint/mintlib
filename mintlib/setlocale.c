/*
 * Routines for handling the local environment.
 * WARNING: This probably isn't in accord with the pANS standard yet.
 *
 * Written by Eric R. Smith and placed in the public domain.
 *
 */

#include <stddef.h>
#include <locale.h>

/* setlocale: set the locale.
 * FIXME: right now, only "C" is supported.
 */
char *setlocale(category, name)
        int category;
        const char *name;
{
  (void) category;
  (void) name;

  return "C";
}
