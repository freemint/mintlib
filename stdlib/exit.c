/*  exit.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>

/* Functions registered by user for calling at exit.  */
typedef void (*ExitFn) __PROTO ((void));
__EXTERN ExitFn *_at_exit;
extern int _num_at_exit;	/* Number of functions registered - 1.  */

#if __GNUC__ > 1
/* In libgcc.a.  */
__EXTERN void __do_global_dtors __PROTO ((void));
#endif

void
___fclose_all_files ()
{
  register FILE* stream = __stdio_head;
  
  stream = __stdio_head;
  while (stream) {
    
    if (__validfp (stream)
        && stream != stdin 
        && stream != stdout 
        && stream != stderr)
      fclose (stream);
    stream = stream->__next;
  }

  fflush (stdout);
  fflush (stderr);  
}
weak_alias (___fclose_all_files, _fclose_all_files)

__EXITING __exit (status)
  int status;
{
  register int i;
#if 0
  /* If you care about non freed memory you should also call __hdestroy.  */
  __EXTERN void __hdestroy __PROTO ((void));
#endif

  for(i = _num_at_exit - 1; i >= 0; --i)
    (*_at_exit[i]) ();

  /* Now registered via atexit() in __do_global_ctors in libgcc.a.  */
#if 0
# if __GNUC__ > 1
  __do_global_dtors ();
# endif
#endif

  ___fclose_all_files ();
#if 0
  __hdestroy ();
#endif
  _exit (status);
}
weak_alias (__exit, exit)
