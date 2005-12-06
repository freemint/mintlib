/*  fgetpwent_r.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
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

int __fgetpwent_r (FILE* stream, struct passwd* result_buf, char* buffer, 
                   size_t buflen, struct passwd** result)
{
  char* write_crs = buffer;
  size_t bytes_used = 0;
  char** fields[10];
  int numerical_error = 0;
  
  enum parse_state { init = 0, name = 1, password = 2, age = 3, uid = 4, 
                     gid = 5, gecos = 6, home = 7, shell = 8,
                     finished = 9 } state;
  
  if (stream == NULL || result == NULL || result_buf == NULL)
    {
      __set_errno (EFAULT);
      return -1;
    }
  else if (buffer == NULL)
    buflen = 0;
    
  fields[0] = NULL;
  fields[1] = &result_buf->pw_name;
  fields[2] = &result_buf->pw_passwd;
  fields[3] = &result_buf->pw_age;
  fields[4] = NULL;
  fields[5] = NULL;
  fields[6] = &result_buf->pw_gecos;
  fields[7] = &result_buf->pw_dir;
  fields[8] = &result_buf->pw_shell;
  fields[9] = NULL;
  
  *result = NULL;
  
  /* Now parse the passwd file.  The technique looks awkwared but I don't
     see anything better.  We read characters one by one from the 
     passwd file keeping track of the current parse state.  If we are in
     a state that reads a string then we copy the currently read byte
     into the user-supplied buffer.  For numerical fields we re-calculate
     the current value.  Thus we optimize the usage of the buffer and
     we stay re-entrant.  */
  state = init;
  memset (result_buf, 0, sizeof *result_buf);
  result_buf->pw_name 
       = result_buf->pw_passwd 
       = result_buf->pw_age 
       = result_buf->pw_gecos
       = result_buf->pw_comment
       = result_buf->pw_dir
       = result_buf->pw_shell
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
          if (state == age)  /* No password aging found.  */
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
      
      if (bytes_used < buflen && fields[state] != NULL 
          && *fields[state] != NULL)
        {
          *write_crs++ = the_char;
          bytes_used++;
        }
        
      switch (state)
        {
          case uid:
            if (the_char < '0' || the_char > '9')
              numerical_error = 1;  /* Should we return an error instead?  */
            else if (!numerical_error)
              {
                result_buf->pw_uid *= 10;
                result_buf->pw_uid += the_char - '0';
              }
            break;
          case gid:
            if (the_char < '0' || the_char > '9')
              numerical_error = 1;  /* Should we return an error instead?  */
            else if (!numerical_error)
              {
                result_buf->pw_gid *= 10;
                result_buf->pw_gid += the_char - '0';
              }
            break;
          case password:
            if (the_char == ',')
              {
                /* Age count found.  */
                if (bytes_used <= buflen && fields[state] != NULL 
                    && *fields[state] != NULL)
                  {
                    /* The comma has already been written.  */
                    write_crs[-1] = '\0';
                  }
                ++state;
            
                if (bytes_used < buflen && fields[state] != NULL)
                  *fields[state] = write_crs;
              }
            break;
          default:
            break;
        }
    }
  
  result_buf->pw_comment = result_buf->pw_gecos;
  *result = result_buf;
  return 0;
}

weak_alias (__fgetpwent_r, fgetpwent_r)
