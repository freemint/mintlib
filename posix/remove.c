/*  remove.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int
remove (filename)
     const char* filename;
{
        int saved_errno = errno;

        /* First try rmdir().  */
        if (__rmdir (filename) == 0) {
                return 0;
        }

	/* This can only work if rmdir always sets errno correctly.  */       
        if (errno == ENOTDIR) {
                __set_errno (saved_errno);
                return __unlink (filename);
        }
        
        __set_errno (ENOENT);
        return -1;
}
