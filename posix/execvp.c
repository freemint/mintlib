/*  src/execvp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/


#include <stdarg.h>
#include <process.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <support.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

static char const *const extensions[] =
{ 
  "",
  ".ttp", 
  ".prg", 
  ".tos", 
  ".app", 
  ".gtp", 
  NULL
};
static char const *const mint_ext[] = { "", NULL };

int
execvp (const char *file, char *const *argv)
{
  	char const* const* exts = __mint == 0 ? extensions : mint_ext;
  	char const* const* ext;
  	char* path;
  	char default_path[] = ":";
  	char* p;
  	char* name;
  	size_t len;
  	int got_eacces = 0;
  	
  	if (*file == '\0') {
  		__set_errno (ENOENT);
  		return -1;
  	}
  	
  	/* Don't search if filename already contains a directory.  */
  	if (strchr (file, '/') != NULL || strchr (file, '\\') != NULL)
  		return __execve (file, argv, (char **) NULL);
  	
	path = getenv ("PATH");
	if (path == NULL && __mint == 0)
		path = "";
		
	if (path == NULL) {
		/* There is no `PATH' in the environment.
		   The default search path is the current directy
		   (actually followed by _CS_PATH which we don't have).  */
		path = default_path;
	}

	len = strlen (file) + 1;
	
	/* Using alloca bears risks for very long $PATHs.  */
	name = malloc (strlen (path) + len + 4);  /* Give room for extenders.  */
	if (name == NULL)
		return -1;  /* errno already set by malloc.  */
	
	p = path;
	do {
		char* extpos;
		char* 
		path = p;
		p = strchr (path, ':');
		if (p == NULL)
			p = strchr (path, '\0');
		
		if (p == path) {
			/* Two adjacent colons, or a colon at the beginning
			   or the end of `PATH' means to search the current
			   directory.  */
			extpos = __mempcpy (name, file, len) - 1;
		} else {
			/* Construct the pathname to try.  */
			char* tmp = __mempcpy (name, path, p - path);
			*tmp++ = '/';
			extpos = __mempcpy (tmp, file, len) - 1;
		}
		
		ext = exts;
		while (*ext) {
			strcpy (extpos, *ext);
			
			/* Try to execute this name.  If it works, execve
			   will not return.  */
			__execve (name, argv, NULL);
			
			switch (errno) {
			case EACCES:
				/* Record that we got a `Permission denied'
				   error.  If we end up finding no executable
				   we can use, we want to diagnose that we
				   did find one but were denied access.  */
				got_eacces = 1;
			case ENOENT:
			case ESTALE:
			case ENOTDIR:
				/* These errors indicate the file is missing 
				   or not executable by us, in which case we
				   want to just try the next path directory.  */
				break;
			
			case ENOEXEC:
				/* Non-MiNT systems refuse to run execute
				   an image if it has not one of the above
				   mentioned extenders.  */
				if (__mint == 0 && **ext == '\0')
					break;
				/* Else fall thru'.  */
				  
			default:
				/* Some other error means we found an
				   executable but something went wrong
				   executing it; return the error to our
				   caller.  */
				free (name);
				return -1;
			}
			ext++;
		}
	} while (*p++ != '\0');
	/* We tried every element and none of them worked.  */
	
	if (got_eacces)
		__set_errno (EACCES);
	
	free (name);
	
	/* Return the error from the last attempt (probably ENOENT).  */
  	return -1;
}
