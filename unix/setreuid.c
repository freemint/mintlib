
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

int
__setreuid (uid_t ruid, uid_t euid)
{
	static short have_setreuid = 1;

	if (have_setreuid) {
		long r;

		r = Psetreuid (ruid, euid);
		if (r == -ENOSYS) {
 			have_setreuid = 0;
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
	return __setuid (euid);
}
weak_alias (__setreuid, setreuid)
