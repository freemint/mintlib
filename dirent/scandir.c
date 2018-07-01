/* Copyright (C) 1992-1998, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef SCANDIR
#define SCANDIR scandir
#define READDIR __readdir
#define DIRENT_TYPE struct dirent
#endif

int SCANDIR(
	const char *dir,
	DIRENT_TYPE ***namelist,
	int (*select) (const DIRENT_TYPE *),
	int (*cmp) (const DIRENT_TYPE **, const DIRENT_TYPE **))
{
  DIR *dp = __opendir (dir);
  DIRENT_TYPE **v = NULL;
  size_t vsize = 0, i;
  DIRENT_TYPE *d;
  int save;

  if (dp == NULL)
    return -1;

  save = errno;
  __set_errno (0);

  i = 0;
  while ((d = READDIR (dp)) != NULL)
    if (select == NULL || (*select) (d))
      {
	DIRENT_TYPE *vnew;
	size_t dsize;

	/* Ignore errors from select or readdir */
	__set_errno (0);

	if (__builtin_expect (i == vsize, 0))
	  {
	    DIRENT_TYPE **new;
	    if (vsize == 0)
	      vsize = 10;
	    else
	      vsize *= 2;
	    new = realloc (v, vsize * sizeof (*v));
	    if (new == NULL)
	      break;
	    v = new;
	  }

	dsize = &d->d_name[_D_ALLOC_NAMLEN (d)] - (char *) d;
	vnew = malloc (dsize);
	if (vnew == NULL)
	  break;

	v[i++] = (DIRENT_TYPE *) memcpy (vnew, d, dsize);
      }

  if (__builtin_expect (errno, 0) != 0)
    {
      save = errno;
      (void) __closedir (dp);
      while (i > 0)
	free (v[--i]);
      free (v);
      __set_errno (save);
      return -1;
    }

  (void) __closedir (dp);
  __set_errno (save);

  /* Sort the list if we have a comparison function to sort with.  */
  if (cmp != NULL)
    qsort (v, i, sizeof (*v), (int (*)(const void *, const void *))cmp);
  *namelist = v;
  return i;
}
