/*-
 * Copyright (c) 1983, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#include "lib.h"
#include <sys/param.h>
#include <sys/time.h>
#include <sys/gmon.h>
#include <sys/gmon_out.h>
#include <sys/uio.h>

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int __profile_frequency __P ((void));

struct __bb *__bb_head;	/*  Head of basic-block list or NULL. */

struct gmonparam _gmonparam = { GMON_PROF_OFF, 0, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 0 };

/*
 * See profil(2) where this is described:
 */
static long int	s_scale;
#define		SCALE_1_TO_1	0x10000L

#define ERR(s) write(2, s, sizeof(s) - 1)

void moncontrol __P ((int mode));
void __moncontrol __P ((int mode));
static void write_hist (int fd);
static void write_call_graph (int fd);
static void write_bb_counts (int fd);

/* FIXME !!! */

int __profil (u_short *, size_t, size_t, u_int);

static ssize_t __gmon_writev (int s, const struct iovec *iov, ssize_t niov)
{
	ssize_t ret = 0;
	int i;

	for (i = 0; i < niov; i++) {
		int r = write (s, iov[i].iov_base, iov[i].iov_len);
		if (r < 0) return r;
		ret += r;
	}
	return ret;	
}

/*
 * Control profiling
 *	profiling is what mcount checks to see if
 *	all the data structures are ready.
 */
void moncontrol (int mode)
{
  struct gmonparam *p = &_gmonparam;

  /* Don't change the state if we ran into an error.  */
  if (p->state == GMON_PROF_ERROR)
    return;

  if (mode)
    {
      /* start */
      __profil((void *) p->kcount, p->kcountsize, p->lowpc, s_scale);
      p->state = GMON_PROF_ON;
    }
  else
    {
      /* stop */
      __profil(NULL, 0, 0, 0);
      p->state = GMON_PROF_OFF;
    }
}


void
monstartup (u_long lowpc, u_long highpc)
{
  register int o;
  char *cp;
  struct gmonparam *p = &_gmonparam;

  /*
   * round lowpc and highpc to multiples of the density we're using
   * so the rest of the scaling (here and in gprof) stays in ints.
   */
  p->lowpc = ROUNDDOWN(lowpc, HISTFRACTION * sizeof(HISTCOUNTER));
  p->highpc = ROUNDUP(highpc, HISTFRACTION * sizeof(HISTCOUNTER));
  p->textsize = p->highpc - p->lowpc;
  p->kcountsize = p->textsize / HISTFRACTION;
  p->hashfraction = HASHFRACTION;
  p->log_hashfraction = -1;
  /* The following test must be kept in sync with the corresponding
     test in mcount.c.  */
  if ((HASHFRACTION & (HASHFRACTION - 1)) == 0) {
      /* if HASHFRACTION is a power of two, mcount can use shifting
	 instead of integer division.  Precompute shift amount. */
      p->log_hashfraction = ffs(p->hashfraction * sizeof(*p->froms)) - 1;
  }
  p->fromssize = p->textsize / HASHFRACTION;
  p->tolimit = p->textsize * ARCDENSITY / 100;
  if (p->tolimit < MINARCS)
    p->tolimit = MINARCS;
  else if (p->tolimit > MAXARCS)
    p->tolimit = MAXARCS;
  p->tossize = p->tolimit * sizeof(struct tostruct);

  cp = calloc (p->kcountsize + p->fromssize + p->tossize, 1);
  if (! cp)
    {
      ERR("monstartup: out of memory\n");
      p->tos = NULL;
      p->state = GMON_PROF_ERROR;
      return;
    }
  p->tos = (struct tostruct *)cp;
  cp += p->tossize;
  p->kcount = (u_short *)cp;
  cp += p->kcountsize;
  p->froms = (u_short *)cp;

  p->tos[0].link = 0;

  o = p->highpc - p->lowpc;
  if (p->kcountsize < (u_long) o)
    {
#ifndef hp300
      s_scale = ((float)p->kcountsize / o ) * SCALE_1_TO_1;
#else
      /* avoid floating point operations */
      int quot = o / p->kcountsize;

      if (quot >= 0x10000)
	s_scale = 1;
      else if (quot >= 0x100)
	s_scale = 0x10000 / quot;
      else if (o >= 0x800000)
	s_scale = 0x1000000 / (o / (p->kcountsize >> 8));
      else
	s_scale = 0x1000000 / ((o << 8) / p->kcountsize);
#endif
    } else
      s_scale = SCALE_1_TO_1;

  moncontrol(1);
}


static void
write_hist (int fd)
{
  u_char tag = GMON_TAG_TIME_HIST;
  struct gmon_hist_hdr thdr __attribute__ ((aligned (__alignof__ (char *))));
  char **p;
  int32_t *pi;

  if (_gmonparam.kcountsize > 0)
    {
      u_long offset = (u_long) _base->p_tbase;
      struct iovec iov[3] =
        {
	  { &tag, sizeof (tag) },
	  { &thdr, sizeof (struct gmon_hist_hdr) },
	  { _gmonparam.kcount, _gmonparam.kcountsize }
	};

      p = (char **) thdr.low_pc;
      *p = (char *) _gmonparam.lowpc - offset;
      p = (char **) thdr.high_pc;
      *p = (char *) _gmonparam.highpc - offset;
      pi = (int32_t *) thdr.hist_size;
      *pi = (_gmonparam.kcountsize / sizeof (HISTCOUNTER));
      pi = (int32_t *) thdr.prof_rate;
      *pi = __profile_frequency ();
      strncpy (thdr.dimen, "seconds", sizeof (thdr.dimen));
      thdr.dimen_abbrev = 's';

      __gmon_writev (fd, iov, 3);
    }
}


