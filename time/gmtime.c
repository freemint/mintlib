/*  gmtime.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the FreeType project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/*  This file is derived from localtime.c from the tz database.
    localtime.c is in the public domain, so clarified as of
    1996-06-05 by Arthur David Olson (arthur_david_olson@nih.gov).
*/

#include <stdlib.h>
#include "tzstruct.h"

static char wildabbr[] = "WILDABBR";

struct tm* gmtime (const time_t* timep)
{
  __gmtsub (timep, 0L, &__tmbuf);
  return &__tmbuf;
}

struct tm* gmtime_r (const time_t* timep, struct tm* tm)
{
  __gmtsub (timep, 0L, tm);
  return tm;
}

/* __gmtsub is to gmtime as __localsub is to localtime.  */
void __gmtsub (const time_t* timep, long offset, struct tm* tmp)
{
  if (!__gmt_is_set) 
    {
      __gmt_is_set = 1;
      __gmtptr = (struct state*) malloc (sizeof *__gmtptr);
      if (__gmtptr != NULL && __tzload ("GMT", __gmtptr) != 0)
        (void) __tzparse ("GMT", __gmtptr, 1);
     }
   
   __timesub (timep, offset, __gmtptr, tmp);
   
   /* Could get fancy here and deliver something such as
      "UTC+xxxx" or "UTC-xxxx" if offset is non-zero,
      but this is no time for a treasure hunt.  */
   
   if (offset != 0)
     {
       tmp->TM_ZONE = wildabbr;
     }
   else 
     {
       if (__gmtptr == NULL)
         tmp->TM_ZONE = "GMT";
       else    
         tmp->TM_ZONE = __gmtptr->chars;
     }
}
