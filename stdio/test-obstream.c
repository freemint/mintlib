/* Copyright (C) 2009 Free Software Foundation, Inc.
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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define obstack_chunk_alloc malloc
#define obstack_chunk_free  free

static void
check_obstack_printf_int(void)
{
  const char *fmt, *want;
  struct obstack ob;
  int got_len, want_len, ob_len;
  char *got;

  obstack_init (&ob);

  fmt = "%d";
  want = "567";
  want_len = strlen (want);
  got_len = obstack_printf (&ob, fmt, 567);
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);

  if (got_len != want_len
      || ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_obstack_printf_int: obstack_printf wrong\n");
      printf ("  fmt      |%s|\n", fmt);
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", got_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  got_len  %d\n", got_len);
      printf ("  ob_len   %d\n", ob_len);
      exit (1);
    }

  obstack_free (&ob, NULL);
}

static void
check_obstack_printf_typical(void)
{
  const char *fmt, *want;
  struct obstack ob;
  int got_len, want_len;
  char *got;

  obstack_init (&ob);

  fmt = "Found %d occurences.";
  want = "Found 23 occurences.";
  want_len = strlen (want);
  obstack_printf (&ob, fmt, 23);
  obstack_1grow(&ob, '\0');
  got = (char*)obstack_finish (&ob);
  got_len = strlen(got);

  if (got_len != want_len
      || strcmp(got, want) != 0)
    {
      printf ("check_obstack_printf_typical: obstack_printf wrong\n");
      printf ("  fmt      |%s|\n", fmt);
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", got_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  got_len  %d\n", got_len);
      exit (1);
    }

  obstack_free (&ob, NULL);
}

static void
check_obstack_printf_two_times(void)
{
  const char *fmt, *want;
  struct obstack ob;
  int got_len, want_len, ob_len;
  char *got;

  obstack_init (&ob);

  /* First write */
  fmt = "%d";
  want = "123";
  want_len = strlen (want);
  got_len = obstack_printf (&ob, fmt, 123);
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);

  if (got_len != want_len
      || ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_obstack_printf_two_times: first obstack_printf wrong\n");
      printf ("  fmt      |%s|\n", fmt);
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", got_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  got_len  %d\n", got_len);
      printf ("  ob_len   %d\n", ob_len);
      exit (1);
    }

  /* Second write */
  fmt = "%d";
  want = "1234567";
  want_len = strlen (want);
  got_len = obstack_printf (&ob, fmt, 4567);
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);

  if (got_len != 4
      || ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_obstack_printf_two_times: second obstack_printf wrong\n");
      printf ("  fmt      |%s|\n", fmt);
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", got_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  got_len  %d\n", got_len);
      printf ("  ob_len   %d\n", ob_len);
      exit (1);
    }

  obstack_free (&ob, NULL);
}

static void
check_obstack_vprintf(const char* want, const char* fmt, ...)
{
  va_list ap;
  struct obstack ob;
  int got_len, want_len, ob_len;
  char *got;

  obstack_init (&ob);

  va_start (ap, fmt);
  want_len = strlen (want);
  got_len = obstack_vprintf (&ob, fmt, ap);
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);

  if (got_len != want_len
      || ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_obstack_vprintf: obstack_printf wrong\n");
      printf ("  fmt      |%s|\n", fmt);
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", got_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  got_len  %d\n", got_len);
      printf ("  ob_len   %d\n", ob_len);
      exit (1);
    }

  obstack_free (&ob, NULL);
}

