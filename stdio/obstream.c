/* Copyright (C) 1992, 1996, 1997, 2009 Free Software Foundation, Inc.
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

#include <stdio.h>
#include <obstack.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/* Output-room function for obstack streams.  */

static void
grow (FILE *stream, int c)
{
  struct obstack *obstack = (struct obstack *) stream->__cookie;
  int size_written = (int)(stream->__target + stream->__bufp - stream->__buffer);

  /* Check if the buffer has been flushed by fseek().  */
  if (stream->__target != -1 && stream->__target > 0)
    {
      /* Restore the stream pointers to match the object.  */
      stream->__buffer = obstack_base (obstack);
      stream->__bufsize = obstack_object_size (obstack);
      stream->__bufp = stream->__buffer + stream->__target;
      stream->__get_limit = stream->__bufp;
      stream->__put_limit = stream->__buffer + stream->__bufsize;
      stream->__target = 0;
    }

  /* The stream buffer always maps exactly to the object on the top
     of the obstack.  The start of the buffer is the start of the object.
     The put limit points just past the end of the object.  On fflush, the
     obstack is sync'd so the end of the object points just past the last
     character written to the stream.  */
  if (c == EOF)
    {
      /* This is fflush. The object must be shrinked to keep only the portion
         of the buffer which the user has already written into.  */
      obstack_blank_fast (obstack, -(obstack_object_size (obstack) - size_written));

      /* Adjust the stream pointers.  */
      stream->__bufsize = obstack_object_size (obstack);
      stream->__put_limit = stream->__buffer + stream->__bufsize;
    }
  else if (size_written == obstack_object_size (obstack))
    {
      /* The buffer is full. Appending a byte to the object
         may cause the allocation of a new chunk.  */
      obstack_1grow (obstack, (unsigned char) c);
      ++size_written;

      /* Increase the object size to the size of the new chunk.  */
      obstack_blank_fast (obstack, obstack_room (obstack));

      /* Relocate the stream pointers.  */
      stream->__buffer = obstack_base (obstack);
      stream->__bufsize = obstack_object_size (obstack);
      stream->__bufp = stream->__buffer + size_written;
      stream->__get_limit = stream->__bufp;
      stream->__put_limit = stream->__buffer + stream->__bufsize;
    }
  else
    {
      /* The user called fseek() backwards, so there is room in the buffer.  */
      *stream->__bufp++ = (unsigned char)c;
    }
}

/* Seek function for obstack streams.
   There is no external state to munge.  */

static int
seek (void *cookie, fpos_t *pos, int whence)
{
  struct obstack *obstack = (struct obstack *) cookie;
  fpos_t current_offset = obstack_object_size (obstack); /* Stream has just been flushed.  */
  fpos_t target_offset;
  ptrdiff_t delta;

  switch (whence)
    {
    case SEEK_SET:
      target_offset = *pos;
      break;

    case SEEK_CUR:
      target_offset = current_offset + *pos;
      break;

    case SEEK_END:
      target_offset = current_offset - *pos;
      break;

    default:
      __libc_fatal ("obstream::seek called with bogus WHENCE\n");
      return -1;
    }

  /* Resize the buffer.  */
  delta = target_offset - current_offset;
  if (delta > 0)
    {
      obstack_blank (obstack, delta);
      bzero (obstack_base (obstack) + current_offset, delta);
    }

  return 0;
}

/* Initialize STREAM to talk to OBSTACK.  */

static void
init_obstream (FILE *stream, struct obstack *obstack)
{
  int initial_object_size;

  stream->__cookie = obstack;
  stream->__magic = _IOMAGIC;
  stream->__mode.__write = 1;

  /* When the buffer is full, grow the obstack.  */
  stream->__room_funcs.__output = grow;

  /* Seek within the object, and extend it.  */
  stream->__io_funcs.__seek = seek;
  stream->__target = stream->__offset = 0;

  /* Increase the size of the current object to the size of the chunk.  */
  initial_object_size = obstack_object_size (obstack);
  obstack_blank_fast (obstack, obstack_room (obstack));

  /* The initial buffer is the current growing object.  */
  stream->__buffer = obstack_base (obstack);
  stream->__bufsize = obstack_object_size (obstack);
  stream->__bufp = stream->__buffer + initial_object_size;
  stream->__get_limit = stream->__bufp;
  stream->__put_limit = stream->__buffer + stream->__bufsize;
  stream->__seen = 1;

  /* Don't deallocate that buffer!  */
  stream->__userbuf = 1;
}

FILE *
open_obstack_stream (struct obstack *obstack)
{
  FILE *stream;

  stream = __newstream ();
  if (stream == NULL)
    return NULL;

  init_obstream (stream, obstack);
  return stream;
}

int
obstack_vprintf (struct obstack *obstack, const char *format, va_list args)
{
  int result;
  FILE f;
  bzero (&f, sizeof (f));
  init_obstream (&f, obstack);
  result = vfprintf (&f, format, args);

  if (result >= 0)
    fflush(&f);

  return result;
}

int
obstack_printf (struct obstack *obstack, const char *format, ...)
{
  int result;
  va_list ap;
  va_start (ap, format);
  result = obstack_vprintf (obstack, format, ap);
  va_end (ap);
  return result;
}
