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

int
__setuid(x)
  int x;
{
  	long r;
	static short have_setuid = 1;

	if (have_setuid) {
		r = Psetuid(x);
                if (r == -ENOSYS) {
			__uid = x;
 			have_setuid = 0;
		}
		else if (r < 0) {
			__set_errno (-r);
			return -1; 
		}
		return 0;		
	}	
	__uid = x;
	return 0;
}

weak_alias (__setuid, setuid)
