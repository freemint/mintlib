/* _buffindfile: given a base filename, a list of directories, and a list
   of possible extensions to the filename, attempts to find a file.
   Useful for doing, e.g. spawnvp. Note that the current directory
   is always searched first! If the filename already contains a
   path specification (or extension) then the given path list
   (or extension list) is ignored.
   Returns the name by which the file was found, or NULL.

   Written by Eric R. Smith and placed in the public domain.

   rehacked by Uwe Ohse, 28.4.93, to support reentrant spawn/popen.

   19.12.93, Andreas Schwab, clean up namespace:
   - findfile moved to separate file
   - buffindfile renamed to _buffindfile
*/

#include <compiler.h>
#include <support.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>

#include "lib.h"

/* characters used to separate components in a path list */
#define PATHSEP1        ':'
#define PATHSEP2        ','

/* characters used to separate directory names in a file */
#define DIRSEP1         '\\'    /* native OS directory separator */
#define DIRSEP2         '/'     /* for emulating another OS */

static const char *const nullext[] = { NULL };

static int EXISTS (const char *);

static int
EXISTS(const char *name)
{
	struct stat dummy;

	if (__quickstat (name, &dummy, 0) != 0)
		return 0;
	if ( (dummy.st_mode & S_IFMT) != S_IFREG )
		return 0;
	return 1;
}


char *
_buffindfile(const char *fname, const char *fpath, const char *const *fext,
	     char *try)
{
      char *s, *extplace, c;
      char const *const *nextext;
      const char *t;
      int  hasext = 0, haspath = 0;

	if (!fname || !*fname)
		return NULL;

      s = try; t = fname;

/* copy the file in, checking to see if a path and/or extension are already
   given */

      while ( (c = *t++) != 0 )
      {
              if (c == DIRSEP1 || c == DIRSEP2)
              {
                      haspath = 1;
                      hasext = 0;
              }
              else if (c == '.')
                      hasext = 1;
              *s++ = c;
      }
      extplace = s;
      *s = 0;

      if (haspath || !fpath)
              fpath = "";
      if (hasext || !fext)
              fext = nullext;

      for(;;) {               /* loop on path elements */
              nextext = fext;
		if (!hasext) {
			extplace[0] = 0;
			extplace[1] = 0;
		}

		if (EXISTS(try))
			return try;
		extplace[0] = '.';
              while(*nextext) {       /* loop on extensions */
                      (void)strcpy(&extplace[1], *nextext++);
                      if (EXISTS(try))
                              return try;
              }
              if (!*fpath) break;  /* no more places to look */

/* copy in next element of path list */
              s = try;
		/* an attempt to accomodate within reason TOS specs  -- mj */
		if (*(fpath + 1) == ':') {
			if ((*(fpath + 2) == DIRSEP1 ||
			     *(fpath + 2) == DIRSEP2)   &&
			    (*fpath != '.' && *fpath != ':')) {
				*s++ = *fpath++;
				*s++ = *fpath++;
				*s++ = *fpath++;
			}
		}
              while ((c = *fpath) != 0 && c != PATHSEP1 && c != PATHSEP2) {
                      *s++ = c;
                      fpath++;
              }
              if (c)
                      fpath++;
              
	      if ( s == try || (s[-1] != DIRSEP1 && s[-1] != DIRSEP2 ) )
              *s++ = DIRSEP1;
              t = fname;
              while ((*s++ = *t++) != 0)
                      ;
              extplace = --s ;        /* where the extension gets written */
      }
      return NULL;
}
