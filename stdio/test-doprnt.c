#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>

extern int _doprnt (int (*f) __P ((int, FILE*)), FILE*, const char*, va_list);
static int snputc  (int ch, FILE* fp);

struct sinfo {
	char *bufp;
	size_t size;
	size_t max;
};

static int
snputc (ch, fp)
     int ch;
     FILE* fp;
{
	struct sinfo *sip = (struct sinfo *)fp;

	if (sip->size >= sip->max)
		return EOF;
	++sip->size;
	*(sip->bufp)++ = ch;
	return ((int) ch) & 0xff;
}

/* This is large enough to force several flushs and since it is prime 
   it should also leave some bytes unflushed at the end so that we can
   check if the buffer gets completely flushed.  */
#ifndef __MSHORT__
# define LARGEBUFSIZE 199999UL
#else
# define LARGEBUFSIZE 32719
#endif
char largesrc[LARGEBUFSIZE];
char largedest[LARGEBUFSIZE];

static int 
mysnprintf (char *buf, size_t len, const char *fmt, ...)
{
	register int n;
	va_list argp;
	struct sinfo si;

	si.bufp = buf;
	si.size = 0;
	si.max  = len-1;

	va_start (argp, fmt);
	n = _doprnt (snputc, (FILE *)&si, fmt, argp);
	if (si.size < si.max)
		*(si.bufp) = '\0';		/* always tie of the string */
	return n;
}


int
main (int argc, char* argv[])
{
	char buf[25];
	int status = 0;
#define MSG "It's the end of the world as we know it and I feel fine.\n"
	
	if (mysnprintf (buf, 25, MSG) != -1 
	    || strncmp (buf, "It's the end of the world", 24)) {
		printf ("test #1 failed\n");
		status = 1;
	}

	if (mysnprintf (buf, 25, "%s", MSG) != -1
	    || strncmp (buf, "It's the end of the world", 24)) {
		printf ("test #2 failed\n");
		status = 1;
	}
	
	if (mysnprintf (buf, 25, "This is test #%d.\n", 3) != 17
	    || strcmp (buf, "This is test #3.\n")) {
		printf ("test #3 failed\n");
		status = 1;
	}
	
	memset (largesrc, 'x', LARGEBUFSIZE - 1);
	largesrc[LARGEBUFSIZE - 1] = '\0';
	if (mysnprintf (largedest, LARGEBUFSIZE, "%s", largesrc) 
		!= LARGEBUFSIZE - 1L
	    || strcmp (largesrc, largedest)) {
	    	printf ("test #4 failed\n");
	    	status = 1;
	}

	return status;
}
