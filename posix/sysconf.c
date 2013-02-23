/*
 * sysconf() for TOS/MiNT (kinda POSIXy)
 * Written by Dave Gymer and placed in the Public Domain
 *
 * NOTE: this file will have to be updated as and when MiNT gains
 * new Sysconf() and Dpathconf() variables, as will unistd.h, so that
 * TOS programs get the correct values back. (But who uses TOS? :-)
 */

#include <unistd.h>
#include <mintbind.h>
#include <errno.h>
#include <limits.h>
#include "lib.h"

#define UNLIMITED	(0x7fffffffL)

long
__sysconf (int var)
{
	long r;

	if ((r = Sysconf(var)) != -ENOSYS)
	  {
	    if (r < 0)
	      return -1;
	    else
	      return r;
	  }

	switch(var) {
	case _SC_LAST:
		return 4;
	case _SC_MEMR_MAX:
		return UNLIMITED; /* not true for TOS < 1.4 :-( */
	case _SC_ARG_MAX:
		return 127; /* ignore this, cuz we can pass via the env */
	case _SC_OPEN_MAX:
		/* XXX TOS reports less than this using a short test app. */
		return 32;
	case _SC_NGROUPS_MAX:
		return NGROUPS_MAX;
	case _SC_CHILD_MAX:
		return UNLIMITED; /* good 'ol TOS :-) */
	default:
		return -1;
	}
}
weak_alias (__sysconf, sysconf)
