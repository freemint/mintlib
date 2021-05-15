/* gethostname -- for now, fake by looking in environment */
/* (written by Eric R. Smith, placed in the public domain) */

/* Modified by Guido Flohr: If no domain name available
   return the empty string instead of "(none)".  */
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <support.h>

/* Changed by Guido Flohr:  Include sys/param.h for maximum hostname
   length.  */
#include <sys/param.h>
#include <sys/types.h>
#include <mint/sysctl.h>

__typeof__(getdomainname) __getdomainname;

int
__getdomainname(char *buf, size_t len)
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
		mib[1] = KERN_DOMAINNAME;
		size = len;

		if (sysctl(mib, 2, buf, &size, NULL, 0) == 0) {
			if (strcmp (buf, "(none)"))
				return 0;
		}
	}

	/* fall back to the old method */	
	{
		char *foo = NULL;
		char xbuf[MAXHOSTNAMELEN + 1];
		int fd, r;
		size_t real_length;

		fd = open("/etc/domainname", O_RDONLY);
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
			foo = getenv ("DOMAINNAME");

		/* Changed by Guido Flohr: Warn if buffer was too small.  */
		real_length = foo ? strlen (foo) : 1;

#if __GNUC_PREREQ(8, 0)
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#endif

		strncpy(buf, foo ? foo : "", len < MAXHOSTNAMELEN  ? 
			len : MAXHOSTNAMELEN);
		
		if (real_length > len) {
			__set_errno (ENAMETOOLONG);
			return -1;
		}

		return 0;
	}
}
weak_alias (__getdomainname, getdomainname)
