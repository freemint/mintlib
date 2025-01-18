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
#include <time.h>
#include <sys/sysinfo.h>
#include "lib.h"

#ifndef UNLIMITED
#define UNLIMITED	(0x7fffffffL)
#endif

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
		return 12;
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
		return get_child_max();
	case _SC_CLK_TCK:
		return CLOCKS_PER_SEC;
	case _SC_PAGE_SIZE:
		return getpagesize();
    case _SC_GETPW_R_SIZE_MAX:
      return -1;
    case _SC_GETGR_R_SIZE_MAX:
      return -1;
    case _SC_PHYS_PAGES:
      return get_phys_pages();
    case _SC_AVPHYS_PAGES:
      return get_avphys_pages();
	case _SC_NPROCESSORS_CONF:
      return get_nprocs_conf();
    case _SC_NPROCESSORS_ONLN:
      return get_nprocs ();
	default:
		return -1;
	}
}
weak_alias (__sysconf, sysconf)
