
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

int
__setregid (gid_t rgid, gid_t egid)
{
	static short have_setregid = 1;

	if (have_setregid) {
		long r;

		r = Psetregid (rgid, egid);
		if (r == -ENOSYS) {
			have_setregid = 0;
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
	return __setgid (egid);
}
weak_alias (__setregid, setregid)
