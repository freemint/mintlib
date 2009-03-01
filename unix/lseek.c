#include <errno.h>
#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mint/osbind.h>

/*
 * emulate berzerkly lseek too
 */
off_t
__lseek (int handle, off_t offset, int mode)
{
    long current_pos;
    long expected_pos;
    long new_pos;
    char buf[256];
    
    if ( (mode == SEEK_END) || (offset <= 0) )
	/* do it the usual way */
      {
	current_pos = Fseek (offset, handle, mode);
	if (current_pos < 0)
	  {
            if (-current_pos == EBADARG) 
	      __set_errno(EINVAL); /* filesystems should return this - fix up */
	    else
	      __set_errno ((int) -current_pos);
	    return -1L;
	  }
	return current_pos;
      }
    
    current_pos = Fseek (0L, handle, SEEK_CUR); /* find out where we are */
    if (current_pos < 0)
      {
        if (-current_pos == EBADARG) 
	  __set_errno(EINVAL); /* filesystems should return this - fix up */
	else
	  __set_errno ((int) -current_pos); /* an unseekable device */

	return -1L;
      }

    if (mode == SEEK_SET)
	expected_pos = offset;
    else
	expected_pos = offset + current_pos;
    new_pos = Fseek (offset, handle, mode);
    if (new_pos == expected_pos)
	return new_pos;
    
    /* otherwise extend file -- zero filling the hole */
    if (new_pos < 0)		/* error? */
    {
	new_pos = Fseek (0L, handle, SEEK_END);	/* go to eof */
    }	
    
    __bzero (buf, (size_t)256);
    while (expected_pos > new_pos)	
    {
	offset = expected_pos - new_pos;
	if (offset > 256) 
	    offset = 256;
	if((current_pos = write(handle, buf, offset)) != offset)
	    return((current_pos > 0) ? (new_pos + current_pos) :
		   -1L);	/* errno set by write */
	new_pos += offset;
    }
    return(new_pos);  
}
weak_alias (__lseek, lseek)
