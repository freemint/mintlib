#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


/* Return orientation of stream.  If mode is nonzero try to change
   the orientation first.  */
#undef _IO_fwide
int
fwide (FILE *fp, int mode)
{
  /* Normalize the value.  */
  mode = mode < 0 ? -1 : (mode == 0 ? 0 : 1);

  (void) fp;
#ifdef NOTYET
  /* The orientation already has been determined.  */
  if (fp->_mode != 0
      /* Or the caller simply wants to know about the current orientation.  */
      || mode == 0)
    return fp->_mode;

  /* Set the mode now.  */
  fp->_mode = mode;
#endif

  return mode;
}



