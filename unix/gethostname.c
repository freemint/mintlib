/* gethostname -- for now, fake by looking in environment */
/* (written by Eric R. Smith, placed in the public domain) */

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Changed by Guido Flohr:  Include sys/param.h for maximum hostname
   length.  */
#include <sys/param.h>
#include <sys/types.h>
#include <mint/sysctl.h>

__typeof__(gethostname) __gethostname;

int
__gethostname (char *buf, size_t len)
{
	if (!buf) {
		__set_errno (EINVAL);
		return -1;
	}

	/* try first the new syscall */
	{
		int mib[2];
		size_t size;

		mib[0] = CTL_KERN;
		mib[1] = KERN_HOSTNAME;
		size = len;

		if (sysctl(mib, 2, buf, &size, NULL, 0) == 0) {
			if (strcmp (buf, "(none)"))
				return 0;
		}
	}

	/* fall back to the old method */	
	{
		char *foo = 0;
		char xbuf[MAXHOSTNAMELEN + 1];
		int fd, r;
		size_t real_length;

		/* try looking for the file /etc/hostname; if it's present,
		 * it contains the name, otherwise we try the environment
		 */
		fd = open("/etc/hostname", O_RDONLY);
		if (fd >= 0) {
			r = read(fd, xbuf, MAXHOSTNAMELEN);
			if (r > 0) {
				xbuf[r] = 0;
				foo = xbuf;
				while (*foo) {
					if (*foo == '\r' || *foo == '\n') {
						*foo = 0;
						break;
					}
					++foo;
				}
				foo = xbuf;
			}
			close(fd);
		}

		if (!foo)
			foo = getenv("HOSTNAME");

		/* Changed by Guido Flohr: Warn if buffer was too small.  */
		real_length = strlen (foo ? foo : "unknown");

#if __GNUC_PREREQ(8, 0)
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#endif

		strncpy(buf, foo ? foo : "unknown", len < MAXHOSTNAMELEN  ? 
			len : MAXHOSTNAMELEN);

		if (real_length > len) {
			__set_errno (ENAMETOOLONG);
			return -1;
		}

		return 0;
	}
}
weak_alias (__gethostname, gethostname)
