/*  setgroups.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifdef __TURBOC__
#include <sys\types.h>
#else
#include <sys/types.h>
#endif
#include <grp.h>
#include <errno.h>
#include <mintbind.h>

int
__setgroups (count, groups)
     size_t count;
     gid_t* groups;
{
  int retval = Psetgroups (count, groups);
  if (retval < 0)
    {
      if (retval == -EACCES)
        retval = -EPERM;
      __set_errno (-retval);
      return -1;
    }
  return 0;
}

weak_alias (__setgroups, setgroups)
