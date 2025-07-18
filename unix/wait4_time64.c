/*  wait4.c -- MiNTLib, 64bit version. */

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <mint/mintbind.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>

#include "lib.h"

pid_t __wait4_time64 (pid_t pid, __WP stat_loc, int options, struct rusage64 *usage)
{
	if (usage)
	{
		struct rusage data32;
		int r;
	
		r = wait4(pid, stat_loc, options, &data32);
		if (r == 0)
		{
			__rusage_to_rusage64(usage, &data32);
		}
		return r;
	}
	return wait4(pid, stat_loc, options, NULL);
}
