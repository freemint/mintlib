/* utime -- set the file modification time of the given file
 * according to the time given; a time of 0 means the current
 * time.
 *
 * All times are in Unix format, i.e. seconds since to
 * midnight, January 1, 1970 GMT
 *
 * written by Eric R. Smith, and placed in the public domain.
 *
 */
 
#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mint/mintbind.h>

#include "lib.h"

int
__utime (const char *_filename, const struct utimbuf *_tset)
{
	char filenamebuf[PATH_MAX];
	char* filename = (char*) _filename;
	long retval;
	struct _mutimbuf settime;
	struct _mutimbuf* tset = NULL;
	int fh;
	
	if (!__libc_unix_names) {
		filename = filenamebuf;
	    	(void) _unx2dos(_filename, filename, sizeof filenamebuf);
	}
	
	retval = Dcntl (FUTIME_UTC, filename, (long) _tset);
	if (retval == 0)
	      	return 0;
	/* FIXME: How can we distinguish between a failure where FUTIME_UTC
	   is not recognized by kernel/filesystem and a real failure?  */
	
	/* The FUTIME_UTC failed.  We have to convert the timestamp
	   to GEMDOS format.  */   
	if (_tset) {
		*((unsigned long*) &(settime.modtime)) = 
			__dostime (_tset->modtime);
		*((unsigned long*) &(settime.actime)) = 
			__dostime (_tset->actime);
		
			tset = &settime;
	}

	/* Try again with FUTIME.  */
	retval = Dcntl (FUTIME, filename, (long) tset);
	if (retval != -ENOSYS) {
		if (retval < 0) {
			if ((retval == -ENOTDIR) && (_enoent(filename)))
				retval = -ENOENT;
				__set_errno (-retval);
				return -1;
		}
		return 0;
	}
	
	/* Try it the hard way.  Open the file and use the Fcntl.  */
	fh = (int) Fopen(filename, 2);
	if (fh < 0) {
		/* Kludge #1: Because of a kernel bug Dcntl on toplevel 
		   directories (such as `/tmp') will fail if this directory 
		   is really a symlink.  */
		if (fh == -ENOENT) {
			size_t len = strlen (filename) + 10;
			char* fn = alloca (len);
		    	struct stat sb;
		    
			_dos2unx (_filename, fn, len);
		    	if (fn[0] == '/' && strrchr (fn, '/') == fn
		        	&& __sys_stat (filename, &sb, 1, 0) == 0
				&& S_ISLNK (sb.st_mode)
				&& __sys_stat (filename, &sb, 0, 0) == 0) {
					/* What should we do now?  Fake success 
					   or change the stamp of the target 
					   of the link instead?  Faking success
					   looks cleaner.  */
			        		return 0;
			}
		}
		  
		/* Kludge #2:  on dos filesystems return success 
		   for dirs even though we failed */
		if ((fh == -ENOENT) 
		    && (((retval = Dpathconf (filename, 5)) == 2) 
		        || (retval == -ENOSYS)) 
		    && (Fattrib (filename, 0, 0) == FA_DIR))
			return 0;

		if ((fh == -ENOTDIR) && (_enoent(filename)))
			fh = -ENOENT;
		__set_errno (-fh);
		return -1;
	}

	/* Open succeded, try Fcntl now.  */
	retval = Fcntl (fh, tset, FUTIME);
	if (retval == -ENOSYS) {
		/* Even that failed, fall back into Fdatime.  */
		unsigned long modtime;
		unsigned long* dtime;
	        
	       	if (tset) {
	       		dtime = (unsigned long *) &tset->modtime;
	       	} else {
			modtime = ((long) Tgettime () << 16) 
	    			| (Tgetdate () & 0xFFFF);
		    		dtime = &modtime;
		}
		
		retval = Fdatime ((_DOSTIME *) dtime, fh, 1);
	}

	if ((fh = Fclose(fh)) != 0) {
		__set_errno (-fh);
		return -1;
	}
	
	if (retval != 0) {
		__set_errno (-fh);
		return -1;
	}
	
	return 0;
}
weak_alias (__utime, utime)
