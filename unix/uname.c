/*  uname.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifdef __TURBOC__
# include <sys\utsname.h>
# include <sys\systeminfo.h>
#else
# include <sys/utsname.h>
# include <sys/systeminfo.h>
#endif

#include <errno.h>

int uname (info)
  struct utsname* info;
{
  if (info == (struct utsname*) 0) {
    __set_errno (EFAULT);
    return -1;
  }
  
  (void) sysinfo (SI_SYSNAME, info->sysname, sizeof (info->sysname));
  (void) sysinfo (SI_HOSTNAME, info->nodename, sizeof (info->nodename));
  (void) sysinfo (SI_RELEASE, info->release, sizeof (info->release));
  (void) sysinfo (SI_VERSION, info->version, sizeof (info->version));
  (void) sysinfo (SI_PLATFORM, info->machine, sizeof (info->machine));

#if 0
  (void) sysinfo (SI_ARCHITECTURE, info->architecture, 
      sizeof (info->architecture));
#endif

  return 0;
}
