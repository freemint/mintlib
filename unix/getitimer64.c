/*  getitimer.c -- MiNTLib, 64bit version */

#include <stdlib.h>
#include <sys/time.h>
#include "lib.h"

int __getitimer64(enum __itimer_which which, struct itimerval64 *old)
{
	return __setitimer64(which, NULL, old);
}
