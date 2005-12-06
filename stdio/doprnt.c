/*  doprnt.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define DOPRNT_BUFSIZE 1024

typedef int putfunc (int c, FILE* stream);

static void doprnt_output __P ((FILE* ptr, int c));

struct doprnt_arg {
	putfunc* putf;
	FILE* ptr;
};

/* This is the classic interface to printf and friends, provided for
   binary compatibility with compiled code that references it.
   
   Write formatted output to STREAM according to the format string FMT,
   using the argument list in ARG, and PUTF to output the resulting
   string.  
   
   Note that we must not interpret anything into the STREAM argument.
   It is merely a pointer that is used in the PUTF.  */
int 
_doprnt (putfunc* putf, FILE* stream, 
         const char* fmt, va_list arg)
{
	FILE file;
	char buf[DOPRNT_BUFSIZE];		/* Minimal buffer.  */
	int retval;
	struct doprnt_arg doprnt_args = { putf, stream };
	
	__bzero ((void*) &file, sizeof (file));
	file.__magic = _IOMAGIC;
	file.__mode.__write = 1;
	file.__bufp = file.__buffer = buf;
	file.__put_limit = buf + DOPRNT_BUFSIZE;
	file.__get_limit = file.__buffer;
	file.__bufsize = DOPRNT_BUFSIZE;
	file.__seen = 1;
	file.__room_funcs.__input = NULL;
	file.__room_funcs.__output = doprnt_output;
	file.__userbuf = 1;
	file.__cookie = &doprnt_args;
	
	retval = vfprintf (&file, fmt, arg);

	/* Flush the stream.  */
	if (retval >= 0)
		if (__flshfp (&file, EOF) != 0)
			return -1;
			
	return retval;
}

static void 
doprnt_output (FILE* stream, int c)
{
	register size_t to_write;
	register size_t i;
  	register putfunc* putf = 
  		((struct doprnt_arg*) (stream->__cookie))->putf;
 	register FILE* ptr = ((struct doprnt_arg*) (stream->__cookie))->ptr;
 	register char* crs;

  	to_write = stream->__bufp > stream->__buffer ? 
  		stream->__bufp - stream->__buffer : 0;
  	crs = stream->__buffer;

  	for (i = 0; i < to_write; i++, crs++) {
  		if ((*putf) ((int) *crs, ptr) != (int) *crs) {
  			stream->__error = 1;
  			return;
  		}
  	}
  	
  	if (c != EOF && (*putf) (c, ptr) != c) {
  			stream->__error = 1;
  			return;
  	}
  	
  	/* Reset buffer pointer.  */
  	stream->__bufp = stream->__buffer;
}
