/*  globals.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* This file defines various internal library variables, mainly for
   the purpose that main.c doesn't define them.  Otherwise it will
   become very hard to override _main() in special programs such
   as drivers.  */
   
#include <stdio.h>
#include <time.h>
#include <mint/basepage.h>
#include <assert.h>
#include "lib.h"

int	errno;
int	__mint;		/* 0 for TOS, MiNT version number in BCD format 
			   otherwise.  */
int	_pdomain;       /* Error code of Pdomain call */
char	_rootdir;	/* User's preferred root directory */

clock_t _starttime;	/* 200 HZ tick when we started the program.  */
clock_t _childtime;	/* Time consumed so far by our children.  */

/* Functions registered by user for calling at exit.  */
typedef void (*ExitFn) __PROTO ((void));
ExitFn *_at_exit;
int _num_at_exit;	/* Number of functions registered - 1.  */

/* Set to 1 if secure mode is advised.  */
int __libc_enable_secure = 1;

/* Set to 1 if we don't have to convert filenames to Redmond style.  */
int __libc_unix_names = 0;

int __has_no_ssystem;

#if defined(__TURBOC__) && !defined(__NO_FLOAT__)
void _fpuinit (void); /* in PCFLTLIB.LIB */

long _fpuvect[10];
long _pfumode;
long _fpuctrl;
#endif

BASEPAGE *_base;
char **environ;
long __libc_argc = 1;
char* __libc_argv[] = { "unknown application", NULL };

unsigned long _PgmSize;		/* total size of program area */

#ifdef __TURBOC__
char *_StkLim;	/* for Turbo / Pure C stack checking */
#endif

/* Default sizeof stdio buffers.  */
size_t __DEFAULT_BUFSIZ__ = 0;

/* are we an app? */
short _app = 1;

/* Are we on a split addr mem ST.  */
short _split_mem = 0;

char* program_invocation_name = "unknown application";
char* program_invocation_short_name = "unknown application";

int _exit_dummy_decl;


/* stdio things */

#define STDIN_MODE	{ 1, 0, 0, 1, 0, 0, 0 }
#define STDOUT_MODE	{ 0, 1, 0, 1, 1, 0, 1 }
#define STDERR_MODE	{ 1, 1, 0, 1, 0, 0, 0 }

#define STD_STREAM(NAME, FD, STREAM_MODE, CHAIN) \
	static FILE __##NAME = { \
		_IOMAGIC, \
		NULL, \
		NULL, \
		NULL, \
		NULL, \
		0, \
		(void *) ((long) FD), \
		STREAM_MODE, \
		{ NULL, NULL, NULL, NULL, NULL }, \
		{ NULL, NULL }, \
		(fpos_t) -1, \
		(fpos_t) -1, \
		CHAIN, \
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL }; \
	FILE* NAME = &__##NAME;


STD_STREAM(stdin, 0, STDIN_MODE, NULL);
STD_STREAM(stdout, 1, STDOUT_MODE, &__stdin);
STD_STREAM(stderr, 2, STDERR_MODE, &__stdout);


FILE* __stdio_head = &__stderr;

