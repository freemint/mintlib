/*  globals.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

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
#include <assert.h>
#include "lib.h"

/* Default sizeof stdio buffers.  */
size_t __DEFAULT_BUFSIZ__ = 0;

/* stdio things */

#if 0
/* The mode of I/O, as given in the MODE argument to fopen, etc.  */
typedef struct
{
  unsigned int __read:1;	/* Open for reading.  */
  unsigned int __write:1;	/* Open for writing.  */
  unsigned int __append:1;	/* Open for appending.  */
  unsigned int __binary:1;	/* Opened binary.  */
  unsigned int __create:1;	/* Create the file.  */
  unsigned int __exclusive:1;	/* Error if it already exists.  */
  unsigned int __truncate:1;	/* Truncate the file on opening.  */
} __io_mode;
#endif

#if 1
#define STDIN_MODE	{ 1, 0, 0, 0, 0, 0, 0 }
#define STDOUT_MODE	{ 0, 1, 0, 0, 1, 0, 1 }
#define STDERR_MODE	{ 0, 1, 0, 0, 0, 0, 0 }
#else
#define STDIN_MODE	{ 1, 0, 0, 1, 0, 0, 0 }
#define STDOUT_MODE	{ 0, 1, 0, 1, 1, 0, 1 }
#define STDERR_MODE	{ 0, 1, 0, 1, 0, 0, 0 }
#endif

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

FILE *__stdio_head = &__stderr;
