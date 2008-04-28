/*  fgetspent_r.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <shadow.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static char* space = "";

/* Ignore \r before \n.  */
static int my_getc (FILE* stream)
{
  int retval = getc (stream);
  if (retval == '\r')
    {
      int next = getc (stream);
      if (next == '\n')
        return next;
      else ungetc (next, stream);
    }
  return retval;
}

int __fgetspent_r (FILE* stream, struct spwd* result_buf, char* buffer, 
                   size_t buflen, struct spwd** result)
{
  char* write_crs = buffer;
  size_t bytes_used = 0;
  char** fields[11];
  void *tmp;
  int numerical_error = 0;
  
  enum parse_state { init = 0, namp = 1, pwdp = 2, lstchg = 3, min = 4, 
                     max = 5, warn = 6, inact = 7, expire = 8,
                     flag = 9, finished = 10 } state;
  
  if (stream == NULL || result == NULL || result_buf == NULL)
    {
      __set_errno (EFAULT);
      return -1;
    }
  else if (buffer == NULL)
    buflen = 0;
    
  fields[0] = NULL;
  fields[1] = &result_buf->sp_namp;
  fields[2] = &result_buf->sp_pwdp;
  tmp = &result_buf->sp_lstchg;
  fields[3] = (char**) tmp;
  tmp = &result_buf->sp_min;
  fields[4] = (char**) tmp;
  tmp = &result_buf->sp_max;
  fields[5] = (char**) tmp;
  tmp = &result_buf->sp_warn;
  fields[6] = (char**) tmp;
  tmp = &result_buf->sp_inact;
  fields[7] = (char**) tmp;
  tmp = &result_buf->sp_expire;
  fields[8] = (char**) tmp;
  tmp = &result_buf->sp_flag;
  fields[9] = (char**) tmp;
  fields[10] = NULL;
  
  *result = NULL;
  
  /* Now parse the shadow file.  The technique looks awkwared but I don't
     see anything better.  We read characters one by one from the 
     shadow file keeping track of the current parse state.  If we are in
     a state that reads a string then we copy the currently read byte
     into the user-supplied buffer.  For numerical fields we re-calculate
     the current value.  Thus we optimize the usage of the buffer and
     we stay re-entrant.  */
  state = init;
  memset (result_buf, 0, sizeof *result_buf);
  result_buf->sp_namp 
       = result_buf->sp_pwdp
       = space;
  while (state != finished)
    {
      int the_char = my_getc (stream);
      
      if (state == init)
        {
          if (the_char == ' ' || the_char == '\t' || the_char == '\r'
              || the_char == '\n')
            continue;
          else if (the_char == '#')
            {
              /* A comment, eat up the rest of the line.  */
              while (1)
                {
                  the_char = my_getc (stream);
                  if (the_char == '\n')
                    break;
                  else if (the_char == EOF)
                    {
                      *result = NULL;
                      return -1;
                    }
                }
              continue;
            }
          else if (the_char == EOF)
            {
              *result = NULL;
              return -1;
            }
          else
            {
              state++;
              ungetc (the_char, stream);
              *fields[state] = write_crs;
              continue;
            }
        }
        
      if (the_char == ':')
        {
          if (fields[state] != NULL && *fields[state] != NULL)
            {
              *write_crs++ = '\0';
              bytes_used++;
            }
          ++state;
              
          if (bytes_used < buflen && fields[state] != NULL)
            *fields[state] = write_crs;
          numerical_error = 0;
          continue;
        }
      else if (the_char == '\n' || the_char == EOF)
        {
          /* Hm, what about crippled entries?  Let the program handle
             this.  */
          if (state > init)
            {
              if (bytes_used < buflen && fields[state] != NULL
                  && *fields[state] != NULL)
                {
                  *write_crs++ = '\0';
                  bytes_used++;
                }
              else if (fields[state] != NULL)
                *fields[state] = NULL;  /* Invalidates last read entry.  */
              state = finished;
            }
          else if (the_char == EOF)
            {
              *result = NULL;
              return -1;
            }
          continue;
        }
      
      if (bytes_used < buflen 
          && (state == namp || state == pwdp) 
          && fields[state] != NULL && *fields[state] != NULL)
        {
          *write_crs++ = the_char;
          bytes_used++;
          continue;
        }
      /* Numerical field.  */
      if (the_char < '0' || the_char > '9')
        numerical_error = 1;
      else if (!numerical_error)
        {
          long int* longptr = (long int*) fields[state];
          *longptr *= 10;
          longptr += the_char - '0';
        }
    }
  
  *result = result_buf;
  return 0;
}

weak_alias (__fgetspent_r, fgetspent_r)
