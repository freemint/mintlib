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
__setregid(rgid,egid)
  int rgid, egid;

{
	long r;
	static short have_setregid = 1;

  	if (have_setregid) {
		r = Psetregid(rgid, egid);
                if (r == -ENOSYS)
 			have_setregid = 0;
		else if (r < 0) {
			if (r == -EACCES)
				r = -EPERM;
			__set_errno ((int) -r);
			return -1; 
		}
		else
			return 0;
			
	}
	return setgid(egid);
}

weak_alias (__setregid, setregid)
