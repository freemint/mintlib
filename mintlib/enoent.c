#include <errno.h>
#include <string.h>

#ifdef __TURBOC__
# include <sys\stat.h>
#else
# include <sys/stat.h>
#endif

#include <mintbind.h>
#include "lib.h"

/*
Given a pathname for which some system call returned ENOTDIR, this function
decides if UNIX would have returned ENOENT instead.

FIXED: First check if the complete path itself is not a directory.  In
this case ENOTDIR is correct. --gfl
*/

int
_enoent(path)
  char *path;
{
  register char *s;
  struct xattr st;
  long oldmask, xattr;

  for (s = path; *s; s++)
    /* nop */;
  oldmask = Psigblock(~0L);

  for ( ; s != path; s--)
  {
    int saved = *s;
    
    if (*s == '\\' || *s == '/')
    {
      *s = '\0';
      xattr = Fxattr (0, path, &st);
      *s = saved;
      if (xattr == -ENOSYS 
          || (xattr == 0 && (((mode_t) st.st_mode & S_IFMT) != S_IFDIR))) {
  	    (void) Psigsetmask (oldmask);
  	    
  	    /* Either we don't have Fxattr or existing non-directory in
  	       PATH.  ENOTDIR is ok in either case.  */
  	    return 0;
      }
    }
  }
  (void) Psigsetmask(oldmask);
  return 1; /* should have been ENOENT */
}
