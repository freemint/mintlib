/* Copyright (C) 1991, 1992, 1996, 1997 Free Software Foundation, Inc.
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
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

/* This file provides glue between Unix stdio and GNU stdio.
   It supports use of Unix stdio `getc' and `putc' (and, by extension,
   `getchar' and `putchar') macros on GNU stdio streams (they are slow, but
   they work).  It also supports all stdio operations (including Unix
   `getc' and `putc') on Unix's stdin, stdout, and stderr (the elements of
   `_iob').

   The reasoning behind this is to allow programs (and especially
   libraries) compiled with Unix header files to work with the GNU C
   library.  */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

typedef union
  {
    struct
      {
#ifndef __MSHORT__
	int magic;
#else
	long magic;
#endif
	FILE **streamp;		/* Overlaps GNU stdio `bufp' member.  */
	/* This overlaps the GNU stdio `get_limit' and `put_limit'
	   members.  They must be <= `streamp'/`bufp' for GNU getc and putc
	   to do the right thing.  */
	FILE **streamp2;
	unsigned int _unused_flag;
	int _file;
      } glue;
    struct _iobuf
      {
      	/* This used to be a little non-standard with the MiNTLib.  */
	long _cnt;
	unsigned char *_ptr;
	unsigned char *_base;
	unsigned int _flag;
	int _file;
	long _bufsiz;
	unsigned char _ch;
      } unix_iobuf;
    /* The original implementation in the GNU libc contained this member.
       This makes the union 80 bytes big and prevents the glue code
       from working.  Any explanation?  */
#if 0
    FILE gnu_stream;
#endif
  } unix_FILE;

/* These are the Unix stdio's stdin, stdout, and stderr.
   In Unix stdin is (&_iob[0]), stdout is (&_iob[1]), and stderr is
   (&_iob[2]).  The magic number marks these as glued streams.  The
   __validfp macro in stdio.h is used by every stdio function.  It checks
   for glued streams, and replaces them with the GNU stdio stream.  */
unix_FILE _iob[] =
  {
    { { _GLUEMAGIC, &stdin,  NULL, 0x4, STDIN_FILENO  } },
    { { _GLUEMAGIC, &stdout, NULL, 0x4, STDOUT_FILENO } },
    { { _GLUEMAGIC, &stderr, NULL, 0x4, STDERR_FILENO } },
  };

/* Called by the Unix stdio `getc' macro.
   The macro is assumed to look something like:
       (--file->_cnt < 0 ? _filbuf (file) ...)
   In a Unix stdio FILE `_cnt' is the first element.
   In a GNU stdio or glued FILE, the first element is the magic number.  */
int
_filbuf (unix_FILE *file)
{
  switch (++file->glue.magic)	/* Compensate for Unix getc's decrement.  */
    {
    case _GLUEMAGIC:
      /* This is a glued stream.  */
      /* For MiNT we also have to make sure that we put the stream into
         the correct binary mode.  This is ok to do now because we will
         be called before the binmode gets checked by the old macro.  */
      file->unix_iobuf._flag = ((FILE*) file)->__mode.__binary ? 
      				0x0004 : 0;
      return getc (*file->glue.streamp);

    case  _IOMAGIC:
      /* This is a normal GNU stdio stream.  */
      return getc ((FILE *) file);

    default:
      /* Bogus stream.  */
      __set_errno (EINVAL);
      return EOF;
    }
}

/* Called by the Unix stdio `putc' macro.  Much like getc, above.  */
int
_flsbuf (int c, unix_FILE *file)
{
  /* Compensate for putc's decrement.  */
  switch (++file->glue.magic)
    {
    case _GLUEMAGIC:
      return putc (c, *file->glue.streamp);

    case  _IOMAGIC:
      return putc (c, (FILE *) file);

    default:
      __set_errno (EINVAL);
      return EOF;
    }
}
