
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

#include "lib.h"

extern gid_t __gid;

int
__setgid (gid_t x)
{
	static short have_setgid = 1;

	if (have_setgid) {
		long r;

		r = Psetgid (x);
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
