
#include <support.h>
#include <errno.h>


/* integer to base-64 char, 0x7F on error */
static char i64a(i)
  int i;
{
  char retval = (char)i;
  
  if ((i < 0) || (i > 63))
  {
    __set_errno (EBADARG);
    return(0x7F);
  }
  retval += '.';
  if (i > 11)
    retval += 'A' - '9' - 1;
  if (i > 37)
    retval += 'a' - 'Z' - 1;
  return(retval);
} /* End of i64a() */

/* long to base-64 string */
char *l64a(l)
  long l;
{
  static char retval[7];
  char buffer[7], *ptr1 = buffer, *ptr2 = retval;
  int counter = 0;

  if (l < 0)
  {
    __set_errno (EBADARG);
    return("");
  }
  if (l == 0)
    return("");
  while ((counter++ < 6) && (l > 0))
  {
    char val;
    
    if ((val = i64a((char)(l & 0x3F))) == 0x7F)
      return(""); /* errno was set by i64a() */
    *ptr1++ = val;
    l >>= 6;
  }
  while (ptr1 > buffer)
    *ptr2++ = *(--ptr1);
  *ptr2 = 0x00;
  return(retval);
} /* End of l64a() */
