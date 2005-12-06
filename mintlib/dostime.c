/* utime -- set the file modification time of the given file
 * according to the time given; a time of 0 means the current
 * time.
 *
 * All times are in Unix format, i.e. seconds since to
 * midnight, January 1, 1970 GMT
 *
 * written by Eric R. Smith, and placed in the public domain.
 *
 */
 
#include <time.h>
#include <errno.h>

#include "lib.h"

time_t __dostime (time_t t);

/* convert a Unix time into a DOS time. The longword returned contains
   the time word first, then the date word */

time_t
__dostime(t)
	time_t t;
{
        time_t time, date;
	struct tm ctm;

	if (localtime_r (&t, &ctm) == NULL)
		return 0;
	time = (ctm.tm_hour << 11) | (ctm.tm_min << 5) | (ctm.tm_sec >> 1);
	date = ((ctm.tm_year - 80) & 0x7f) << 9;
	date |= ((ctm.tm_mon+1) << 5) | (ctm.tm_mday);
	return (time << 16) | date;
}
