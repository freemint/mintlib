#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <unistd.h>
#include <osbind.h>
#include <mintbind.h>
#include <errno.h>

extern uid_t __uid;

#include "lib.h"

uid_t
__getuid (void)
{
	long r;
	static short have_getuid = 1;

	if (have_getuid) {
		r = Pgetuid();
		if (r == -ENOSYS)
			have_getuid = 0;
		else
			return (uid_t)r;
	}
	return __uid;
}

weak_alias (__getuid, getuid)
