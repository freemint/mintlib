#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <unistd.h>
#include <mintbind.h>
#include <errno.h>

uid_t
__geteuid()
{
	long r;
  	static short have_geteuid = 1;

  	if (have_geteuid) {
		r = Pgeteuid();
                if (r == -ENOSYS)
 			have_geteuid = 0;
		else
			return (uid_t)r;
	}
	return getuid();
}

weak_alias (__geteuid, geteuid)
