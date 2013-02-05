/*  quickstat.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Modified by Frank Naumann <fnaumann@freemint.de>:
   - Use __sys_stat syscall wrapper  */
   
#include <alloca.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mint/mintbind.h>
#include "lib.h"


/* A quick stat version that gets everything but the timestamps.  This
   is often enough and saves a lot of performance.  
   
   For symbolic links the size may also be inaccurate.  */
   
int
__quickstat (const char *_path, struct stat *st, int lflag)
{
	char tmpbuf[PATH_MAX];
	char *path = (char *) _path;
	int nval;
	long r;

	if (!_path) {
		__set_errno (EFAULT);
		return -1;
	}

	if (*_path == '\0') {
		__set_errno (ENOENT);
		return -1;
	}

	if (__libc_unix_names) 
		nval = 0;
	else {
	    	/* _unx2dos returns 1 for device names (like /dev/con) */
	     	path = tmpbuf;
  	    	nval = _unx2dos(_path, path, sizeof (tmpbuf));
	}

	r = __sys_stat (path, st, lflag, 0);
	if (r != -ENOSYS) {
		if (r) {
			if ((r == -ENOTDIR) && _enoent (path)) {
				r = -ENOENT;
			}
			__set_errno (-r);
			return -1;
		}
		return 0;
	}

	{
	char	*ext, drv, *cwd, *prevdir = NULL;
	_DTA	d;
	_DTA	*olddta;
	int	isdot = 0;
	int	isdir = 0;
	
	__bzero (st, sizeof (*st));
	
	/* Otherwise, check to see if we have a name like CON: or AUX: */
	if (nval == 1) {
		st->st_mode = S_IFCHR | 0600;
		st->st_flags = 0;
		st->st_ino = __inode++;
		st->st_rdev = 0;
		st->st_mtime = st->st_ctime = st->st_atime = 0;
		st->st_dev = 0;
		st->st_nlink = 1;
		st->st_uid = geteuid();
		st->st_gid = getegid();
		st->st_size = st->st_blocks = 0;
		st->st_blksize = 1024;
		return 0;
	}

	/* A file name: check for root directory of a drive */
	if (path[0] == '\\' && path[1] == 0) {
		drv = Dgetdrv() + 'A';
		goto rootdir;
	}

	if (((drv = path[0]) != 0) && path[1] == ':' &&
	     (path[2] == 0 || (path[2] == '\\' && path[3] == 0)) ) {
rootdir:
		isdir = 1;
		st->st_mode = S_IFDIR | 0755;
		st->st_flags = 0;
		st->st_dev = isupper(drv) ? drv - 'A' : drv - 'a';
		st->st_ino = 2;
		st->st_mtime = st->st_ctime = st->st_atime = 0;
		goto fill_dir;
	}


	/* Forbid wildcards in path names */
	if (index(path, '*') || index (path, '?')) {
		__set_errno (ENOENT);
		return -1;
	}

	/* NOTE: Fsfirst(".",-1) or Fsfirst("..",-1) both fail under TOS,
	 * so we kludge around this by using the fact that Fsfirst(".\*.*"
	 * or "..\*.*" will return the correct file first (except, of course,
	 * in root directories :-( ).
	 * NOTE2: Some versions of TOS don't like Fsfirst("RCS\\", -1) either,
	 * so we do the same thing if the path ends in '\\'.
	 */
	
	/* Find the end of the string, and previous directory for kludging  */
	for (ext = path; ext[0] && ext[1]; ext++) {
		if (ext[1] && ext[1] != '.') {
			if (ext[0] == '\\') {
				prevdir = ext;
			}
		}
	};

	/* Add appropriate kludge if necessary. */

	/* Handle C:\XXXX\. */
	if (*ext == '.' && (ext == path || ext[-1] == '\\')) {
		isdot = 1;
		strcat (path, "\\*.*");
	}
	/* Now, Handle C:\XXXX\.. */
	else if (*ext == '.' && (ext == path || ext[-1] == '.')) {
		/*
		 * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		 * FIXME.
		 * Need to handle recursively, such as....
		 * C:\XXXX\YYYY\ZZZZ\..\..\..
		 *
		 * Also, need to handle non-rooted drives such as...
		 * ..\..\.., where the CWD needs to be retrieved.
		 * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		 */

		isdot = 1;
		if (prevdir) {
			/* 
			 * In the case of C:\XXXX\YYYY\.., we now have....
			 * C:\XXXX\*.*
			 */
			strcpy(prevdir, "\\*.*\0");
		} else {
			/*
			 * In the case of C:\.., we now have....
			 * C:\*.*
			 */
			strcpy(&ext[-2], "\\*.*\0");
		}
	} 
	/* Finally, Handle C:\XXXX\ */
	else if (*ext == '\\') {
		isdot = 1;
		strcat (path, "*.*");
	}
	olddta = Fgetdta();
	Fsetdta(&d);
	r = Fsfirst (path, 0xff);
	Fsetdta (olddta);
	if (r < 0) {
		/* 
		 * This is incorrect. When Fsfirst fails for things such as
		 * C:\\FOO\\ and appends *.*, to become C:\\FOO\\*.*, and
		 * we get ENOENT, why did we say it was a directory and return
		 * success ???
		 *
		 * Commenting out. See bug....
		 * http://sparemint.atariforge.net/bugtracker/view.php?id=191
		 *
		 * if (isdot && r == -ENOENT) goto rootdir;
		 */
		__set_errno (-r);
		return -1;
	}	

	if (isdot && ((d.dta_name[0] != '.') || (d.dta_name[1]))) {
		goto rootdir;
	}

	if (((drv = *path) != 0) && path[1] == ':')
		st->st_dev = _toupper (drv) - 'A';
	else
		st->st_dev = Dgetdrv ();

	st->st_ino = __inode++;
	st->st_flags = 0;
	st->st_mode = 0644 | (isdir ? S_IFDIR | 0111 : S_IFREG);

	if (st->st_flags & FA_RDONLY)
		st->st_mode &= ~0222;	/* no write permission */
	if (st->st_flags & FA_HIDDEN)
		st->st_mode &= ~0444;	/* no read permission */

	/* Check for a file with an executable extension */
	ext = strrchr(_path, '.');
	if (ext) {
		if (!strcmp (ext, ".app") || !strcmp (ext, ".gtp") ||
		    !strcmp (ext, ".ttp") || !strcmp (ext, ".prg") ||
		    !strcmp (ext, ".tos")) {
			st->st_mode |= 0111;
		}
	}
	if ((st->st_mode & S_IFMT) == S_IFREG) {
		st->st_size = d.dta_size;
		/* In Unix, blocks are measured in 512 bytes */
		st->st_blocks = (st->st_size + 511) / 512;
		st->st_nlink = 1; /* we dont have hard links */
	} else {
fill_dir:
		st->st_size = 1024;
		st->st_blocks = 2;
		st->st_nlink = 2;	/* "foo" && "foo/.." */
	}

	st->st_uid = geteuid();	/* the current user owns every file */
	st->st_gid = getegid();
	st->st_blksize = 1024;
	
	}
	
	return 0;
}
