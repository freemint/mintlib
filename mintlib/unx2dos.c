#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <osbind.h>

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\param.h>
#else
# include <sys/types.h>
# include <sys/param.h>
#endif

#include <support.h>
#include <limits.h>
#include "lib.h"

extern int __mint;
extern char _rootdir;	/* in main.c: user's preferred root directory */

int _unixmode;		/* not used right now */

/*
 * returns 0 for ordinary files, 1 for special files (like /dev/tty)
 */

int
_unx2dos(unx, dos, len)
	const char *unx;
	char *dos;
	size_t len;
{
	const char *u;
	char *d, c;

	dos[0] = 0;
	len--;			/* for terminating NUL */
	u = unx; d = dos;
	if (!strncmp(u, "/dev/", 5)) {
		u += 5;
	/* make /dev/A/foo the same as A:/foo */

		if (*u && isalpha (*u)
		    && (u[1] == 0 || (u[1] == '/' || u[1] == '\\'))) {
			d[0] = *u++;
			d[1] = ':';
			d += 2;
			len -= 2;
		}
	/* check for a unix device name */
		else if (__mint) {
/*
			if (__mint >= 8) {
*/
				strcpy(d, "U:\\dev\\"); d += 7;
				len -= 7;
/*
			} else {
				strcpy(d, "V:\\");
				d += 3;
				len -= 3;
			}
*/
		}
		else {
			strncpy(d, u, len);
			len -= strlen (u);
			strncat(d, ":", len);
			if (!strcmp(d, "tty:"))
				strcpy(d, "con:");
			return 1;
		}
	} else if (__mint && !strncmp(u, "/pipe/", 6)) {
		u += 6;
/*
		if (__mint >= 9) {
*/
			strcpy(d, "U:\\pipe\\"); d += 8;
			len -= 8;
/*
		} else {
			strcpy(d, "Q:\\"); d += 3;
			len -= 3;
		}
*/
	} else if (*u == '/' && _rootdir) {
		*d++ = _rootdir;
		*d++ = ':';
		len -= 2;
	}

	while( (c = *u++) != 0 ) {
		if (c == '/')
			c = '\\';
#if 0
/* translate "c:/foo/d:/bar" into "d:\bar" */
		else if (c == ':') {
			if (   (d > &dos[1] && d[-2] == '\\')
			    || (d == &dos[1]) ) {
				*dos = d[-1];
				len += d - (dos + 1);
				d = dos+1;
			}
		}
#endif
		*d++ = c;
		len--;
		if (len == 0)
			break;
	}
	*d = 0;
	return 0;
}

int
_dos2unx(dos, unx, len)
	const char *dos;
	char *unx;
	size_t len;
{
	register char c;

	len--;			/* for terminating NUL */
	/* replace A:\x with /dev/a/x,
	 * replace A:\x with /x, if _rootdir is 'a',
	 * replace A:\x with /a/x, if _rootdir is 'u'.
	 * BUG/FEATURE: A:x is converted to A:\x, you lose the feature
	 *              of one current directory per device.
	 *              This is because we assume that /dev/a/x is always 
	 *              an absolute path.
	 */ 
	if (*dos && dos[1] == ':') {
		register char dev = tolower(*dos);
		dos += 2;
		if (dev != _rootdir) {
			if (_rootdir != 'u') {
				*unx++ = '/'; *unx++ = 'd'; 
				*unx++ = 'e'; *unx++ = 'v';
				len -= 4;
			}
			*unx++ = '/';
			*unx++ = dev;
			len -= 2;
		}
		if (*dos != '/' && *dos != '\\') {
				*unx++ = '/';
				len--;
		}
	}
	/* convert slashes
	 */
	while ( (c = *dos++) != 0) {
		if (c == '\\')
			c = '/';
		else if (__mint < 7)
			c = tolower(c);
		*unx++ = c;
		len--;
		if (len == 0)
			break;
	}
	*unx = 0;
	return 0;
}

int
unx2dos(unx, dos)
        const char *unx;
        char *dos;
{
	return _unx2dos(unx, dos, PATH_MAX);
}

int
dos2unx(dos, unx)
        const char *dos;
        char *unx;
{
	return _dos2unx(dos, unx, PATH_MAX);
}

int
_path_unx2dos(unx, dos, len)
	const char *unx;
	char *dos;
	size_t len;
{
	char buf[MAXPATHLEN], *s;
		
	while (*unx) {
		s = buf;
		while (*unx) {
			if (*unx == ':') {
				unx++;
				break;
			}
			if (s < buf + sizeof (buf) - 1)
				*s++ = *unx;
			unx++;
		}
		*s = 0;
		_unx2dos(buf, dos, len);
		while (*dos) {
			dos++;
			len--;
		}
		if (len <= 10)
			break;
		if (*unx) {
			*dos++ = ',';
			len--;
		}
	}		

	*dos = 0;
	return 0;
}		

int 
_path_dos2unx(dos, unx, len)
	const char *dos;
	char *unx;
	size_t len;
{
	char buf[MAXPATHLEN], *s;

	while (*dos) {
		s = buf;
		while (*dos) {
			if (*dos == ';' || *dos == ',') {
				dos++;
				break;
			}
			if (s < buf + sizeof (buf) - 1)
				*s++ = *dos;
			dos++;
		}
		*s = 0;
		_dos2unx(buf, unx, len);
		while (*unx) {
			unx++;
			len--;
		}
		if (len <= 10)
			break;
		if (*dos) {
			*unx++ = ':';
			len--;
		}
	}

	*unx = 0;
	return 0;
}
