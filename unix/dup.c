/* from Dale Schumacher's dLibs library */

/* will have to be adjusted at some time ++jrb */
/* use with caution, TOS 1.4 still has double re-direction bug! */

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include "lib.h"

int
__dup (int handle)
{
	register int rv;
	long flags;

	if ((rv = (int)Fcntl(handle, (long)0, F_DUPFD)) == -ENOSYS)
		rv = (int)Fdup(handle);

	if (rv < (__SMALLEST_VALID_HANDLE)) {
		__set_errno (-rv);
		rv = -1;
	}
	else
	{
		if (__OPEN_INDEX(rv) < __NHANDLES) {
			__open_stat[__OPEN_INDEX(rv)] =
				__open_stat[__OPEN_INDEX(handle)];
		}
		
		if ((flags = (long)Fcntl(rv, (long)0, F_GETFD)) != -ENOSYS)
			(void)Fcntl(rv, flags & ~FD_CLOEXEC, F_SETFD);
	}
	return(rv);
}
weak_alias (__dup, dup)
