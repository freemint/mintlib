
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

uid_t
__geteuid (void)
{
	static short have_geteuid = 1;

	if (have_geteuid) {
		long r;

		r = Pgeteuid ();
		if (r == -ENOSYS)
			have_geteuid = 0;
		else
			return (uid_t) r;
	}

	return getuid ();
}
weak_alias (__geteuid, geteuid)
