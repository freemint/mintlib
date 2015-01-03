/* based upon Dale Schumacher's dLibs library */
/* extensively modified by ers */

#include <mint/mintbind.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>
#include <device.h>

#include "lib.h"

#ifndef PIPE_RDEV
#define PIPE_RDEV 0x7e00
#endif

/*
 * the MiNT kernel uses 0x08 for O_APPEND. For
 * backwards compatibility with old .o files,
 * we leave the definition in fcntl.h the same,
 * but adjust the file masks here.
 */

int __current_umask = -1;

/* Try to open the file NAME with FLAGS.  If the OS returns EACCES check
   if we are the super-user and then try to temporarily change the 
   permissions on the file to emulate the standard behavior where 
   the super-user can access everything, regardless of the permissions.  */
static int
failsafe_Fopen (const char* name, int flags)
{
	struct stat statbuf;
	int fd = Fopen (name, flags);
	int saved_errno = errno;

#define __S_I_WALL (S_IWUSR | S_IWGRP | S_IWOTH)

	if (fd == -EACCES && (flags & O_ACCMODE) != O_RDONLY && !geteuid () 
	    && __quickstat (name, &statbuf, 0) == 0) {
	    	mode_t saved_mode = statbuf.st_mode;
		if (chmod (name, saved_mode | __S_I_WALL) == 0) {
			fd = Fopen (name, flags);
			(void) chmod (name, saved_mode);				
		}
	}
	
	__set_errno (saved_errno);
	return fd;
}

