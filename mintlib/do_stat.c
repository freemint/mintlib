/*
 * $Id$
 * 
 * stat, fstat, lstat emulation for TOS
 * written by Eric R. Smith and placed in the public domain
 */

/* Modified by Guido Flohr: Don't convert pathnames for recent MiNT
   versions.  */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <support.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <mint/mintbind.h>

#include "lib.h"

/* 
 * stat system call wrapper
 * 
 * first try Fstat64, then fallback to Fxattr and convert
 * to struct stat
 */
long
Fstat (const char *path, struct stat *st, int lflag, int exact)
{
	long r;

	/* first try the native syscall */
	r = Fstat64 (lflag, path, st);
	if (r == -ENOSYS || r == -EINVAL) {

		/* fall back to Fxattr */
		struct xattr xattr;

		r = Fxattr (lflag, path, &xattr);
		if (r == 0) {
			unsigned short *ptr;

			__bzero (st, sizeof (*st));

			st->st_dev = (dev_t) xattr.st_dev;
			st->st_ino = (ino_t) xattr.st_ino;
			st->st_mode = (mode_t) xattr.st_mode;
			st->st_nlink = (nlink_t) xattr.st_nlink;
			st->st_uid = (uid_t) xattr.st_uid;
			st->st_gid = (gid_t) xattr.st_gid;
			st->st_rdev = (dev_t) xattr.st_rdev;

			if (exact) {
				ptr = (unsigned short *) &xattr.st_mtime;
				st->st_mtime = __unixtime (ptr[0], ptr[1]);
				ptr = (unsigned short *) &xattr.st_atime;
				st->st_atime = __unixtime (ptr[0], ptr[1]);
				ptr = (unsigned short *) &xattr.st_ctime;
				st->st_ctime = __unixtime (ptr[0], ptr[1]);
			}

			st->st_size = (off_t) xattr.st_size;
			st->st_blocks = 
				(off_t) (((off_t) xattr.st_blocks 
					 * (off_t) xattr.st_blksize) >> 9);
			st->st_blksize = xattr.st_blksize;
			// st->st_flags = 0;
			// st->st_gen = 0;

# if 0
			/* if we hit a symbolic link, try to get its size
			 * right
			 */
			if (lflag && ((st->st_mode & S_IFMT) == S_IFLNK)) {
				char buf[PATH_MAX + 1];
				char buf1[PATH_MAX + 1];
				r = Freadlink(PATH_MAX, buf, path);
				if (r < 0) {
					__set_errno (-r);
					return -1;
				}
				buf[PATH_MAX] = 0;
				_dos2unx (buf, buf1, sizeof (buf1));
				st->st_size = strlen (buf1);
			}
# endif
		}
	}

	return r;
}

extern char _rootdir;
extern ino_t __inode;

/* for backwards compatibilty: if nonzero, files are checked to see if
 * they have the TOS executable magic number in them
 */
int _x_Bit_set_in_stat = 0;

/* date for files (like root directories) that don't have one */
#define OLDDATE __unixtime(0,0)

/*
 * common routine for stat() and lstat(); if "lflag" is 0, then symbolic
 * links are automatically followed (like stat), if 1 then they are not
 * (like lstat)
 */
