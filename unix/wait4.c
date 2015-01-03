/*  wait4.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <mint/mintbind.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>

#include "lib.h"

extern long __waitval, __waittime;

pid_t
__wait4 (pid_t pid, __WP stat_loc, int options, struct rusage *usage)
{
  static short have_Pwaitpid = 1;
  long retval = 0; /* make gcc happy */
  long lusage[8];  /* For current MiNT versions 2 longs should 
                    * be enough.  The MiNTLib has 8 longs.
                    * Don't know why but better leave it as
                    * it is.
                    */
  pid_t child_pid;
  
  if (have_Pwaitpid) {
    retval = Pwaitpid (pid, options, lusage);
    if (retval == -ENOSYS)
      have_Pwaitpid = 0;
  }
  
  if (!have_Pwaitpid) {
    retval = __waitval;
    __waitval = -ECHILD;
    lusage[0] = __waittime;
    lusage[1] = 0;
  }

  /* That's all we can get from the OS.  */
  if (retval < 0) {
    if (retval == -ENOENT || retval == -ECHILD)
      {
        if (options & WNOHANG)
          return 0;          /* Work-around for kernel bug.  */
        retval = -ECHILD;
      }
    
    if (retval == -ENOENT)
      retval = -ECHILD;

    __set_errno (-retval);
    return -1; 
  }

  child_pid = (pid_t) (retval >> 16);

  /* Mask out the child pid.  */
  retval &= 0xffff;

  if (stat_loc != NULL) {
    /* Previous kernel versions had been confused by programs that
       terminate with bogus exit codes (i. e. more than 8 bits). 
       We try our best to fix that here.  */
    if (__mint < 0x10f)
      {
        if ((retval & 0x7f) == 0x7f)
          {
            /* Check if we have a valid stop signal.  */
            if ((retval & 0xff00) != (SIGSTOP << 8) &&
                (retval & 0xff00) != (SIGTSTP << 8) &&
                (retval & 0xff00) != (SIGTTIN << 8) &&
                (retval & 0xff00) != (SIGTTOU << 8))
              {
                /* Somehing wrong here.  Strip down to 8 bits.  */
                retval &= 0xff;
                
                /* If the child had a non-zero exit status, make sure
                   this is preserved.  This behavior is non-standard but
                   it is also non-standard to terminate with an exit code
                   wider than 8 bits.  */
                if (!retval)
                  retval = 1;
              }
          }  
        else if ((retval & 0xff00) != 0)
          {
            /* Signaled and possibly core dumped.  Check if this can
               be true.  */
            int termsig = (retval & 0x7f00) >> 8;
            int coredumped = retval & 8000;
            int correct = 0;  /* Be pessimistic.  */
            
            if (coredumped)
              {
                if (termsig == SIGFPE || termsig == SIGILL || termsig == SIGSEGV
                    || termsig == SIGBUS || termsig == SIGABRT || termsig == SIGPRIV 
                    || termsig == SIGTRAP || termsig == SIGSYS)
                  correct = 1;
              }
            if (!correct && termsig)
              {
                /* Fatal signals are 1-15 (SIGHUP to SIGTERM), SIGXCPU, SIGXFSZ,
                   and SIGPWR.  */
                if (termsig <= SIGTERM || termsig == SIGXCPU || termsig == SIGXFSZ
                    || termsig == SIGPWR)
                  correct = 1;
              }
          
            if (!correct)
              {
                /* The program screwed up the exit code.  Fix it.  */
                retval &= 0xff;
                if (!retval)
                  retval = 1;
              }
          }
      }
      
    if (((char) (retval & 0xff)) == (char) -32 && Pdomain (0) != 1) {
      /* Special kludge in the MiNT kernel.  */
      *stat_loc = SIGINT;
    } else if (((retval & 0x7f) == 0x7f) && ((retval & 0xff00) != 0)) {
      *stat_loc = retval;
    } else {
      /* MiNT returns the lower 2 bytes swapped.  */
      *stat_loc = ((retval & 0xff00) >> 8) | ((retval & 0xff) << 8);
    }
  }
  
  if (usage) {
    memset (usage, 0, sizeof (struct rusage));
    usage->ru_utime.tv_sec = lusage[0] / 1000;
    usage->ru_utime.tv_usec = 1000 * (lusage[0] % 1000);
    usage->ru_stime.tv_sec = lusage[1] / 1000;
    usage->ru_stime.tv_usec = 1000 * (lusage[1] % 1000);
  }
  
  return child_pid;
}
weak_alias (__wait4, wait4)
