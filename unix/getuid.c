
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

#include "lib.h"

extern uid_t __uid;

uid_t
__getuid (void)
{
	static short have_getuid = 1;

	if (have_getuid) {
		long r;
		
		r = Pgetuid ();
		if (r == -ENOSYS)
			have_getuid = 0;
		else
			return (uid_t) r;
	}
	
	return __uid;
}
weak_alias (__getuid, getuid)
