#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <unistd.h>
#include <osbind.h>
#include <mintbind.h>
#include <errno.h>

extern gid_t __gid;

#include "lib.h"

int
__setgid(x)
  int x;
{
  	long r;
	static short have_setgid = 1;

	if (have_setgid) {
		r = Psetgid(x);
                if (r == -ENOSYS) {
			__gid = x;
 			have_setgid = 0;
		}
		else if (r < 0) {
			__set_errno (-r);
			return -1; 
		}
		return 0;		
	}	
	__gid = x;
	return 0;
}

weak_alias (__setgid, setgid)
