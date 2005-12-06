/*  gentemp.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* The routines in this file are used by the temporary files functions.  */

#include <stdio.h>
#include <unistd.h>
#include <mintbind.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#ifdef __TURBO_C__
# include <sys\stat.h>
# include <sys\types.h>
#else
# include <sys/stat.h>
# include <sys/types.h>
#endif

#include "lib.h"

const char __tmp_letters[] = 
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

int __diraccess (const char*);
const char* __get_tmpdir (const char*, int try_tmpdir);
int __exists (const char*);

/* Get the name to use for a temporary directory.  */
const char*
__get_tmpdir (const char* preferred, int try_tmpdir)
{
  	char* trydir = NULL;
  
  	/* If we have a preferred directory try this one.  */
  	if (preferred != NULL && strlen (preferred) < L_tmpnam  
  	    && __diraccess (preferred))
    		return (const char*) preferred;
    
  	/* Next try: $TMPDIR but only if try_tmpdir.  */
  	if (try_tmpdir) {
  		trydir =  __secure_getenv ("TMPDIR");
  		if (trydir != NULL && strlen (trydir) < L_tmpnam 
      		    && __diraccess (trydir))
    			return trydir;
  	}
  
  	/* Next try: P_tmpdir.  */
  	if (strcmp (trydir, P_tmpdir) && __diraccess (__ugly_tos_P_tmpdir))
    		return __mint ? P_tmpdir : __ugly_tos_P_tmpdir;
  
  	/* Try "/tmp" if it exists.  */
  	if (strcmp (P_tmpdir, "/tmp") && __diraccess ("/tmp"))
    		return __mint ? "/tmp" : "\\tmp";

#if 0  
  	/* Now we leave the POSIX paths.  These environment variables
  	   get evaluated for historical reasons.  */
  	if (try_tmpdir && getenv ("POSIXLY_CORRECT")) {  
  		trydir = __secure_getenv ("TEMPDIR");
  		if (trydir != NULL  && strlen (trydir) < L_tmpnam 
  		    && __diraccess (trydir))
    			return trydir;
  		trydir = __secure_getenv ("TMP");
  		if (trydir != NULL && strlen (trydir) < L_tmpnam  
  		    && __diraccess (trydir))
    			return trydir;
  		trydir = __secure_getenv ("TEMP");
  		if (trydir != NULL && strlen (trydir) < L_tmpnam  
  		    && __diraccess (trydir))
    			return trydir;
    	}
#endif

  	__set_errno (ENOENT);
  	return NULL;
}

/* Check if NAME is a writable directory.  Avoid calling access() because
   that would use the real user id and real group id of the calling 
   process.  Don't think that we could cache the values.  Permission
   bits may change, directories may be created/deleted ...  */
int __diraccess (const char* name)
{
  	struct stat statbuf;
  	int retval = -1;
  	int __saved_errno = errno;  
  
  	if (__quickstat (name, &statbuf, 0) != 0) {
      		uid_t euid = geteuid ();
      		gid_t egid = getegid ();
      
      		/* Don't use access here because that would use the real 
      		   user and real group id of the calling process.  */
      		if (!S_ISDIR (statbuf.st_mode))
        		retval = -1;
      		/* Emulate access() but with effective user id.  */
      		else if (euid == 0)
        		retval = 0;  /* Free parking for setuid root.  */
      		else if (__mint < 9 && euid == statbuf.st_uid) {
          		if (((statbuf.st_mode >> 6) & W_OK) == W_OK)
            			retval = 0;
          		else
            			retval = -1;
      		} else if (egid == statbuf.st_gid) {
          		if (((statbuf.st_mode >> 3) & W_OK) == W_OK)
            			retval = 0;
          		else
            			retval = -1;
        	} else if (__mint >= 0x10b) {
          		int i, n;
          		gid_t groups[NGROUPS_MAX];
          
          		n = getgroups (NGROUPS_MAX, groups);
          		for (i = 0; i < n; i++) {
              			if (groups[i] == statbuf.st_gid) {
                  			if (((statbuf.st_mode >> 3) & W_OK) 
                  			    == W_OK) {
                      				retval = 0;
                      				break;
                    			} else {
                      				retval = -1;
                      				break;
                    			}
                		}
            		}
		}
	}
    
  	__set_errno (__saved_errno);
  	return retval;
}

int __exists (const char* pathname)
{
  	/* We can stat the file even if we can't read its data.  */
  	struct stat statbuf;
  	int saved_errno = errno;
  	if (__quickstat (pathname, &statbuf, 0) == 0)
    		return 1;
  	else {
      		/* We report that the file exists if stat failed for a 
      		   reason other than nonexistence.  In this case, it may 
      		   or may not exist, and we don't know; but reporting that 
      		   it does exist will never cause any trouble, while reporting 
      		   that it doesn't exist when it does would violate the 
      		   interface of __stdio_gen_tempname.  */
      		int exists = errno != ENOENT;
		__set_errno (saved_errno);
      		return exists;
    	}  
}
