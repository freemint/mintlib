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
seteuid(x)
  int x;
{
	long r;
	static short have_seteuid = 1;

  	if (have_seteuid) {
		r = Pseteuid(x);
                if (r == -ENOSYS)
 			have_seteuid = 0;
		else if (r < 0) {
			if (r == -EACCES)
				r = -EPERM;
			__set_errno ((int) -r);
			return -1; 
		}
		else
			return 0;
			
	}
	return setuid(x);
}
