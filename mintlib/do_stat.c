/*
 * stat, fstat, lstat emulation for TOS
 * written by Eric R. Smith and placed in the public domain
 */

/* Modified by Guido Flohr: Don't convert pathnames for recent MiNT
   versions.  */
#include <limits.h>

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\stat.h>
# include <sys\ioctl.h>	/* for FSTAT */
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>	/* for FSTAT */
#endif

#include <ctype.h>
#include <errno.h>
#include <osbind.h>
#include <mintbind.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <support.h>
#include "lib.h"

extern int __mint;
extern char _rootdir;

extern ino_t __inode;

/* for backwards compatibilty: if nonzero, files are checked to see if
 * they have the TOS executable magic number in them
 */

int	_x_Bit_set_in_stat = 0;

/* date for files (like root directories) that don't have one */
#define OLDDATE __unixtime(0,0)

/*
 * common routine for stat() and lstat(); if "lflag" is 0, then symbolic
 * links are automatically followed (like stat), if 1 then they are not
 * (like lstat)
 */

__EXTERN int _do_stat __PROTO((const char *_path, struct stat *st, int lflag));

int
_do_stat(_path, statbuf, lflag)
	const char *_path;
	struct stat *statbuf;
	int lflag;
{
	char	pathbuf[PATH_MAX];
	char*	path = (char*) _path;
	int 	nval;
	long	r;

	if (!_path) {
		__set_errno (EFAULT);
		return -1;
	}

	if (__libc_unix_names) {
		nval = 0;
	} else {
	    	/*
	     	 * _unx2dos returns 1 for device names (like /dev/con)
	     	 */
	    	path = pathbuf;
  	    	nval = _unx2dos(_path, path, PATH_MAX);
	}
	  
	/* First try Fstat64.  Unfortunately we cannot cache reliably
	 * if Fstat is present or not.
	 * This is IMHO a weakness of the Fstat64 kernel API.  It returns
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
				if ((r == -ENOTDIR) && _enoent(path))
					r = -ENOENT;
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
	struct xattr xattr;
	int	isdir = 0;
	/* try to use the build in stat() call, but if the system does not
	 * have it, record that and never try again
	 */

	/* actually we can't do that, because Fxattr() works for MetaDOS devices
	 * but returns -ENOSYS for other GEMDOS devices. Really unhappy solution.
	 * Since I don't want to patch chdir() and other calls I simply have to
	 * test the presence of Fxattr() every time the stat() is called.
	 * PS 970606
	 */

	r = Fxattr(lflag, path, &xattr);
	if (r != -ENOSYS) {
		if (r) {
			if ((r == -ENOTDIR) && _enoent(path)) {
				r = -ENOENT;
			}
			__set_errno (-r);
			return -1;
		} else {
			unsigned short* ptr;
			
			memset (statbuf, 0, sizeof *statbuf);
			statbuf->st_dev = (dev_t) xattr.st_dev;
			statbuf->st_ino = (ino_t) xattr.st_ino;
			statbuf->st_mode = (mode_t) xattr.st_mode;
			statbuf->st_nlink = (nlink_t) xattr.st_nlink;
			statbuf->st_uid = (uid_t) xattr.st_uid;
			statbuf->st_gid = (gid_t) xattr.st_gid;
			statbuf->st_rdev = (dev_t) xattr.st_rdev;
			ptr = (unsigned short*) &xattr.st_mtime;
			statbuf->st_mtime = __unixtime (ptr[0], ptr[1]);
			ptr = (unsigned short*) &xattr.st_atime;
			statbuf->st_atime = __unixtime (ptr[0], ptr[1]);
			ptr = (unsigned short*) &xattr.st_ctime;
			statbuf->st_ctime = __unixtime (ptr[0], ptr[1]);
			statbuf->st_size = (off_t) xattr.st_size;
			statbuf->st_blocks = 
				(off_t) (((off_t) xattr.st_blocks 
					 * (off_t) xattr.st_blksize) >> 9);
			statbuf->st_blksize = xattr.st_blksize;
			statbuf->st_flags = 0;
			
		/* if we hit a symbolic link, try to get its size right */
			if (lflag && ((statbuf->st_mode & S_IFMT) == S_IFLNK)) {
				char buf[PATH_MAX + 1];
				char buf1[PATH_MAX + 1];
				r = Freadlink(PATH_MAX, buf, path);
				if (r < 0)
				  {
					__set_errno (-r);
					return -1;
				  }
				buf[PATH_MAX] = 0;
				_dos2unx (buf, buf1, sizeof (buf1));
				statbuf->st_size = strlen (buf1);
			}
			return 0;
		}
	}

	memset (statbuf, 0, sizeof *statbuf);
/* otherwise, check to see if we have a name like CON: or AUX: */
	if (nval == 1) {
		statbuf->st_mode = S_IFCHR | 0600;
		statbuf->st_flags = 0;
		statbuf->st_ino = __inode++;
		statbuf->st_rdev = 0;
		statbuf->st_mtime = statbuf->st_ctime = statbuf->st_atime = 
			time((time_t *)0) - 2;
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

	if ( ((drv = path[0]) != 0) && path[1] == ':' &&
	     (path[2] == 0 || (path[2] == '\\' && path[3] == 0)) ) {
rootdir:
		isdir = 1;
		statbuf->st_mode = S_IFDIR | 0755;
		statbuf->st_flags = 0;
		statbuf->st_dev = isupper(drv) ? drv - 'A' : drv - 'a';
		statbuf->st_ino = 2;
		statbuf->st_mtime = statbuf->st_ctime = statbuf->st_atime = OLDDATE;
		goto fill_dir;
	}

/* forbid wildcards in path names */
	if (index(path, '*') || index(path, '?')) {
		__set_errno (ENOENT);
		return -1;
	}

/* OK, here we're going to have to do an Fsfirst to get the date */
/* NOTE: Fsfirst(".",-1) or Fsfirst("..",-1) both fail under TOS,
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

	statbuf->st_mtime = statbuf->st_ctime = statbuf->st_atime =
		__unixtime(d.dta_time, d.dta_date);
	if (((drv = *path) != 0) && path[1] == ':')
		statbuf->st_dev = _toupper(drv) - 'A';
	else
		statbuf->st_dev = Dgetdrv();

	statbuf->st_ino = __inode++;
	statbuf->st_flags = 0;
/*
	if (__mint && statbuf->st_dev == ('Q' - 'A'))
			statbuf->st_mode = 0644 | S_IFIFO;
	else
*/
	{
		statbuf->st_mode = 0644 | (isdir ? S_IFDIR | 0111 : S_IFREG);
	}

	if (statbuf->st_flags & FA_RDONLY)
		statbuf->st_mode &= ~0222;	/* no write permission */
	if (statbuf->st_flags & FA_HIDDEN)
		statbuf->st_mode &= ~0444;	/* no read permission */

/* check for a file with an executable extension */
	ext = strrchr(_path, '.');
	if (ext) {
		if (!strcmp(ext, ".app") || !strcmp(ext, ".gtp") ||
		    !strcmp(ext, ".ttp") || !strcmp(ext, ".prg") ||
		    !strcmp(ext, ".tos")) {
			statbuf->st_mode |= 0111;
		}
	}
	if ( (statbuf->st_mode & S_IFMT) == S_IFREG) {
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
				statbuf->st_mode |= 0111;
		}
		statbuf->st_size = d.dta_size;
	/* in Unix, blocks are measured in 512 bytes */
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
