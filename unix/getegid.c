#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <unistd.h>
#include <mintbind.h>
#include <errno.h>

#include "lib.h"

gid_t
__getegid (void)
{
	long r;
  	static short have_getegid = 1;

  	if (have_getegid) {
		r = Pgetegid();
                if (r == -ENOSYS)
 			have_getegid = 0;
		else
			return (gid_t)r;
	}
	return getgid();	     
}

weak_alias (__getegid, getegid)