static void
check_open_obstack_stream(void)
{
  struct obstack ob;
  const char* fmt;
  int got_len, want_len, ob_len, got2_len, want2_len, err;
  const char *want, *got, *want2;
  FILE* f;

  obstack_init (&ob);

  f = open_obstack_stream(&ob);
  if (f == NULL)
    {
      printf("check_open_obstack_stream: open_obstack_stream returned NULL\n");
      exit (1);
    }

  /* Test fprintf */
  fmt = "one %d";
  want = "one 2";
  want_len = strlen (want);
  got_len = fprintf(f, fmt, 2);
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);
  if (got_len != want_len
      || ob_len < want_len /* Will be equal after flush.  */
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_open_obstack_stream: fprintf wrong\n");
      printf ("  fmt      |%s|\n", fmt);
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", got_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  got_len  %d\n", got_len);
      printf ("  ob_len   %d\n", ob_len);
      exit (1);
    }

  /* Test fwrite */
  want = "one 2 three\nfour";
  want_len = strlen (want);
  want2 = " three\nfour";
  want2_len = strlen (want2);
  got2_len = fwrite(want2, 1, want2_len, f);
  if (got2_len != want2_len)
    {
      printf("check_open_obstack_stream: fwrite failed.\n");
      exit (1);
    }

  /* Test fflush */
  err = fflush(f);
  if (err != 0)
    {
      printf("check_open_obstack_stream: fflush failed.\n");
      exit (1);
    }

  /* Check fwrite + fflush */
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);
  if (got2_len != want2_len
      || ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_open_obstack_stream: fwrite wrong\n");
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", ob_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  ob_len   %d\n", ob_len);
      printf ("  want2_len %d\n", want2_len);
      printf ("  got2_len  %d\n", got2_len);
      exit (1);
    }

  /* Test fseek SEEK_SET */
  err = fseek(f, 25, SEEK_SET);
  if (err != 0)
    {
      printf("check_open_obstack_stream: fseek SEEK_SET failed.\n");
      exit (1);
    }

  want = "one 2 three\nfour\0\0\0\0\0\0\0\0\0";
  want_len = 25;
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);
  if (ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_open_obstack_stream: fseek SEEK_SET wrong\n");
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", ob_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  ob_len   %d\n", ob_len);
      exit (1);
    }

  /* Test fseek SEEK_CUR backwards.  */
  err = fseek(f, -11, SEEK_CUR);
  if (err != 0)
    {
      printf("check_open_obstack_stream: fseek SEEK_CUR failed.\n");
      exit (1);
    }

  /* Seeking backwards should not change the object contents.  */
  want = "one 2 three\nfour\0\0\0\0\0\0\0\0\0";
  want_len = 25;
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);
  if (ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_open_obstack_stream: fseek SEEK_CUR wrong\n");
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", ob_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  ob_len   %d\n", ob_len);
      exit (1);
    }

  /* Test fwrite2 */
  want = "one 2 three\nfoObar five six seven";
  want_len = strlen (want);
  want2 = "Obar five six seven";
  want2_len = strlen (want2);
  got2_len = fwrite(want2, 1, want2_len, f);
  if (got2_len != want2_len)
    {
      printf("check_open_obstack_stream: fwrite2 failed.\n");
      exit (1);
    }

  /* Test fclose */
  err = fclose(f);
  if (err != 0)
    {
      printf("check_open_obstack_stream: fclose failed.\n");
      exit (1);
    }

  /* Check fwrite + fclose */
  got = obstack_base (&ob);
  ob_len = obstack_object_size (&ob);
  if (got2_len != want2_len
      || ob_len != want_len
      || memcmp (got, want, want_len) != 0)
    {
      printf ("check_open_obstack_stream: fwrite2 wrong\n");
      printf ("  want     |%s|\n", want);
      printf ("  got      |%.*s|\n", ob_len, got);
      printf ("  want_len %d\n", want_len);
      printf ("  ob_len   %d\n", ob_len);
      printf ("  want2_len %d\n", want2_len);
      printf ("  got2_len  %d\n", got2_len);
      exit (1);
    }

  obstack_free (&ob, NULL);
}

int
main (int argc, char *argv[])
{
  check_obstack_printf_int();
  check_obstack_printf_typical();
  check_obstack_printf_two_times();
  check_obstack_vprintf("one and 2 then 3.4", "%s and %d then %.1f", "one", 2, 3.4);
  check_obstack_vprintf("one\ntwo\nthree", "one\n%s", "two\nthree");
  check_open_obstack_stream();

  return 0;
}
