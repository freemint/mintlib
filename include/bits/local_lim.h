/*  include/bits/local_lim.h -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* These are the MiNT specific limits.  */

#define NGROUPS_MAX 8		/* 8 supplementary groups.  */
#define ARG_MAX 32767
#define CHILD_MAX 999
#define OPEN_MAX 32
#define LINK_MAX 32767
#define MAX_CANON 256
#define PIPE_BUF 1024

/* For SVR3, this is 14.  For SVR4, it is 255, at least on ufs
   file systems, even though the System V limits.h incorrectly
   defines it as 14.  Giving it a value which is too large
   is harmless (it is a maximum).  */
#define NAME_MAX 255

#define PATH_MAX 1024

/* The gcc header depends on the macro __GNU_LIBRARY__ which is 
   not set for the MiNTLib.  */
#if defined (__USE_GNU)
/* Minimum and maximum values a `signed long long int' can hold.  */
#ifndef __LONG_LONG_MAX__
#define __LONG_LONG_MAX__ 9223372036854775807LL
#endif
#undef LONG_LONG_MIN
#define LONG_LONG_MIN (-LONG_LONG_MAX-1)
#undef LONG_LONG_MAX
#define LONG_LONG_MAX __LONG_LONG_MAX__

/* Maximum value an `unsigned long long int' can hold.  (Minimum is 0).  */
#undef ULONG_LONG_MAX
#define ULONG_LONG_MAX (LONG_LONG_MAX * 2ULL + 1)
#endif

/* Sigh, mshort stuff.  Maybe this could be removed if gcc installs
   separate header files for each multilib target.  */
#ifdef __MSHORT__
#define __INT_MAX__ 32767
#endif