static void
internal_function
write_call_graph (int fd)
{
#define NARCS_PER_WRITEV	32
  u_char tag = GMON_TAG_CG_ARC;
  struct gmon_cg_arc_record raw_arc[NARCS_PER_WRITEV]
    __attribute__ ((aligned (__alignof__ (char*))));
  int from_index, to_index, from_len;
  u_long frompc;
  struct iovec iov[2 * NARCS_PER_WRITEV];
  int nfilled;
  u_long offset = (u_long) _base->p_tbase;
  char **p;
  int32_t *pi;

  for (nfilled = 0; nfilled < NARCS_PER_WRITEV; ++nfilled)
    {
      iov[2 * nfilled].iov_base = &tag;
      iov[2 * nfilled].iov_len = sizeof (tag);

      iov[2 * nfilled + 1].iov_base = &raw_arc[nfilled];
      iov[2 * nfilled + 1].iov_len = sizeof (struct gmon_cg_arc_record);
    }

  nfilled = 0;
  from_len = _gmonparam.fromssize / sizeof (*_gmonparam.froms);
  for (from_index = 0; from_index < from_len; ++from_index)
    {
      if (_gmonparam.froms[from_index] == 0)
	continue;

      frompc = _gmonparam.lowpc;
      frompc += (from_index * _gmonparam.hashfraction
		 * sizeof (*_gmonparam.froms));
      for (to_index = _gmonparam.froms[from_index];
	   to_index != 0;
	   to_index = _gmonparam.tos[to_index].link)
	{
	  p = (char **) raw_arc[nfilled].from_pc;
	  *p = (char *) frompc - offset;
	  p = (char **) raw_arc[nfilled].self_pc;
	  *p = (char *)_gmonparam.tos[to_index].selfpc - offset;
	  pi = (int32_t *)raw_arc[nfilled].count;
	  *pi = _gmonparam.tos[to_index].count;

	  if (++nfilled == NARCS_PER_WRITEV)
	    {
	      __gmon_writev (fd, iov, 2 * nfilled);
	      nfilled = 0;
	    }
	}
    }
  if (nfilled > 0)
    __gmon_writev (fd, iov, 2 * nfilled);
}


static void
internal_function
write_bb_counts (int fd)
{
  struct __bb *grp;
  u_char tag = GMON_TAG_BB_COUNT;
  size_t ncounts;
  size_t i;

  struct iovec bbhead[2] =
    {
      { &tag, sizeof (tag) },
      { &ncounts, sizeof (ncounts) }
    };
  struct iovec bbbody[8];
  size_t nfilled;

  for (i = 0; i < (sizeof (bbbody) / sizeof (bbbody[0])); i += 2)
    {
      bbbody[i].iov_len = sizeof (grp->addresses[0]);
      bbbody[i + 1].iov_len = sizeof (grp->counts[0]);
    }

  /* Write each group of basic-block info (all basic-blocks in a
     compilation unit form a single group). */

  for (grp = __bb_head; grp; grp = grp->next)
    {
      ncounts = grp->ncounts;
      __gmon_writev (fd, bbhead, 2);
      for (nfilled = i = 0; i < ncounts; ++i)
	{
	  if (nfilled > (sizeof (bbbody) / sizeof (bbbody[0])) - 2)
	    {
	      __gmon_writev (fd, bbbody, nfilled);
	      nfilled = 0;
	    }

	  bbbody[nfilled++].iov_base = (char *) NO_CONST(&grp->addresses[i]);
	  bbbody[nfilled++].iov_base = &grp->counts[i];
	}
      if (nfilled > 0)
	__gmon_writev (fd, bbbody, nfilled);
    }
}


static void
write_gmon (void)
{
    struct gmon_hdr ghdr __attribute__ ((aligned (__alignof__ (int))));
    int fd = -1;
    char *env;
    int32_t *pi;

    env = getenv ("GMON_OUT_PREFIX");
    if (env != NULL && !__libc_enable_secure)
      {
	size_t len = strlen (env);
	char buf[len + 20];
	sprintf (buf, "%s.%u", env, getpid ());
	fd = open (buf, O_CREAT|O_TRUNC|O_WRONLY, 0666);
      }

    if (fd == -1)
      {
	fd = open ("gmon.out", O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if (fd < 0)
	  {
	    char buf[300];
	    int errnum = errno;
	    fprintf (stderr, "_mcleanup: gmon.out: %s\n",
		     strerror_r (errnum, buf, sizeof buf));
	    return;
	  }
      }

    /* write gmon.out header: */
    memset (&ghdr, '\0', sizeof (struct gmon_hdr));
    memcpy (&ghdr.cookie[0], GMON_MAGIC, sizeof (ghdr.cookie));
    pi = (int32_t *) ghdr.version;
    *pi = GMON_VERSION;
    write (fd, &ghdr, sizeof (struct gmon_hdr));

    /* write PC histogram: */
    write_hist (fd);

    /* write call-graph: */
    write_call_graph (fd);

    /* write basic-block execution counts: */
    write_bb_counts (fd);

    close (fd);
}


void
__write_profiling (void)
{
  long save = _gmonparam.state;
  _gmonparam.state = GMON_PROF_OFF;
  if (save == GMON_PROF_ON)
    write_gmon ();
  _gmonparam.state = save;
}
weak_alias (__write_profiling, write_profiling)


void
_mcleanup (void)
{
  moncontrol (0);

  if (_gmonparam.state != GMON_PROF_ERROR)
    write_gmon ();

  /* free the memory. */
  if (_gmonparam.tos != NULL)
    free (_gmonparam.tos);
}
