
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

extern gid_t __gid;

gid_t
__getgid (void)
{
	static short have_getgid = 1;

	if (have_getgid) {
		long r;
		
		r = Pgetgid ();
		if (r == -ENOSYS)
			have_getgid = 0;
		else
			return (gid_t) r;
	}
	
	return __gid;
}
weak_alias (__getgid, getgid)
