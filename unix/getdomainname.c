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

#define MAXLEN 127

int
__getdomainname(buf, len)
    char *buf;
    size_t len;
{
    char *foo = 0;
    char xbuf[MAXLEN+1];
    int fd, r;
    size_t real_length;

    if (!buf) {
	__set_errno (EINVAL);
	return -1;
    }

    fd = open("/etc/domainname", O_RDONLY);
    if (fd >= 0) {
	r = read(fd, xbuf, MAXLEN);
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
    
    strncpy(buf, foo ? foo : "", len < MAXLEN  ? 
	    len : MAXLEN);
    
    if (real_length > len) {
	__set_errno (ENAMETOOLONG);
	return -1;
    }
    
    return 0;
}

/* Stubs function: setdomainname.  */
int
__setdomainname (name, length)
    const char* name;
    size_t length;
{
    __set_errno (ENOSYS);
    return -1;
}
weak_alias (__setdomainname, setdomainname)
