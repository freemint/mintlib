#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <unistd.h>
#include <osbind.h>
#include <mintbind.h>
#include <errno.h>

int
__setreuid (int ruid, int euid)
{
	long r;
	static short have_setreuid = 1;

  	if (have_setreuid) {
		r = Psetreuid(ruid, euid);
                if (r == -ENOSYS)
 			have_setreuid = 0;
		else if (r < 0) {
			if (r == -EACCES)
				r = -EPERM;
			__set_errno ((int) -r);
			return -1; 
		}
		else
			return 0;
			
	}
	return setuid(euid);
}

weak_alias (__setreuid, setreuid)
