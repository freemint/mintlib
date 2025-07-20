#include "private.h"

#ifndef WILDABBR
/*
** Someone might make incorrect use of a time zone abbreviation:
**	1.	They might reference tzname[0] before calling tzset (explicitly
**		or implicitly).
**	2.	They might reference tzname[1] before calling tzset (explicitly
**		or implicitly).
**	3.	They might reference tzname[1] after setting to a time zone
**		in which Daylight Saving Time is never observed.
**	4.	They might reference tzname[0] after setting to a time zone
**		in which Standard Time is never observed.
**	5.	They might reference tm.TM_ZONE after calling offtime.
** What's best to do in the above cases is open to debate;
** for now, we just set things up so that in any of the five cases
** WILDABBR is used. Another possibility: initialize tzname[0] to the
** string "tzname[0] used before set", and similarly for the other cases.
** And another: initialize tzname[0] to "ERA", with an explanation in the
** manual page of what this "time zone abbreviation" means (doing this so
** that tzname[0] has the "normal" length of three characters).
*/
#define WILDABBR "   "
#endif

char __tz_wildabbr[] = WILDABBR;

#if 2 <= HAVE_TZNAME + TZ_TIME_T
char *tzname[2] = {
	__tz_wildabbr,
	__tz_wildabbr
};
#endif

#if 2 <= USG_COMPAT + TZ_TIME_T
long timezone = 0;
int daylight = 0;
#endif
#if 2 <= ALTZONE + TZ_TIME_T
long altzone;
#endif


