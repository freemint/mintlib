
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

int
__setegid (gid_t x)
{
	static short have_setegid = 1;

	if (have_setegid) {
		long r;

		r = Psetegid (x);
		if (r == -ENOSYS) {
			have_setegid = 0;
		}
		else if (r < 0) {
			if (r == -EACCES)
				r = -EPERM;
			__set_errno (-r);
			return -1; 
		}
		else
			return 0;
	}
	return __setgid (x);
}
weak_alias (__setegid, setegid)
