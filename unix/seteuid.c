
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

int
__seteuid (uid_t x)
{
	static short have_seteuid = 1;

	if (have_seteuid) {
		long r;

		r = Pseteuid (x);
		if (r == -ENOSYS) {
			have_seteuid = 0;
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
	return __setuid (x);
}
weak_alias (__seteuid, seteuid)
