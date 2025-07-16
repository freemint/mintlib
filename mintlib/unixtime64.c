/*  unixtime.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <time.h>
#include <support.h>
#include "lib.h"

/* Convert a GEMDOS time to seconds since the epoch.
   The calculated value is always in UTC.  */
void __unixtime64(__time64_t *t, unsigned timestamp, unsigned datestamp)
{
	struct tm tmbuf;
	struct tm *tm = &tmbuf;

	tm->tm_sec = (timestamp & 31) << 1;
	tm->tm_min = (timestamp >> 5) & 63;
	tm->tm_hour  = (timestamp >> 11) & 31;

	tm->tm_mday  = datestamp & 31;
	tm->tm_mon = ((datestamp >> 5) & 15) - 1;
	tm->tm_year = 80 + ((datestamp >> 9) & 127);
	tm->tm_isdst = -1;

	*t = __mktime64(tm);
}
