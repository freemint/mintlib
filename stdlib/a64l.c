/****************************************************************/
/* Module name:   a64l.c                                        */
/* Library name:  mintlibs for Atari ST                         */
/* Author:        Hildo Biersma (boender@dutiws.twi.tudelft.nl) */
/* Date:          January 11, 1993                              */
/* Revision:      1 (first attempt)                             */
/*                2 ++entropy Made compatible with K&R compilers*/
/****************************************************************/

/* FIXME: maybe use ERANGE or EDOM instead of EBADARG */

/*
NAME
    a64l, l64a - convert between long integer and base-64 ASCII string

SYNOPSIS
    #include <support.h>
    long a64l(const char *s);
    char *l64a(long l);

DESCRIPTION
    These functions are used to maintain numbers stored in base-64
    ASCII characters. This is a notation by which long integers
    can be represented by up to six characters; each character
    represents a "digit" in a radix-64 notation.
    
    The characters used to represent "digits" are . for 0, / for 1,
    0 through 9 for 2-11, A through Z for 12-37, and a through z
    for 38-63.
    
    a64l takes a pointer to a null-terminated base-64 representation
    and returns a corresponding long value. If the string pointed to
    by s contains more than six characters, a64l will use the first
    six. a64l scans the character string from left to right, decoding
    each character as a 6 bit radix-64 number. If the string contains
    illegal characters, -1 is returned and errno is set to EBADARG.
    
    l64a takes a long argument and returns a pointer to the
    corresponding base-64 representation. If the argument is 0, a64l
    returns a pointer to a null string. If the argument is smaller
    than zero, a pointer to a null string is returned and errno is
    set to EBADARG.

CAVEATS
    The value returned by l64a is a pointer into a static buffer,
    the contents of which are overwritten by each call.
    
    The value returned by a64l may be incorrect if the value
    is too large; for that reason, only strings that resulted
    from a call to l64a should be used to call a64l.

    Maybe these calls should unsigned long values, but longs are
    used here to retain compatibility with UN*X System V.

AUTHOR
    Hildo Biersma, with the help of a UN*X System V man page.
*/

#include <support.h>
#include <errno.h>


/* base-64 char to int, -1 on error */
static int a64i(c)
  char c;
{
  int retval = c;

  if ((c < '.') || (c > 'z'))
  {
    __set_errno (EBADARG);
    return(-1);
  }
  retval -= '.';
  if (c > '9')
    retval -= 'A' - '9' - 1;
  if (c > 'Z')
    retval -= 'a' - 'Z' - 1;
  if (retval > 63)
  {
    __set_errno (EBADARG);
    return(-1);
  }
  return(retval);
} /* End of a64i() */

/* base-64 string to long */
long a64l(s)
  const char *s;
{
  long retval = 0;
  int counter = 0;
  const char *ptr = s;

  while ((counter++ < 6) && (*ptr != 0x00))
  {
    int val;
    
    if ((val = a64i(*ptr++)) == -1)
      return(-1); /* errno was set by a64i() */
    retval <<= 6;
    retval += val;
  }
  return(retval);
} /* End of a64l() */

