/*  exit.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>
#include <unistd.h>

/* Functions registered by user for calling at exit.  */
typedef void (*ExitFn) (void);
extern ExitFn *_at_exit;
extern int _num_at_exit;	/* Number of functions registered - 1.  */

#ifdef OLD_CLOSE
void
___fclose_all_files (void)
{
  register FILE *stream;
  
  stream = __stdio_head;
  while (stream)
  {  
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
#endif

__EXITING
__exit (int status)
{
  register int i;

  for(i = _num_at_exit - 1; i >= 0; --i)
    (*_at_exit[i]) ();

#ifdef OLD_CLOSE
  ___fclose_all_files ();
#else
  __fcloseall ();
#endif
  _exit (status);
}
weak_alias (__exit, exit)
