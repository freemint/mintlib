/*  strerror.c -- MiNTLib.
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

#ifndef NO_CONST
#define NO_CONST(p) ((void *)(p))
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

/*
 * compile with "gcc -Iinclude -Imintlib -DMAIN -D_LIBC string/strerror.c"
 * Then run "./a.out > string/strerror.h"
 */

#include <errno.h>

#ifndef E_OK
#define E_OK 0
#endif
#ifndef EMOUNT
#define EMOUNT 200
#endif

#define ERR(s, o) s,
#define NONE 0,
static const char *const _new_sys_errlist_internal[] = {
#include "strerror.h"
};

#undef SYS_NERR
#define SYS_NERR (unsigned int) (sizeof (_new_sys_errlist_internal) / sizeof (_new_sys_errlist_internal[0]))

static const char *errno_names[SYS_NERR] = {
#define ERR(x) [x] = #x
	ERR(E_OK),
	ERR(EERROR),
	ERR(EBUSY),
	ERR(EUKCMD),
	ERR(ECRC),
	ERR(EBADR),
	ERR(ESPIPE),
	ERR(EMEDIUMTYPE),
	ERR(ESECTOR),
	ERR(EPAPER),
	ERR(EWRITE),
	ERR(EREAD),
	ERR(EGENERIC),
	ERR(EROFS),
	ERR(ECHMEDIA),
	ERR(ENODEV),
	ERR(EBADSEC),
	ERR(ENOMEDIUM),
	ERR(EINSERT),
	ERR(EDRVNRSP),
	ERR(ESRCH),
	ERR(ECHILD),
	ERR(EDEADLK),
	ERR(ENOTBLK),
	ERR(EISDIR),
	ERR(EINVAL),
	ERR(EFTYPE),
	ERR(EILSEQ),
	ERR(ENOSYS),
	ERR(ENOENT),
	ERR(ENOTDIR),
	ERR(EMFILE),
	ERR(EACCES),
	ERR(EBADF),
	ERR(EPERM),
	ERR(ENOMEM),
	ERR(EFAULT),
	ERR(ENXIO),
	ERR(EXDEV),
	ERR(ENMFILES),
	ERR(ENFILE),
	ERR(ELOCKED),
	ERR(ENSLOCK),
	ERR(EBADARG),
	ERR(EINTERNAL),
	ERR(ENOEXEC),
	ERR(ESBLOCK),
	ERR(EBREAK),
	ERR(EXCPT),
	ERR(ETXTBSY),
	ERR(EFBIG),
	ERR(ELOOP),
	ERR(EPIPE),
	ERR(EMLINK),
	ERR(ENOTEMPTY),
	ERR(EEXIST),
	ERR(ENAMETOOLONG),
	ERR(ENOTTY),
	ERR(ERANGE),
	ERR(EDOM),
	ERR(EIO),
	ERR(ENOSPC),
	ERR(EPROCLIM),
	ERR(EUSERS),
	ERR(EDQUOT),
	ERR(ESTALE),
	ERR(EREMOTE),
	ERR(EBADRPC),
	ERR(ERPCMISMATCH),
	ERR(EPROGUNAVAIL),
	ERR(EPROGMISMATCH),
	ERR(EPROCUNAVAIL),
	ERR(ENOLCK),
	ERR(EAUTH),
	ERR(ENEEDAUTH),
	ERR(EBACKGROUND),
	ERR(EBADMSG),
	ERR(EIDRM),
	ERR(EMULTIHOP),
	ERR(ENODATA),
	ERR(ENOLINK),
	ERR(ENOMSG),
	ERR(ENOSR),
	ERR(ENOSTR),
	ERR(EOVERFLOW),
	ERR(EPROTO),
	ERR(ETIME),
	ERR(E2BIG),
	ERR(ERESTART),
	ERR(ECHRNG),
	ERR(EINTR),
	ERR(ESNDLOCKED),
	ERR(ESNDNOTLOCK),
	ERR(EL2NSYNC),
	ERR(EL3HLT),
	ERR(EL3RST),
	ERR(ELNRNG),
	ERR(EUNATCH),
	ERR(ENOCSI),
	ERR(EL2HLT),
	ERR(EBADE),
	ERR(EXFULL),
	ERR(ENOANO),
	ERR(EBADRQC),
	ERR(EBADSLT),
	ERR(EBFONT),
	ERR(ENONET),
	ERR(ENOPKG),
	ERR(EADV),
	ERR(ESRMNT),
	ERR(ECOMM),
	ERR(EDOTDOT),
	ERR(ELIBACC),
	ERR(ELIBBAD),
	ERR(ELIBSCN),
	ERR(ELIBMAX),
	ERR(ELIBEXEC),
	ERR(ESTRPIPE),
	ERR(EUCLEAN),
	ERR(ENOTNAM),
	ERR(ENAVAIL),
	ERR(EREMOTEIO),
	/* ERR(EMOUNT), */ /* should never be returned to userspace */
	ERR(ENOTSOCK),
	ERR(EDESTADDRREQ),
	ERR(EMSGSIZE),
	ERR(EPROTOTYPE),
	ERR(ENOPROTOOPT),
	ERR(EPROTONOSUPPORT),
	ERR(ESOCKTNOSUPPORT),
	ERR(EOPNOTSUPP),
	ERR(EPFNOSUPPORT),
	ERR(EAFNOSUPPORT),
	ERR(EADDRINUSE),
	ERR(EADDRNOTAVAIL),
	ERR(ENETDOWN),
	ERR(ENETUNREACH),
	ERR(ENETRESET),
	ERR(ECONNABORTED),
	ERR(ECONNRESET),
	ERR(EISCONN),
	ERR(ENOTCONN),
	ERR(ESHUTDOWN),
	ERR(ETIMEDOUT),
	ERR(ECONNREFUSED),
	ERR(EHOSTDOWN),
	ERR(EHOSTUNREACH),
	ERR(EALREADY),
	ERR(EINPROGRESS),
	ERR(EAGAIN),
	ERR(ENOBUFS),
	ERR(ETOOMANYREFS),
	ERR(ENOTSUP),
	ERR(ECANCELED),
	ERR(ECANCELED),
	ERR(EOWNERDEAD),
	ERR(ENOTRECOVERABLE),
#undef ERR
};

#ifdef __MINT__
char *_ultoa(unsigned long n, char *buffer, int radix)
{
	(void)radix;
	sprintf(buffer, "%u", (unsigned int)n);
	return buffer;
}
#endif

int main(void)
{
	unsigned int i;
	unsigned int offset = sizeof("Unknown error");
	
	for (i = 0; i < SYS_NERR; i++)
	{
		const char *name = errno_names[i];
		if (_new_sys_errlist_internal[i])
		{
			if (name == NULL)
			{
				fprintf(stderr, "string defined for unknown errno number %u\n", i);
				name = "";
			}
			printf("  /* %3u - %s */%*.sERR(N_(\"%s\"), %u)\n", i, name, (int)(21 - strlen(name)), "", _new_sys_errlist_internal[i], offset);
			offset += strlen(_new_sys_errlist_internal[i]) + 1;
		} else
		{
			if (name != NULL)
			{
				fprintf(stderr, "no string defined for %s\n", name);
			}
			printf("  /* %3u */                        NONE\n", i);
		}
	}
	printf("\n");
	printf("#undef ERR\n");
	printf("#undef NONE\n");

	return 0;
}
#endif
