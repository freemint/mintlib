
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <mint/mintbind.h>

#include "lib.h"

gid_t
__getegid (void)
{
	static short have_getegid = 1;

	if (have_getegid) {
		long r;
		
		r = Pgetegid ();
		if (r == -ENOSYS)
			have_getegid = 0;
		else
			return (gid_t) r;
	}
	
	return getgid ();	     
}
weak_alias (__getegid, getegid)