int
__do_stat (const char *_path, struct stat *st, int lflag)
{
	char pathbuf[PATH_MAX];
	char *path = (char*) _path;
	int nval;
	long r;

	if (!_path) {
		__set_errno (EFAULT);
		return -1;
	}

	if (__libc_unix_names) {
		nval = 0;
	} else {
		/* _unx2dos returns 1 for device names (like /dev/con) */
		path = pathbuf;
		nval = _unx2dos (_path, path, sizeof (pathbuf));
	}

	r = Fstat (path, st, lflag, 1);
	if (r != -ENOSYS) {
		if (r) {
			if ((r == -ENOTDIR) && _enoent(path)) {
				r = -ENOENT;
			}
			__set_errno (-r);
			return -1;
		}
		return 0;
	}

	{
	_DTA	*olddta;
	char	*ext, drv;
	int	fd;
	short	magic;
	_DTA	d;
	int	isdot = 0;
	int	isdir = 0;

	memset (st, 0, sizeof *st);

	/* otherwise, check to see if we have a name like CON: or AUX: */
	if (nval == 1) {
		st->st_mode = S_IFCHR | 0600;
		st->st_flags = 0;
		st->st_ino = __inode++;
		st->st_rdev = 0;
		st->st_mtime = st->st_ctime = st->st_atime = 
			time((time_t *)0) - 2;
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
		isdir = 1;
		goto rootdir;
	}

	if ( ((drv = path[0]) != 0) && path[1] == ':' &&
	     (path[2] == 0 || (path[2] == '\\' && path[3] == 0)) ) {
rootdir:
		isdir = 1;
		st->st_mode = S_IFDIR | 0755;
		st->st_flags = 0;
		st->st_dev = isupper(drv) ? drv - 'A' : drv - 'a';
		st->st_ino = 2;
		st->st_mtime = st->st_ctime = st->st_atime = OLDDATE;
		goto fill_dir;
	}

	/* forbid wildcards in path names */
	if (index(path, '*') || index(path, '?')) {
		__set_errno (ENOENT);
		return -1;
	}

	/*
	 * OK, here we're going to have to do an Fsfirst to get the date
	 * 
	 * NOTE: Fsfirst(".",-1) or Fsfirst("..",-1) both fail under TOS,
	 * so we kludge around this by using the fact that Fsfirst(".\*.*"
	 * or "..\*.*" will return the correct file first (except, of course,
	 * in root directories :-( ).
	 * NOTE2: Some versions of TOS don't like Fsfirst("RCS\\", -1) either,
	 * so we do the same thing if the path ends in '\\'.
	 */

	/* find the end of the string */
	for (ext = path; ext[0] && ext[1]; ext++) ;

	/* add appropriate kludge if necessary */
	if (*ext == '.' && (ext == path || ext[-1] == '\\' || ext[-1] == '.')) {
		isdot = 1;
		strcat(path, "\\*.*");
	} else if (*ext == '\\') {
		isdot = 1;
		strcat(path, "*.*");
	}
	olddta = Fgetdta();
	Fsetdta(&d);
	r = Fsfirst(path, 0xff);
	Fsetdta(olddta);
	if (r < 0) {
		if (isdot && r == -ENOENT) goto rootdir;
		__set_errno (-r);
		return -1;
	}	

	if (isdot && ((d.dta_name[0] != '.') || (d.dta_name[1]))) {
		goto rootdir;
	}

	st->st_mtime = st->st_ctime = st->st_atime =
		__unixtime(d.dta_time, d.dta_date);
	if (((drv = *path) != 0) && path[1] == ':')
		st->st_dev = _toupper(drv) - 'A';
	else
		st->st_dev = Dgetdrv();

	st->st_ino = __inode++;
	st->st_flags = 0;
	st->st_mode = 0644 | (isdir ? S_IFDIR | 0111 : S_IFREG);

	if (st->st_flags & FA_RDONLY)
		st->st_mode &= ~0222;	/* no write permission */
	if (st->st_flags & FA_HIDDEN)
		st->st_mode &= ~0444;	/* no read permission */

	/* check for a file with an executable extension */
	ext = strrchr(_path, '.');
	if (ext) {
		if (!strcmp(ext, ".app") || !strcmp(ext, ".gtp") ||
		    !strcmp(ext, ".ttp") || !strcmp(ext, ".prg") ||
		    !strcmp(ext, ".tos")) {
			st->st_mode |= 0111;
		}
	}
	if ( (st->st_mode & S_IFMT) == S_IFREG) {
		if (_x_Bit_set_in_stat) {
			if ((fd = (int) Fopen(path,0)) < 0) {
				__set_errno (-fd);
				return -1;
			}
			magic = 0;
			(void)Fread(fd,2,(char *)&magic);
			(void)Fclose(fd);
			if (magic == 0x601A	/* TOS executable */
			    || magic == 0x2321) /* "#!" shell file */
				st->st_mode |= 0111;
		}
		st->st_size = d.dta_size;
	/* in Unix, blocks are measured in 512 bytes */
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
