/* asctime a la ISO C.  */

/*
** This file is in the public domain, so clarified as of
** 1996-06-05 by Arthur David Olson.
*/

/*
** Avoid the temptation to punt entirely to strftime;
** strftime can behave badly when tm components are out of range, and
** the output of strftime is supposed to be locale specific
** whereas the output of asctime is supposed to be constant.
*/

#include "private.h"
#include <stdio.h>

/*
** Some systems only handle "%.2d"; others only handle "%02d";
** "%02.2d" makes (most) everybody happy.
** At least some versions of gcc warn about the %02.2d;
** we conditionalize below to avoid the warning.
*/
/*
** All years associated with 32-bit time_t values are exactly four digits long;
** some years associated with 64-bit time_t values are not.
** Vintage programs are coded for years that are always four digits long
** and may assume that the newline always lands in the same place.
** For years that are less than four digits, we pad the output with
** leading zeroes to get the newline in the traditional place.
** The -4 ensures that we get four characters of output even if
** we call a strftime variant that produces fewer characters for some years.
** This conforms to recent ISO C and POSIX standards, which say behavior
** is undefined when the year is less than 1000 or greater than 9999.
*/
#define ASCTIME_FMT   "%s %s%3d %.2d:%.2d:%.2d %-4d\n"
#define ASCTIME_FMT_B "%s %s%3d %.2d:%.2d:%.2d     %-4d\n"

#define STD_ASCTIME_BUF_SIZE	26
/*
** Big enough for something such as
** ??? ???-2147483648 -2147483648:-2147483648:-2147483648     -2147483648\n
** (two three-character abbreviations, five strings denoting integers,
** seven explicit spaces, two explicit colons, a newline,
** and a trailing NUL byte).
** The values above are for systems where an int is 32 bits and are provided
** as an example; the size expression below is a bound for the system at
** hand.
*/
#define MAX_ASCTIME_BUF_SIZE	(2*3+5*INT_STRLEN_MAXIMUM(int)+7+2+1+1)

static char buf_asctime[MAX_ASCTIME_BUF_SIZE];

/* A similar buffer for ctime.
   C89 requires that they be the same buffer.
   This requirement was removed in C99, so support it only if requested,
   as support is more likely to lead to bugs in badly written programs.  */
#if SUPPORT_C89
# define buf_ctime buf_asctime
#else
static char buf_ctime[sizeof buf_asctime];
#endif

/*
** A la ISO/IEC 9945-1, ANSI/IEEE Std 1003.1, 2004 Edition.
*/

/* Publish asctime_r and ctime_r only when supporting older POSIX.  */
#if SUPPORT_POSIX2008
# define asctime_static
#else
# define asctime_static static
# undef asctime_r
# undef ctime_r
# define asctime_r static_asctime_r
# define ctime_r static_ctime_r
#endif

asctime_static
char *asctime_r(const struct tm *__restrict timeptr, char *__restrict buf)
{
	static const char wday_name[][4] = {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	static const char mon_name[][4] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	const char *wn;
	const char *mn;
	int year;
	char result[MAX_ASCTIME_BUF_SIZE];
	int len;

	if (timeptr == NULL)
	{
		errno = EINVAL;
		return strcpy(buf, "??? ??? ?? ??:??:?? ????\n");
	}
	if (timeptr->tm_wday < 0 || timeptr->tm_wday >= DAYSPERWEEK)
		wn = "???";
	else
		wn = wday_name[timeptr->tm_wday];
	if (timeptr->tm_mon < 0 || timeptr->tm_mon >= MONSPERYEAR)
		mn = "???";
	else
		mn = mon_name[timeptr->tm_mon];
	year = timeptr->tm_year;
	/* We limit the size of the year which can be printed.  Using the %d
       format specifier used the addition of 1900 would overflow the
       number and a negative value is printed.  For some architectures we
       could in theory use %ld or an even larger integer format but
       this would mean the output needs more space.  This would not be a
       problem if the 'asctime_r' interface would be defined sanely and
       a buffer size would be passed.  */
    if (year > INT_MAX - TM_YEAR_BASE)
	{
		errno = EOVERFLOW;
		return NULL;
	}
	/*
	 ** We avoid using snprintf since it's not available on all systems.
	 */
	len = sprintf(result,
		-999 - TM_YEAR_BASE <= year && year <= 9999 - TM_YEAR_BASE ? ASCTIME_FMT : ASCTIME_FMT_B,
		wn, mn, timeptr->tm_mday, timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec, year + TM_YEAR_BASE);
	if (len < STD_ASCTIME_BUF_SIZE || buf == buf_asctime || buf == buf_ctime)
		return strcpy(buf, result);
	else
	{
		errno = EOVERFLOW;
		return NULL;
	}
}

/*
** A la ISO/IEC 9945-1, ANSI/IEEE Std 1003.1, 2004 Edition.
*/

char *asctime(const struct tm *timeptr)
{
	return asctime_r(timeptr, buf_asctime);
}
