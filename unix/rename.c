/* a public domain rename, by ERS */

#include <limits.h>
#include <errno.h>
#include <osbind.h>
#include <string.h>
#include <unistd.h>

#ifdef __TURBOC__
# include <sys\stat.h>
#else
# include <sys/stat.h>
#endif

#include <mintbind.h>
#include "lib.h"

int __rename(_oldname, _newname)
	const char *_oldname, *_newname;
{
	char oldnamebuf[PATH_MAX], newnamebuf[PATH_MAX];
	int rval, r;
	long xattr;
	struct xattr oldstat;
	struct xattr newstat;
	char* oldname = (char*) _oldname;
	char* newname = (char*) _newname;
	
	if (_oldname == NULL || _newname == NULL)
	  {
	    __set_errno (EFAULT);
	    return -1;
	  }
	if (!__libc_unix_names)
	  {
	    oldname = oldnamebuf;
	    newname = newnamebuf;
	    _unx2dos(_oldname, oldname, sizeof (oldnamebuf));
	    _unx2dos(_newname, newname, sizeof (newnamebuf));
	  }
	
	xattr = Fxattr (1, newname, &newstat);
	if (xattr == 0)
	  xattr = Fxattr (1, oldname, &oldstat);
	if (xattr == 0)
	  {
	    /* Find some errors.  FIXME:  That should be done conditionally
	       when the kernel can do that.  */
	    
	    /* First check: new is a directory and old isn't.  */
	    if (S_ISDIR ((mode_t) newstat.st_mode) 
	    	&& !S_ISDIR ((mode_t) oldstat.st_mode))
	      {
	        __set_errno (EISDIR);
	        return -1;
	      }
	    /* Check if newname is a non-empty directory?  What will currently
	       happen then?  This should result in ENOTEMPTY.  */

	    /* Check for same file.  */
	    if (newstat.st_dev == oldstat.st_dev &&
	        newstat.st_ino == oldstat.st_ino)
	      {
	        /* Same file.  */
	        __set_errno (EEXIST);
	        return -1;
	      }
	  }

	rval = Frename(0, oldname, newname);
	if (rval == 0)
	  return 0;
	if (rval != -EXDEV && rval != -ENOENT && rval != -ENOTDIR)
	  {
	    if (!strcmp(newname, oldname)) {
/* on inode-less filesystems do at least catch rename("foo", "foo"); */
		    __set_errno (EEXIST);
		    return -1;
	    }
	    if (!(r = Fdelete (newname)))
		    rval = Frename(0, oldname, newname);
/* kludge for kernel versions that suffer from `too much DOS' :)  i.e.
 * still look at the files write permission instead of the directories
 * even on real filesystems and when running in the MiNT domain:
 * if it says EACCES and the dest.dir exists try the old link/unlink way...
 */
	    if (rval == -EACCES && r != -ENOTDIR) {
		if (!(rval = Flink (oldname, newname))) {
		    if ((r = Fdelete (oldname)) && r != -ENOENT && r != -ENOTDIR) {
			    (void) Fdelete (newname);
		    } else {
			    rval = 0;	/* alright that did it! */
		    }
		} else if (rval == -ENOSYS) {
		    rval = -EACCES;	/* filesystem doesn't know link()... */
		}
	    }
	  }

	if (rval < 0) {
		if ((rval == -ENOTDIR) && (xattr != -ENOSYS) &&
		    (_enoent(Fxattr(1, oldname, &oldstat) ? oldname : newname)))
			rval = -ENOENT;
		__set_errno (-rval);
		rval = -1;
	}
	return rval;
}

weak_alias (__rename, rename)
