/* One way encryption based on MD5 sum.
   Copyright (C) 1996, 1997, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.

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

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#include "md5.h"
#include "ufc-crypt.h"
#include "crypt.h"
#include "crypt-private.h"


/* Define our magic string to mark salt for MD5 "encryption"
   replacement.  This is meant to be the same as for other MD5 based
   encryption implementations.  */
static const char md5_salt_prefix[] = "$1$";

/* Table with characters for base64 transformation.  */
static const char b64t[64] =
"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";



/* This entry point is equivalent to the `crypt' function in Unix
   libcs.  */
char *
__md5_crypt_r (const char *key, const char *salt, char *buffer, long int buflen)
{
  unsigned char alt_result[16];
  struct md5_ctx ctx;
  struct md5_ctx alt_ctx;
  size_t salt_len;
  size_t key_len;
  size_t cnt;
  char *cp;

  /* Find beginning of salt string.  The prefix should normally always
     be present.  Just in case it is not.  */
  if (strncmp (md5_salt_prefix, salt, sizeof (md5_salt_prefix) - 1) == 0)
    /* Skip salt prefix.  */
    salt += sizeof (md5_salt_prefix) - 1;

  salt_len = MIN (strcspn (salt, "$"), 8);
  key_len = strlen (key);

  /* Prepare for the real work.  */
  __md5_init_ctx (&ctx);

  /* Add the key string.  */
  __md5_process_bytes (key, key_len, &ctx);

  /* Because the SALT argument need not always have the salt prefix we
     add it separately.  */
  __md5_process_bytes (md5_salt_prefix, sizeof (md5_salt_prefix) - 1, &ctx);

  /* The last part is the salt string.  This must be at most 8
     characters and it ends at the first `$' character (for
     compatibility which existing solutions).  */
  __md5_process_bytes (salt, salt_len, &ctx);


  /* Compute alternate MD5 sum with input KEY, SALT, and KEY.  The
     final result will be added to the first context.  */
  __md5_init_ctx (&alt_ctx);

  /* Add key.  */
  __md5_process_bytes (key, key_len, &alt_ctx);

  /* Add salt.  */
  __md5_process_bytes (salt, salt_len, &alt_ctx);

  /* Add key again.  */
  __md5_process_bytes (key, key_len, &alt_ctx);

  /* Now get result of this (16 bytes) and add it to the other
     context.  */
  __md5_finish_ctx (&alt_ctx, alt_result);

  /* Add for any character in the key one byte of the alternate sum.  */
  for (cnt = key_len; cnt > 16; cnt -= 16)
    __md5_process_bytes (alt_result, 16, &ctx);
  __md5_process_bytes (alt_result, cnt, &ctx);

  /* For the following code we need a NUL byte.  */
  *alt_result = '\0';

  /* The original implementation now does something weird: for every 1
     bit in the key the first 0 is added to the buffer, for every 0
     bit the first character of the key.  This does not seem to be
     what was intended but we have to follow this to be compatible.  */
  for (cnt = key_len; cnt > 0; cnt >>= 1)
    __md5_process_bytes ((cnt & 1) != 0 ? (const char *) alt_result : key, 1,
			 &ctx);

  /* Create intermediate result.  */
  __md5_finish_ctx (&ctx, alt_result);

  /* Now comes another weirdness.  In fear of password crackers here
     comes a quite long loop which just processes the output of the
     previous round again.  We cannot ignore this here.  */
  for (cnt = 0; cnt < 1000; ++cnt)
    {
      /* New context.  */
      __md5_init_ctx (&ctx);

      /* Add key or last result.  */
      if ((cnt & 1) != 0)
	__md5_process_bytes (key, key_len, &ctx);
      else
	__md5_process_bytes (alt_result, 16, &ctx);

      /* Add salt for numbers not divisible by 3.  */
      if (cnt % 3 != 0)
	__md5_process_bytes (salt, salt_len, &ctx);

      /* Add key for numbers not divisible by 7.  */
      if (cnt % 7 != 0)
	__md5_process_bytes (key, key_len, &ctx);

      /* Add key or last result.  */
      if ((cnt & 1) != 0)
	__md5_process_bytes (alt_result, 16, &ctx);
      else
	__md5_process_bytes (key, key_len, &ctx);

      /* Create intermediate result.  */
      __md5_finish_ctx (&ctx, alt_result);
    }

  /* Now we can construct the result string.  It consists of three
     parts.  */
  cp = __stpncpy (buffer, md5_salt_prefix, MAX (0, buflen));
  buflen -= sizeof (md5_salt_prefix);

  cp = __stpncpy (cp, salt, MIN ((size_t) buflen, salt_len));
  buflen -= MIN ((size_t) buflen, salt_len);

  if (buflen > 0)
    {
      *cp++ = '$';
      --buflen;
    }

#define b64_from_24bit(B2, B1, B0, N)					      \
  do {									      \
    unsigned int w = ((B2) << 16) | ((B1) << 8) | (B0);			      \
    int n = (N);							      \
    while (n-- > 0 && buflen > 0)					      \
      {									      \
	*cp++ = b64t[w & 0x3f];						      \
	--buflen;							      \
	w >>= 6;							      \
      }									      \
  } while (0)

  b64_from_24bit (alt_result[0], alt_result[6], alt_result[12], 4);
  b64_from_24bit (alt_result[1], alt_result[7], alt_result[13], 4);
  b64_from_24bit (alt_result[2], alt_result[8], alt_result[14], 4);
  b64_from_24bit (alt_result[3], alt_result[9], alt_result[15], 4);
  b64_from_24bit (alt_result[4], alt_result[10], alt_result[5], 4);
  b64_from_24bit (0, 0, alt_result[11], 2);
  if (buflen <= 0)
    {
      __set_errno (ERANGE);
      buffer = NULL;
    }
  else
    *cp = '\0';		/* Terminate the string.  */

  /* Clear the buffer for the intermediate result so that people
     attaching to processes or reading core dumps cannot get any
     information.  */
  memset (alt_result, '\0', sizeof (alt_result));

  return buffer;
}


char *
__md5_crypt (const char *key, const char *salt)
{
  /* We don't want to have an arbitrary limit in the size of the
     password.  We can compute the size of the result in advance and
     so we can prepare the buffer we pass to `md5_crypt_r'.  */
  static char *buffer = NULL;
  static int buflen = 0;
  int needed = 3 + strlen (salt) + 1 + 26 + 1;

  if (buflen < needed)
    {
      buflen = needed;
      if ((buffer = realloc (buffer, buflen)) == NULL)
	return NULL;
    }

  return __md5_crypt_r (key, salt, buffer, buflen);
}
