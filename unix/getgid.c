#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <unistd.h>
#include <mintbind.h>
#include <errno.h>

extern gid_t __gid;

gid_t
__getgid()
{
	long r;
	static short have_getgid = 1;

	if (have_getgid) {
		r = Pgetgid();
		if (r == -ENOSYS)
			have_getgid = 0;
		else
			return (gid_t)r;
	}
	return __gid;
}

weak_alias (__getgid, getgid)
