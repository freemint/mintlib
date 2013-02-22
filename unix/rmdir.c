/* rmdir -- remove a directory */
/* written by Eric R. Smith and placed in the public domain */

/* Modified by Guido: The return code from Ddelete is to unreliable.
   We therefore check ourselves for correct arguments.  */
   
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mint/mintbind.h>
#include "lib.h"

int
__rmdir(const char *_path)
{
	char pathbuf[PATH_MAX];
	int  r;
	char* path = (char*) _path;
	struct stat statbuf;
	
	if (_path == NULL)
	  {
	    __set_errno (EFAULT);
	    return -1;
	  }
	  
	if (!__libc_unix_names)
	  {
	    path = pathbuf;
	    _unx2dos(_path, path, sizeof (pathbuf));
	  }
	
	if (__quickstat (path, &statbuf, 1) != 0) 
	  {
	    /* Can't stat, can't remove.  */
	    __set_errno (ENOENT);
	    return -1;
	  }
	if (!S_ISDIR (statbuf.st_mode))
	  {
	    __set_errno (ENOTDIR);
	    return -1;
	  }
	  
	r = Ddelete(path);
	if (r < 0) {
		long d;
		if ((r == -EACCES) &&
		    (((d = Dopendir(path, 0)) & 0xff000000L) != 0xff000000L)) {
			char *name;
			int  rd;

			do
				rd = (int)Dreaddir((int)(PATH_MAX), d, path);
			while (rd >= 0 && *(name=path+sizeof(long)) == '.' &&
				(!*++name || (*name == '.' && !*++name)));
			if (rd != -ENMFILES)
				r = -ENOTEMPTY;
			(void)Dclosedir (d);
		}
		__set_errno (-r);
		r = -1;
	}
	return r;
}
weak_alias (__rmdir, rmdir)
