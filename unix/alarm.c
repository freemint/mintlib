/*
 * alarm: a public domain alarm for MiNT (by ers)
 */

#include <errno.h>
#include <mintbind.h>
#include <limits.h>
#include <unistd.h>

#include "lib.h"

unsigned int
__alarm (unsigned secs)
{
	static short have_talarm = 1;

	if (have_talarm) {
		long r;
#ifndef __MSHORT__
		if (secs > ((unsigned int) (LONG_MAX/1000)))
			secs = ((unsigned int) (LONG_MAX/1000));
#endif
		r = Talarm((long) secs);
		if (r == -ENOSYS)
			have_talarm = 0;
		else
			return (unsigned int) r;
	}			
	return 0;

}
weak_alias (__alarm, alarm)
