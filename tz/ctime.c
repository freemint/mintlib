#include "private.h"

/*
** Section 4.12.3.2 of X3.159-1989 requires that
**	The ctime function converts the calendar time pointed to by timer
**	to local time in the form of a string. It is equivalent to
**		asctime(localtime(timer))
*/
char *ctime(const time_t *timep)
{
	/* Do not call localtime_r, as C23 requires ctime to initialize the
	   static storage that localtime updates.  */
	struct tm *tmp = localtime(timep);

	return tmp ? asctime(tmp) : NULL;
}

char *ctime_r(const time_t *timep, char *buf)
{
	struct tm mytm;
	struct tm *tmp = localtime_r(timep, &mytm);

	return tmp ? asctime_r(tmp, buf) : NULL;
}
