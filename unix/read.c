/*
 * _read: like read, but takes a long instead of an int. Written by
 * Eric R. Smith and placed in the public domain.
 */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <support.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <mint/mintbind.h>
#include "lib.h"

#define CTRL(x) (x & 0x1f)
#define UNDEF -1

struct tchars __tchars = {
	CTRL('C'),		/* interrupt */
	CTRL('\\'),		/* quit */
	CTRL('Q'),		/* start */
	CTRL('S'),		/* stop */
	CTRL('D'),		/* EOF */
	'\r'			/* alternate end of line */
};

struct ltchars __ltchars = {
	CTRL('Z'),		/* suspend */
	CTRL('Y'),		/* suspend after read */
	CTRL('R'),		/* reprint */
	UNDEF,			/* flush output */
	UNDEF,			/* erase word */
	UNDEF			/* quote next char */
};

/*
 * BUGS: in tos, turning ECHO off but leaving RAW and CBREAK alone doesn't
 * work properly
 */
static int scancode = -1;

#ifdef __MSHORT__
long
#else
int
#endif
__read (int fd, void *buf, size_t size)
{
	char *foo;
	long r;
	int indx;
	int flags;
#ifdef EIO
	long tty_pgrp;
	long omask;
	sighandler_t osigt;
#endif
#ifdef EAGAIN
	long waiting_bytes = 1;
#endif

	if (isatty(fd)) {
/* work around a bug in TOS; 4096 bytes should be plenty for terminal reads */
		if (size > 4096) size = 4096;
		indx = __OPEN_INDEX(fd);
		if (indx < 0 || indx >= __NHANDLES)
			indx = __NHANDLES - 1;
		flags = __open_stat[indx].flags;
	}
	else
		flags = -1;

	if ( (__mint > 0) || (flags  == -1) ||
	     ( ((flags & (RAW|CBREAK|ECHO)) == ECHO) ) ) {
#ifdef EIO
                if (__mint && _isctty(fd)) {
		  (void) Fcntl(fd, (long) &tty_pgrp, TIOCGPGRP);
		  if (tty_pgrp != Pgetpgrp()) {
#if 0
		    /* This isn't really what we mean here...we really want to
		       know if our process group has no controlling terminal.
		    */
		    if (fd == -1 && __open_stat[indx] == FH_ISAFILE) {
		      __set_errno (EIO);
		      return -1;
		    }
#endif
		    omask = Psigblock(~0L);
		    osigt = (sighandler_t) Psignal(SIGTTIN, (long) SIG_IGN);
		    (void) Psignal(SIGTTIN, (long) osigt);
		    (void) Psigsetmask(omask);
		    if ((omask & sigmask(SIGTTIN)) || (osigt == SIG_IGN)) {
		      __set_errno (EIO);
		      return -1;
		    }
		  }
		}
#endif /* EIO */

		/* Workaround a bug in MiNT.  If the file descriptor has
		   the O_NONBLOCK flag set and there is no input immediately
		   available, the kernel returns 0.  We do a pre-check
		   if any data is waiting.  If there is nothing to read
		   and the kernel later returns 0 nevertheless that means
		   we have hit the bug.  We then return -1 and set errno
		   to EAGAIN.
		   Note: A return value of 0, no matter if blocking or
		   non-blocking read always signifies end of file.  */
#ifdef EAGAIN
		if (__mint) {
			register int handle = __OPEN_INDEX(fd);
			register int checkit = 1;
			
			if (handle < __NHANDLES) {
				if (__open_stat[handle].check_eagain == 0) {
					struct stat s;
					int saved_errno = errno;
					if (__do_fstat (fd, &s, 0) == 0) {
						if (S_ISREG (s.st_mode)
						    || S_ISDIR (s.st_mode)
						    || S_ISLNK (s.st_mode))
							__open_stat[handle].check_eagain = checkit = 1;
						else
							__open_stat[handle].check_eagain = 2;
					}
					__set_errno (saved_errno);
				}
				else
					checkit = __open_stat[handle].check_eagain - 1;
			}
			
			if (checkit)
				if ((Fcntl (fd, 0, F_GETFL)) & O_NONBLOCK)
					if (Fcntl(fd, &waiting_bytes, FIONREAD) != 0)
							waiting_bytes = 1;
		}
#endif
		
		r = Fread(fd, size, buf);
		
#ifdef EAGAIN
		if (__mint && r == 0 && waiting_bytes == 0) {
			r = -EAGAIN;
		}
#endif
		
		if (r < 0) {
			__set_errno (-r);
			return -1;
		}

	/* watch out for TTYs */
		if (__mint == 0 && isatty(fd)) {
			foo = (char *)buf;
			if (*foo == __tchars.t_eofc) /* EOF character? */
				return 0;
			/* for multibyte reads terminated by a CR, we add
			   the CR since TOS doesn't put it in for us
                        */
			if ((r < (long)size)  && (foo[r - 1] != '\r'))
			{
				foo[r] = '\r';
				r++;
			}
			/* If the last char is a CR (either added above
			   or read from a single-byte Fread()) we translate
			   it according to the CRMOD setting
			*/
 			if ((flags & CRMOD) && r && (foo[r - 1] == '\r')) {
 				foo[r - 1] = '\n';
				Cconout('\n'); /* not quite right if fd != 0 */
			}
		}
	}
	else {
		long key;
		
again:
		r = _console_read_byte(fd) & 0x00ff;
		if (scancode > 0 && size == 1) {	/* valid scan-code? */
			*((char *)buf) = scancode;
			scancode = -1;				/* invalidate scan-code */
			return 1;
		}

		key = _console_read_byte(fd);
		r = key & 0x00ff;	/* r = ASCII code */
		key >>= 16;			/* key = scan-code */

		if (flags & ECHO) {
			_console_write_byte(fd, (int)r);
		}
		if (flags & CRMOD) {
			if (r == '\r') r = '\n';
		}
		if (!(flags & RAW)) {
			if (r == __tchars.t_intrc) {
				raise(SIGINT);
				goto again;
			}
			else if (r == __tchars.t_quitc) {
				raise(SIGQUIT);
				goto again;
			}
		}
		if (r != 0) {
			*((char *)buf) = r;
			r = 1;
		}
		else {
			*((char *)buf) = '\034';	/* indicates that a scan-code follows */
			if (size > 1) {
				*((char *)buf+1) = key;	/* put scan-code to buffer */
				r = 2;
			}
			else {
				scancode = key & 0x00ff;/* valid scan-code for next read() call */
				r = 1;
			}
		}
	}

	return r;
}
weak_alias (__read, read)
