/* getrusage emulation for MiNT */

#include <compiler.h>
#include <osbind.h>
#include <mintbind.h>
#include <time.h>
#include <resource.h>
#include <errno.h>
#include <string.h>

#include "lib.h"


static void
_ms2tval(unsigned long milliseconds, struct timeval *tval)
{
	tval->tv_sec = milliseconds/1000;
	tval->tv_usec = (milliseconds % 1000) * 1000;
}

#if 0
static void
_add_tval(struct timeval *orig, struct timeval *new)
{
	long t;

	t = orig->tv_usec + new->tv_usec;
	if (t > 1000000L) {
		orig->tv_sec += t/1000000L;
		t = t % 1000000L;
	}
	orig->tv_usec = t;
	orig->tv_sec += new->tv_sec;
}
#endif

int 
__getrusage(__rusage_who_t which, struct rusage *data)
{
	long r;
	long usage[8];

	memset(data, 0, sizeof(*data));
	
	r = Prusage(usage);

	if (r < 0 && r != -ENOSYS) {
		__set_errno (-r);
		return -1;
	} else if (r == -ENOSYS) {
		usage[0] = usage[2] = usage[4] = 0;
		/*
		 * Both _clock() and _childtime are measured in clock ticks.
		 * Convert to milliseconds to match Prusage system call.
		 */
		usage[1] = (_clock() - _childtime) * (1000L / CLOCKS_PER_SEC);
		usage[3] = _childtime * (1000L / CLOCKS_PER_SEC);
	}

	if (which == RUSAGE_SELF) {
		_ms2tval(usage[0], &(data->ru_stime));
		_ms2tval(usage[1], &(data->ru_utime));
		data->ru_maxrss = usage[4];
	}
	else if (which == RUSAGE_CHILDREN) {
		_ms2tval(usage[2], &(data->ru_stime));
		_ms2tval(usage[3], &(data->ru_utime));
	}
	return 0;
}

weak_alias (__getrusage, getrusage)
