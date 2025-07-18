/*  wait3.c -- MiNTLib, 64bit version */

#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include "lib.h"

pid_t __wait3_time64 (__WP stat_loc, int options, struct rusage64 *usage)
{
	return __wait4_time64 (-1, stat_loc, options, usage);
}
