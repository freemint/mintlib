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

int __mint;		/* 0 for TOS, MiNT version number in BCD format 
			   otherwise.  */
char _rootdir;		/* User's preferred root directory */

/* Set to 1 if secure mode is advised.  */
int __libc_enable_secure = 1;

/* Set to 1 if we don't have to convert filenames to Redmond style.  */
int __libc_unix_names = 0;

long __has_no_ssystem;

BASEPAGE *_base;
char **environ;

/* total size of program area */
unsigned long _PgmSize;

/* are we an app? */
short _app = 1;

/* Are we on a split addr mem ST.  */
short _split_mem = 0;
