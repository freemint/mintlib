/*  quickstat.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Modified by Frank Naumann <fnaumann@freemint.de>:
   - Use Fstat64.  */
   
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>	/* for FSTAT */
#include <errno.h>
#include <mintbind.h>
#include <alloca.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "lib.h"

extern int __mint;
extern char _rootdir;

extern ino_t __inode;

/* A quick stat version that gets everything but the timestamps.  This
   is often enough and saves a lot of performance.  
   
   For symbolic links the size may also be inaccurate.  */
   
int
__quickstat (_path, statbuf, lflag)
	const char *_path;
	struct stat *statbuf;
	int lflag;
{
	long	r;
	int	nval;
	char*	path = (char*) _path;
	char	tmpbuf[PATH_MAX];

	if (!_path) {
		__set_errno (EFAULT);
		return -1;
	}

	if (__libc_unix_names) 
		nval = 0;
	else {
	    	/*
	     	 * _unx2dos returns 1 for device names (like /dev/con)
	     	 */
	     	path = tmpbuf;
  	    	nval = _unx2dos(_path, path, PATH_MAX);
	}
	  
	/* First try Fstat.  Unfortunately we cannot cache reliably
	 * if Fstat is present or not.
	 * This is IMHO a weakness of the Fstat kernel API.  It returns
  	 * EINVAL if the call is performed on a filesystem that does not
  	 * know about Fstat.  Why doesn't the kernel simply wrap the 
  	 * call in order to drag the code overhead into the kernel?
  	 * The kernel is the only shared library we currently have ...
  	 */
	r = Fstat64 (lflag, path, statbuf);
	
	switch (r) {
		case -ENOSYS:
		case -EINVAL:
			break;
		default:
			if (r < 0) {
				__set_errno (-r);
				return -1;
			}
			return 0;
	}
		
	/* Next try Fxattr.  */
	{
	char	*ext, drv;
	_DTA	d;
	_DTA	*olddta;
	int	isdot = 0;
	struct xattr xattr;
	int	isdir = 0;
	
	r = Fxattr(lflag, path, &xattr);
	if (r != -ENOSYS) {
		if (r) {
			if ((r == -ENOTDIR) && _enoent (path)) {
				r = -ENOENT;
			}
			errno = (int) -r;
			return -1;
		} else {
			memset (statbuf, 0, sizeof *statbuf);
			statbuf->st_dev = (dev_t) xattr.st_dev;
			statbuf->st_ino = (ino_t) xattr.st_ino;
			statbuf->st_mode = (mode_t) xattr.st_mode;
			statbuf->st_nlink = (nlink_t) xattr.st_nlink;
			statbuf->st_uid = (uid_t) xattr.st_uid;
			statbuf->st_gid = (gid_t) xattr.st_gid;
			statbuf->st_rdev = (dev_t) xattr.st_rdev;
			statbuf->st_mtime = 0;
			statbuf->st_atime = 0;
			statbuf->st_ctime = 0;
			statbuf->st_size = (off_t) xattr.st_size;
			statbuf->st_blocks = 
				(off_t) (((off_t) xattr.st_blocks 
					 * (off_t) xattr.st_blksize) >> 9);
			statbuf->st_flags = 0;
			statbuf->st_blksize = xattr.st_blksize;
			
			return 0;
		}
	}

	memset (statbuf, 0, sizeof *statbuf);
	
	/* Otherwise, check to see if we have a name like CON: or AUX: */
	if (nval == 1) {
		statbuf->st_mode = S_IFCHR | 0600;
		statbuf->st_flags = 0;
		statbuf->st_ino = __inode++;
		statbuf->st_rdev = 0;
		statbuf->st_mtime = statbuf->st_ctime = statbuf->st_atime = 0;
		statbuf->st_dev = 0;
		statbuf->st_nlink = 1;
		statbuf->st_uid = geteuid();
		statbuf->st_gid = getegid();
		statbuf->st_size = statbuf->st_blocks = 0;
		statbuf->st_blksize = 1024;
		return 0;
	}

	/* A file name: check for root directory of a drive */
	if (path[0] == '\\' && path[1] == 0) {
		drv = Dgetdrv() + 'A';
		isdir = 1;
		goto rootdir;
	}

	if (((drv = path[0]) != 0) && path[1] == ':' &&
	     (path[2] == 0 || (path[2] == '\\' && path[3] == 0)) ) {
rootdir:
		isdir = 1;
		statbuf->st_mode = S_IFDIR | 0755;
		statbuf->st_flags = 0;
		statbuf->st_dev = isupper(drv) ? drv - 'A' : drv - 'a';
		statbuf->st_ino = 2;
		statbuf->st_mtime = statbuf->st_ctime = statbuf->st_atime = 0;
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

	/* Find the end of the string.  */
	for (ext = path; ext[0] && ext[1]; ext++) ;

	/* Add appropriate kludge if necessary. */
	if (*ext == '.' && (ext == path || ext[-1] == '\\' || ext[-1] == '.')) {
		isdot = 1;
		strcat (path, "\\*.*");
	} else if (*ext == '\\') {
		isdot = 1;
		strcat (path, "*.*");
	}
	olddta = Fgetdta();
	Fsetdta(&d);
	r = Fsfirst (path, 0xff);
	Fsetdta (olddta);
	if (r < 0) {
		if (isdot && r == -ENOENT) goto rootdir;
		__set_errno (-r);
		return -1;
	}	

	if (isdot && ((d.dta_name[0] != '.') || (d.dta_name[1]))) {
		goto rootdir;
	}

	if (((drv = *path) != 0) && path[1] == ':')
		statbuf->st_dev = _toupper (drv) - 'A';
	else
		statbuf->st_dev = Dgetdrv ();

	statbuf->st_ino = __inode++;
	statbuf->st_flags = 0;
	statbuf->st_mode = 0644 | (isdir ? S_IFDIR | 0111 : S_IFREG);

	if (statbuf->st_flags & FA_RDONLY)
		statbuf->st_mode &= ~0222;	/* no write permission */
	if (statbuf->st_flags & FA_HIDDEN)
		statbuf->st_mode &= ~0444;	/* no read permission */

	/* Check for a file with an executable extension */
	ext = strrchr(_path, '.');
	if (ext) {
		if (!strcmp (ext, ".app") || !strcmp (ext, ".gtp") ||
		    !strcmp (ext, ".ttp") || !strcmp (ext, ".prg") ||
		    !strcmp (ext, ".tos")) {
			statbuf->st_mode |= 0111;
		}
	}
	if ((statbuf->st_mode & S_IFMT) == S_IFREG) {
		statbuf->st_size = d.dta_size;
		/* In Unix, blocks are measured in 512 bytes */
		statbuf->st_blocks = (statbuf->st_size + 511) / 512;
		statbuf->st_nlink = 1; /* we dont have hard links */
	} else {
fill_dir:
		statbuf->st_size = 1024;
		statbuf->st_blocks = 2;
		statbuf->st_nlink = 2;	/* "foo" && "foo/.." */
	}

	statbuf->st_uid = geteuid();	/* the current user owns every file */
	statbuf->st_gid = getegid();
	statbuf->st_blksize = 1024;
	
	}
	
	return 0;
}
