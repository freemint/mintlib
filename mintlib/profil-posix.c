/* Low-level statistical profiling support function.  Mostly POSIX.1 version.
   Copyright (C) 1996, 1997, 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>


static u_short *samples;
static size_t nsamples;
static size_t pc_offset;
static u_int pc_scale;

static inline void
profil_count (void *pc)
{
  size_t i = (pc - pc_offset - (void *) 0) / 2;

#if 0
  if (sizeof (unsigned long long int) > sizeof (size_t))
    i = (unsigned long long int) i * pc_scale / 65536;
  else
#endif
    i = i / 65536 * pc_scale + i % 65536 * pc_scale / 65536;

  if (i < nsamples)
    ++samples[i];
}

/* Get the machine-dependent definition of `profil_counter', the signal
   handler for SIGPROF.  It calls `profil_count' (above) with the PC of the
   interrupted code.  */
#include "profil-counter.h"

/* Enable statistical profiling, writing samples of the PC into at most
   SIZE bytes of SAMPLE_BUFFER; every processor clock tick while profiling
   is enabled, the system examines the user PC and increments
   SAMPLE_BUFFER[((PC - OFFSET) / 2) * SCALE / 65536].  If SCALE is zero,
   disable profiling.  Returns zero on success, -1 on error.  */

__typeof__(sigaction) __sigaction;
__typeof__(setitimer) __setitimer;
__typeof__(profil) __profil;

int
__profil (u_short *sample_buffer, size_t size, size_t offset, u_int scale)
{
  static struct sigaction oact;
  static struct itimerval otimer;
  struct sigaction act;
  struct itimerval timer;

  if (sample_buffer == NULL)
    {
      /* Disable profiling.  */
      if (samples == NULL)
	/* Wasn't turned on.  */
	return 0;

      if (__setitimer (ITIMER_PROF, &otimer, NULL) < 0)
	return -1;
      samples = NULL;
      return __sigaction (SIGPROF, &oact, NULL);
    }

 if (samples)
    {
      /* Was already turned on.  Restore old timer and signal handler
	 first.  */
      if (__setitimer (ITIMER_PROF, &otimer, NULL) < 0
	  || __sigaction (SIGPROF, &oact, NULL) < 0)
	return -1;
    }

  samples = sample_buffer;
  nsamples = size / sizeof *samples;
  pc_offset = offset;
  pc_scale = scale;

  /* FIXME: should use SA_SIGINFO & sa_sigaction */
  act.sa_handler = (sighandler_t) &profil_counter;
  act.sa_flags = 0; //SA_RESTART;
  sigfillset (&act.sa_mask);
  if (__sigaction (SIGPROF, &act, &oact) < 0)
    return -1;

  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 10000;
  timer.it_interval = timer.it_value;
  return __setitimer (ITIMER_PROF, &timer, &otimer);
}
weak_alias (__profil, profil)
