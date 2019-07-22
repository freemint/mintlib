/*  time.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "support.h"
#include "lib.h"

#ifndef N_
# define N_(String) String
#endif

#ifndef _
# define _(String) N_(String)
#endif

#define ERR(s, o) s "\0"
#define NONE
static char const _sys_err_msgs[] = {
	"Unknown error" "\0"
#include "strerror.h"
};
 

#define ERR(s, o) o,
#define NONE 0,
static unsigned short const _sys_errlist_internal[] = {
#include "strerror.h"
};
 
/* Map error number to descriptive string.  */

static char unknown_error2[] = N_("Unknown error 1234567890");

#define SYS_NERR (unsigned int) (sizeof (_sys_errlist_internal) / sizeof (_sys_errlist_internal[0]))

char *strerror(int errnum)
{
	if ((unsigned int)errnum < SYS_NERR)
		return (char *) NO_CONST(_(&_sys_err_msgs[_sys_errlist_internal[errnum]]));
#ifdef __MINT__
	_ultoa(errnum, unknown_error2 + sizeof("Unknown error ") - 1, 10);
#else
	sprintf(unknown_error2 + sizeof("Unknown error ") - 1, "%u", errnum);
#endif
	return unknown_error2;
}


#ifdef MAIN

#define ERR(s, o) s,
#define NONE 0,
static const char *const _new_sys_errlist_internal[] = {
#include "strerror.h"
};

#undef SYS_NERR
#define SYS_NERR (unsigned int) (sizeof (_new_sys_errlist_internal) / sizeof (_new_sys_errlist_internal[0]))

int main(void)
{
	unsigned int i;
	unsigned int offset = sizeof("Unknown error");
	
	for (i = 0; i < SYS_NERR; i++)
	{
		printf("%u: %u: %s\n", i, offset, _new_sys_errlist_internal[i]);
		if (_new_sys_errlist_internal[i])
			offset += strlen(_new_sys_errlist_internal[i]) + 1;
	}
	return 0;
}
#endif
