
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

extern uid_t __uid;

int
__setuid (uid_t x)
{
	static short have_setuid = 1;

	if (have_setuid) {
		long r;
		
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