int
__open_v (const char *_filename, int iomode, va_list argp)
{
	int rv;
	int modemask;			/* which bits get passed to the OS? */
	char filenamebuf[PATH_MAX];
	long fcbuf;			/* a temporary buffer for Fcntl */
	struct stat sb;
	unsigned int pmode = 0;
	char *filename = (char *) _filename;

	if (!_filename) {
		__set_errno (EFAULT);
	    	return -1;
	}
	
	if (*_filename == '\0') {
		__set_errno (ENOENT);
		return -1;
	}
	
	if (!__libc_unix_names) {
	    	filename = filenamebuf;
	    	_unx2dos(_filename, filename, sizeof (filenamebuf));
	}

	if (iomode & O_CREAT)
	    	pmode = va_arg (argp, unsigned int);

	/* use the umask() setting to get the right permissions */
	if (__current_umask == -1) {
		__current_umask = Pumask (0);

		if (__current_umask < 0)
			 __current_umask = 0;

		/* put back the old umask */
		Pumask(__current_umask);
	}
	pmode &= ~__current_umask;

	/* set the file access modes correctly */
	iomode = iomode & ~O_SHMODE;

	if (__mint >= 9) {
		modemask = O_ACCMODE | O_SHMODE | O_SYNC | O_NDELAY 
                           | O_CREAT | O_TRUNC | O_EXCL;

		iomode |= O_DENYNONE;
#if 0
		if (__mint >= 96)
#endif
		{
			modemask |= _REALO_APPEND;
			if (iomode & O_APPEND)
				iomode |= _REALO_APPEND;
		}

		if (__mint >= 0x111) 
			modemask |= O_DIRECTORY | O_NOATIME;

	} else {
		modemask = O_ACCMODE;
	}
	
	if (iomode & O_NOFOLLOW)
		rv = __quickstat (filename, &sb, 1);
	else
		rv = __quickstat (filename, &sb, 0);

	/* The code used to call Fstat.  Emulate this here.  */
	if (rv != 0)
		rv = -errno;
	
	if (rv == 0)		/* file exists */
	{
		if (S_ISLNK (sb.st_mode) && (iomode & O_NOFOLLOW)) {
			__set_errno(ELOOP);
			return -1;
		}
		
		if (S_ISDIR (sb.st_mode)) {
			/* Mimick old behaviour on 1.16 or earlier.
			 * It's valid to open a directory read-only but
			 * MiNT 1.16 (and earlier) couldn't do it, and even
			 * then the filesystem code also needs updates.
			 */
			if (__mint < 0x111) {
				__set_errno(EISDIR);
				return -1;
			}
				
			if ((iomode & O_ACCMODE) != O_RDONLY) {
	    			__set_errno (EISDIR);
	    			return -1;
			}
		} else {
			if (iomode & O_DIRECTORY) {
				__set_errno(ENOTDIR);
				return -1;
			}
		}

		if ((iomode & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL)) {
			__set_errno (EEXIST);
			/* return __SMALLEST_VALID_HANDLE - 1; */
			return -1;
		}
		
		rv = (int)failsafe_Fopen(filename,iomode & modemask & ~O_CREAT);
		if (rv == -ENOENT)
		/* race: file can disappear between stat and open... */
			goto noent;
		if (rv >= 0 && __mint >= 9 && !(iomode & O_DENYNONE)
			&& (major((dev_t) sb.st_rdev) == major(PIPE_RDEV))
		    && ((iomode & O_WRONLY) ? Foutstat(rv) : Finstat(rv)) < 0) {
		/* /pipe/file still open but noone at other end */
			(void)Fclose(rv);
			__set_errno (ENXIO);
			/* return __SMALLEST_VALID_HANDLE - 1; */
			return -1;
		}
		if ((iomode & ~modemask & O_TRUNC) && (rv >= 0)) {
			/* Give up if the mode flags conflict */
			if ((iomode & O_ACCMODE) == O_RDONLY) {
				(void)Fclose(rv);
				__set_errno (EACCES);
				/* return __SMALLEST_VALID_HANDLE - 1; */
				return -1;
			}
			/* Try the FTRUNCATE first.  If it fails, have GEMDOS
			   truncate it, then reopen with the correct modes.
			*/
			fcbuf = 0L;
			if ((__mint <= 90)
			    || (Fcntl(rv, (long) &fcbuf, FTRUNCATE) < 0)) {
				(void)Fclose(rv);
				rv = (int)Fcreate(filename, 0x00);
				if (rv < 0) {
					__set_errno (-rv);
					/* return __SMALLEST_VALID_HANDLE - 1; */
					return -1;
				}
				(void)Fclose(rv);
				rv = (int)failsafe_Fopen(filename,iomode & modemask);
			}
		}
	}
	else					/* file doesn't exist */
	{
		char linkf[40];
		long l;

noent:
	/* difference between MiNT and unix:  unix can create named pipes
	   (fifos) and ptys anywhere in the filesystem with mknod/mkfifo
	   and open both ends with standard open(), without O_CREAT.
	   MiNT keeps all this in /pipe, creating and first open
	   have to be done thru Fcreate with mode flags encoded as dos
	   `attributes' and the kernel doesn't know ENXIO. also ptys
	   use the same filename for both sides and everything in /pipe
	   unlinks itself at the last close.

	   the idea is when open would return ENOENT or EACCES on
	   creating see if its a symlink to /pipe/[cn]$* and then try
	   the right Fcreate/chmod here...  so mknod/mkfifo can create
	   a symlink and pass the mknod info in the link:
		/pipe/c$ pmode Fcreate-mode [flag] id
		/pipe/n$ pmode [flag] long-id	(Fcreate-mode == pipe)

	   pmode is octal, Fcreate-mode is 2 nibbles + '@', flag is '-'
	   for pty server side (/dev/ptyp*) or '$' for pty client (ttyp*,
	   open server side Fcreates this).  the ids only have to be uniqe
	   and long-id not start with an octal digit...
	*/
		if (__mint >= 9 &&
		    (rv == -EACCES || rv == -ENOENT) &&
		    Freadlink (sizeof linkf - 1, linkf, filename) >= 0 &&
		    !strncmp(linkf, "u:\\pipe\\", 8) &&
		    linkf[9] == '$' && (linkf[8] == 'c' || linkf[8] == 'n') &&
		    linkf[10] >= '0' && linkf[10] <= '7') {
			char *p, *q;
			pmode = strtoul (linkf+10, &q, 8);
			p = q;

			if (linkf[8] == 'n')
				l = (FA_HIDDEN|0x80);
			else {
				l = (*p++ & 0xf) << 4;
				l |= *p++ & 0xf;
			}
			if (((l & 0x80) && ((iomode & (O_ACCMODE|O_NDELAY)) ==
					(O_WRONLY|O_NDELAY))) ||
			    ((l & FA_SYSTEM) && *p == '$')) {
				__set_errno (ENXIO);
				/* return __SMALLEST_VALID_HANDLE - 1; */
				return -1;
			}
			if ((iomode & O_ACCMODE) == O_WRONLY) {
				l |= FA_RDONLY;
			}
			if (*p == '-')
				*p = '$';
			if (!(l & ~0x80)) {
				rv = (int) failsafe_Fopen (filename, (iomode & modemask)|
					O_CREAT|O_EXCL);
			} else {
				rv = (int) Fcreate (linkf, l & ~0x80);
				if (rv >= 0 && (iomode & O_NDELAY))
					Fcntl (rv, iomode & modemask, F_SETFL);
			}
			if (rv >= 0) {
				if (!Fchmod (linkf, pmode) &&
				    !__quickstat (filename, &sb, 1))
					(void)Fchown (linkf, 
						      (uid_t) sb.st_uid, 
						      (gid_t) sb.st_gid);
			}
		} else if(iomode & O_CREAT) {
			/* posix requirement for trailing slash check */
			size_t len = strlen(filename);

			if (len > 0 && filename[len - 1] == '/') {
				__set_errno(EISDIR);
				return -1;
			}

			if (len > 1 && filename[len - 1] == '\\' &&
				       filename[len - 2] == '\\') {
				__set_errno(EISDIR);
				return -1;
			}

			if (__mint >= 9) {
			    rv = (int) failsafe_Fopen (filename, iomode & modemask);
			} else {
			    rv = (int)Fcreate(filename, 0x00);                             
			    if (rv >= 0) {
			        struct stat statbuf;
				sb.st_mode = 0;
				
				/*
				   Problem: Why is sb.st_mode set to 0 and
				   why do we check then for a fifo???  
				 */
				if (fstat(rv,&statbuf) != 0 
				    || !S_ISFIFO(sb.st_mode)) {
					(void)Fclose(rv);
					rv = (int)failsafe_Fopen(filename,iomode & modemask);
				}
			    }
			}
			if (rv >= 0 && __mint >= 9)
				(void)Fchmod(filename, pmode);
		}
	}

	if (rv < (__SMALLEST_VALID_HANDLE)) {
		if ((rv == -ENOTDIR) && (_enoent(filename)))
			rv = -ENOENT;
		__set_errno (-rv);
		/* return __SMALLEST_VALID_HANDLE - 1; */
		return -1;
	}
	if (__mint) {
	    /* Relocate the handle to the lowest positive numbered handle
	       available
	    */
	    fcbuf = Fcntl(rv, (long) 0, F_DUPFD);
	    if (fcbuf >= 0) {
	      if (fcbuf < rv) {
		(void) Fclose(rv);
	        rv = (int) fcbuf;
	      } else {
	        (void) Fclose((int) fcbuf);
	      }
	    }
            /* clear the close-on-exec flag */
	    fcbuf = (long)Fcntl(rv, (long)0, F_GETFD);
	    if (fcbuf & FD_CLOEXEC)
		(void)Fcntl(rv, fcbuf & ~FD_CLOEXEC, F_SETFD);
	}
	if ((iomode & O_APPEND) && !(modemask & _REALO_APPEND))
		(void)Fseek(0L, rv, SEEK_END);

	/* fix the case `isatty() called before and not closed thru close()' */
	if (__OPEN_INDEX(rv) < __NHANDLES) {
		__open_stat[__OPEN_INDEX(rv)].status = FH_UNKNOWN;
		__open_stat[__OPEN_INDEX(rv)].check_eagain = 0;
	}
 	/* Important side effect:  isatty(rv) sets up flags under TOS */
	if (isatty(rv) && (!(iomode & O_NOCTTY)) && (!(isatty(-1)))) {
          /* If the process is a session leader with no controlling tty,
             and the tty that was opened is not already the controlling
             tty of another process, the tty becomes the controlling tty
             of the process.  Note that MiNT has no concept of a session
             leader so we really only check that it is a process group
             leader.
          */
	  if ((!__mint) 
              || ((Pgetpgrp() == Pgetpid())
                  && (Fcntl(rv, &fcbuf, TIOCGPGRP) >= 0)
                  && (fcbuf == 0))) {
	    ioctl(rv, TIOCSCTTY, 0);	/* new controlling tty */
            __open_stat[__OPEN_INDEX(-1)] = __open_stat[__OPEN_INDEX(rv)];
	  }
	}
	
	return(rv);
}

int
__open (const char *_filename, int iomode, ...)
{
	va_list args;
	int retval;

	va_start (args, iomode);
	retval = __open_v (_filename, iomode, args);
	va_end (args);

	return retval;
}
weak_alias (__open, open)
