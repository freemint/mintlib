/*
 *
 * Crtinit: C run-time initialization code.
 * Written by Eric R. Smith, and placed in the public domain.
 * Use at your own risk.
 *
 * 01/03/89 ++jrb
 *	The (new) meaning of _stksize: (thanks to allan pratt for the feedback)
 *
 *	_stksize			meaning
 *	  -1L	    keep all of memory (except MINFREE at top) and do
 *		    mallocs from own heap, with heap grown upwards towards
 *		    stack, and the stack growing down towards heap,
 *		    with a minimum slush between them so that they
 *		    dont meet (only checked while malloc'ing). With
 *		    this model, further spawning is not possible, but it is
 *		    well suited for programs such as gcc-cc1 etc.
 *		    Thanks to Piet van Oostrum & Atze Dijkstra for this idea
 *
 *	0L	    keep minimum amount of memory. this is also the
 *		    case when _stksize is undefined by the user.
 *	1L	    keep 1/4 of memory, free 3/4 ( as in Alcyon GEMSTART)
 *	2L	    keep 2/4 (1/2), free rest
 *	3L	    keep 3/4, free 1/4
 *	other	    keep that many bytes
 *	-other	    keep |other| bytes, use the heap for mallocs
 *
 * 02/14/90 ++jrb (thanks edgar)
 *	auto acc detect
 *	undump friendly
 *
 * NOTE: dumping applications should use _initial_stack instead: if
 *	 !=0, then _stksize is initialized from _initial_stack, and
 *	 mallocs are always from internal heap. (TeX works much better now),
 *	 thanks edgar!
 *
 * Acc convention:
 *      Preferred: user sets _stksize, then _heapbase is set to Malloc(_stksize)
 *      sp to _heapbase + _stksize and all mallocs happen from heap
 *
 *      Old way:
 *	user sets _heapbase to bottom of stack + heap area
 *	     sets _stksize to the size of this area
 *	     at startup, sp will be set to top of this area
 *	     (_heapbase  + _stksize ) and malloc()'s will happen from heap.
 *		(note malloc() and *not* Malloc())
 *
 * 02/16/90 ++jrb
 *  - bug fix: dont get screwed by desktop launch when fast bit is set
 *             convert env string to format usable
 *		(atari get your act together!!)
 *
 * 09-20-92 hyc
 *	Support base relative addressing, for shared-text execution.
 *	Also merged in some stuff from ++jrb's crt0.c.
 *
 * Turbo / Pure C version 21-6-92 um
 *   the Turbo / Pure linker reserves stack space in the BSS and sets
 *   the symbol _StkSize to its size. If _StkSize is set to 0, we use
 *   _stksize etc. as usual
 *
 * 19 Jan 93 hohmuth
 *	new variable _PgmSize, holds size of program area
 *	(useful when doing Ptermres)
 *
 * 08 Apr 93 hohmuth
 *	added support for ARGV standard extension allowing empty arguments
 *
 */

/* define this symbol to get ARGV argument passing that's strictly
 * compatible with the Atari standard. If it's not defined, then
 * the startup code won't validate the ARGV= variable by checking
 * the command byte for 0x127. Note that there are still some
 * applications (gulam is a notable example) that implement only
 * part of the standard and don't set the command byte to 0x127.
 */

#if 0
#define STRICTLY_COMPATIBLE_WITH_STANDARD
#endif

#include <basepage.h>
#include <osbind.h>
#include <support.h>
#include <string.h>
#include "lib.h"

#define isspace(c) ((c) == ' '||(c) == '\t')
#define isdigit(c) ((c) >= '0' && (c) <= '9')

#define MINFREE	(8L * 1024L)		/* free at least this much mem */
					/* on top */
#define MINKEEP (17L * 1024L)		/* keep at least this much mem */

extern BASEPAGE *_base;
extern char **environ;
extern long __libc_argc;
extern char** __libc_argv;

/* size to be allocated for the stack */
extern long _stksize;		/* picked up from user or from stksiz.c */

/* set to heap base addr when _stksize < 0 || _initial_stack || When DA
 * note that we allow the user to provide a _heapbase of their own, since
 * that used to be necessary for acc's; but that is no longer needed
 * (or encouraged) since the acc startup code now Mallocs a heap
 * automatically
 */
extern void *_heapbase;		/* picked up from user or from heapbase.c */

/*
 * initial stack is used primarily by dumping application,
 * if it is, malloc is always from heap, and _stksize is init
 * from initial_stack (to preserve the value in the undumped run)
 */
extern long _initial_stack;	/* picked up from user or from inistack.c */

extern unsigned long _PgmSize;	/* total size of program area */

#ifdef __TURBOC__
extern char *_StkLim;	/* for Turbo / Pure C stack checking */
extern _StkSize; /* set by linker */
#endif

/* are we an app? */
extern short _app;

/* are we on a split addr mem ST */
extern short _split_mem;

static long parseargs	__PROTO((BASEPAGE *));

/*
 * accessories start here:
 */

static char	*acc_argv[] = {"", (char *) 0}; /* no name and no arguments */

extern char* program_invocation_name;
extern char* program_invocation_short_name;

void _acc_main()
{
#ifdef __TURBOC__
	if (&_StkSize == 0)
	{
#endif

	if (_stksize == 0 || _stksize == -1L)
		_stksize = MINKEEP;

	if (_stksize < 0)
		_stksize = -_stksize;
	_stksize &= 0xfffffffeL;	/* stack on word boundary */

#ifdef __TURBOC__
	}
	else
	{
		/* This compound statement is executed if the Pure linker
		has reserved space for the stack in the BSS */
		_stksize = (long) &_StkSize;
		_heapbase = _base->p_bbase + _base->p_blen - _stksize;
	}
	_StkLim = (char *) _heapbase + 256;	 /* for stack checking */
#endif
  
	if (_heapbase == 0) {
		_heapbase = (void *)Malloc(_stksize);
	}
	_setstack((char *) _heapbase + _stksize);
	_app = 0;				/* this is an accessory */

	_main(1L, acc_argv, acc_argv);
	/*NOTREACHED*/
}

void _crtinit()
{
	register BASEPAGE *bp;
	register long m;
	register long freemem;
#ifdef __GNUC__
	extern void etext();	/* a "function" to fake out pc-rel addressing */
#endif
	_app = 1;	/* its an application */

	bp = _base;

	m = parseargs(bp);	/* m = # bytes used by environment + args */

/* make m the total number of bytes required by program sans stack/heap */
	m += (bp->p_tlen + bp->p_dlen + bp->p_blen + sizeof(BASEPAGE));
	m = (m + 3L) & (~3L);

#ifdef __TURBOC__
	if (&_StkSize == 0)
	{
#endif

/* freemem the amount of free mem accounting for MINFREE at top */
	if((freemem = (long)bp->p_hitpa - (long)bp - MINFREE - m) <= 0L)
	    goto notenough;
	
	if(_initial_stack)
	{
	    /* the primary use of _initial_stack will be in dumping */
	    /* applications where only a heap for malloc makes sense */
	    _heapbase = (void *) ((long)bp + m);
	    _stksize = _initial_stack;
	} else {
	    if (_stksize >= -1L)
		_split_mem = 1; /* malloc from Malloc first, then from own heap */
	}

	if (_stksize == -1L) {
	    _stksize = freemem;
	    _heapbase = (void *) ((long)bp + m);
	} else if (_stksize == 0L) {	/* free all but MINKEEP */
	    _stksize = MINKEEP;
	} else if (_stksize == 1L) { 	/* keep 1/4, free 3/4 */
	    _stksize = freemem >> 2;
	} else if (_stksize ==  2L) {	/* keep 1/2, free 1/2 */
	    _stksize = freemem >> 1;
	} else if (_stksize == 3L) {	/* keep 3/4, free 1/4 */
	    _stksize = freemem - (freemem >> 2); 
	} else {
	    if(_stksize < -1L) { /* keep |_stksize|, use heap for mallocs */
		_stksize = -_stksize;
		_heapbase = (void *)((long)bp + m);
	    }
	}
	
/* make m the total number of bytes including stack */
	_stksize = _stksize & (~3L);
	m += _stksize;

/* make sure there's enough room for the stack */
	if (((long)bp + m) > ((long)bp->p_hitpa - MINFREE))
	    goto notenough;

/* set up the new stack to bp + m  */

#ifdef __TURBOC__
	{
		char *tmp;
		tmp = (char *) bp + m;
		_setstack(tmp);
		_StkLim = tmp - _stksize + 256; /* for stack checking */
	}
#else
	_setstack((char *)bp + m);
#endif

#ifdef __TURBOC__
	} /* if (&_StkSize == 0) */
	else
	{
		/* This compound statement is executed if the Pure linker
		has reserved space for the stack in the BSS */
		_stksize = (long) &_StkSize;
		_stksize = _stksize & (~3L);
		
		{
			char *tmp;
			tmp = (char *) bp->p_bbase + bp->p_blen;
			_setstack(tmp);
			_StkLim = tmp - _stksize + 256; /* for stack checking */
			_heapbase = NULL; /* no mallocs from heap */
		}
	}
#endif /* __TURBOC__ */

/* shrink the TPA */
	(void)Mshrink(bp, m);

/* keep length of program area */
	_PgmSize = m;

/* establish handlers,  call the main routine */
	_init_signal();

/* start profiling, if we were linked with gcrt0.o */
#ifdef __GNUC__
	_monstartup((void *)bp->p_tbase, (void *)((long)etext - 1));
#else
	_monstartup((void *)(bp->p_tbase), 
		   (void *)((long)bp->p_tbase +  bp->p_tlen));
#endif

	_main(__libc_argc, __libc_argv, environ);
	/* not reached normally */

notenough:
	Cconws("Fatal error: insufficient memory\r\n");
		Pterm(-1);
}


/*
 * parseargs(bp): parse the environment and arguments pointed to by the
 * basepage. Return the number of bytes of environment and arguments
 * that have been appended to the bss area (the environ and argv arrays
 * are put here, as is a temporary buffer for the command line, if
 * necessary).
 *
 * The MWC extended argument passing scheme is assumed.
 *
 */

static long parseargs(bp)
	BASEPAGE *bp;
{
	long count = 4;		/* compensate for aligning */
	long  i;
	char *from, *cmdln, *to;
	char **envp, **arg;
	char *null_list = 0;
/* flag to indicate desktop-style arg. passing */
	long desktoparg;

/* handle the environment first */

	environ = envp = (char **)(( (long)bp->p_bbase + bp->p_blen + 4) & (~3));
	from = bp->p_env;
	while (*from) {

/* if we find MWC arguments, tie off environment here */
		if (*from == 'A' && *(from+1) == 'R' && *(from+2) == 'G' &&
		    *(from+3) == 'V' && *(from+4) == '=')
		{
			*envp++ = (char *) 0; count += 4;
			*from = 0;
#ifdef STRICTLY_COMPATIBLE_WITH_STANDARD
			if (bp->p_cmdlin[0] != 127)
				goto old_cmdlin;
#endif
			from += 5;        /* skip ARGV= string */

			/* find list of empty params
			 */
			if (*from == 'N' && *(from+1) == 'U'
			    && *(from+2) == 'L' && *(from+3) == 'L' 
			    && *(from+4) == ':')
			{
				null_list = from + 5;
			}
			    
			while (*from++) ; /* skip ARGV= value */
			__libc_argv = arg = envp;
			*arg++ = from; count+= 4;
			while (*from++) ; /* skip __libc_argv[0] */
			goto do_argc;
		}
		*envp++ = from;
		count += 4;
		desktoparg = 1;
		while (*from) {
			if (*from == '=') {
				desktoparg = 0;
			}
			from++;
		}
		from++;		/* skip 0 */

/* the desktop (and some shells) use the environment in the wrong
   way, putting in "PATH=\0C:\0" instead of "PATH=C:". so if we
   find an "environment variable" without an '=' in it, we
   see if the last environment variable ended with '=\0', and
   if so we append this one to the last one
 */
		if(desktoparg && envp > &environ[1]) 
		{
		/* launched from desktop -- fix up env */
		    char *p, *q;

		    q = envp[-2];	/* current one is envp[-1] */
		    while (*q) q++;
		    if (q[-1] == '=') {
			p = *--envp;
			while(*p)
			   *q++ = *p++;
		        *q = '\0';
		   }
		}
	}
	*envp++ = (char *)0;
	count += 4;

#ifdef STRICTLY_COMPATIBLE_WITH_STANDARD
old_cmdlin:
#endif
/* Allocate some room for the command line to be parsed */
	cmdln = bp->p_cmdlin;
	i = *cmdln++;
	from = to = (char *) envp;
	if (i > 0) {
		count += (i&(~3));
		envp = (char **) ( ((long) envp)  + (i&(~3)) );
	}
	envp += 2; count += 8;

/* Now parse the command line and put __libc_argv after the environment */

	__libc_argv = arg = envp;
	*arg++ = "";		/* __libc_argv[0] not available */
	count += 4;
	while(i > 0 && isspace(*cmdln) )
		cmdln++,--i;

	/* 
	 * MagXDesk only uses ARGV if the arg is longer than the 126 character
	 * of bp->cmdlin. If the arg is short enough and contains a file name with
	 * blanks it will be come quoted via bp->cmdlin!!
	*/ 
	if (cmdln[0] != '\'')
	{
		while (i > 0) {
			if (isspace(*cmdln)) {
				--i; cmdln++;
				while (i > 0 && isspace(*cmdln))
					--i,cmdln++;
				*to++ = 0;
			}
			else {
				if ((*to++ = *cmdln++) == 0) break;
				--i;
			}
		}
	}
	else
	{
		int in_quote = 0;
		
		while (i > 0) 
		{
			if (*cmdln == '\'')
			{
				i--; 
				cmdln++;
				if (in_quote)
				{
					if (*cmdln == '\'')		/* double ': file name contains ' */
					{
						*to++ = *cmdln++;
						i--;
					}
					else
					{
						in_quote = 0;
						*to++ = 0;				/* end of quoted arg */
						i--; cmdln++;
					}
				}
				else
					in_quote = 1;
			}
			else
			{
				if (*cmdln == ' ')
				{
					if (in_quote)
					{
						*to++ = *cmdln++;
						i--;
					}
					else
					{
						--i; cmdln++;
						*to++ = 0;
					}
				}
				else
				{
					*to++ = *cmdln++;
					i--;
				}
			}
		}
	}

	*to++ = '\0';
	*to = '\0'; /* bug fix example:cmdln == '\3' 'a' ' ' 'b' '\0' */
	/* the loop below expects \0\0 at end to terminate! */
	/* the byte @ cmdln[i+2] != 0 when fast bit is set */
do_argc:
	/* Find out the name we have been invoked with.  */
 	if (__libc_argv[0] != 0 && __libc_argv[0][0] != '\0') {
 	  char* p;
 	  program_invocation_name = __libc_argv[0];
 	  p = strrchr (program_invocation_name, '\\');
 	  if (p == 0)
 	    p = strrchr (program_invocation_name, '/');
 	  if (p != 0)
 	    p++;
 	  program_invocation_short_name = p == 0 ? 
 	      program_invocation_name : p;
 	}
 	
	__libc_argc = 1;		/* at this point __libc_argv[0] is done */
	while (*from) {
		*arg++ = from;
		__libc_argc++;
		count += 4;
		while(*from++) ;
	}
	*arg = (char *) 0;

	/* zero epmty params
	 */
	if (null_list) {
		char *s;
		unsigned long idx;

		while (*null_list) {
			s = null_list;
			
			while (* ++null_list) {	/* find ',' or '\0' */
				if (*null_list == ',') {
					*null_list++ = 0;
					break;
				}
			}
			
			idx = 0;
			for (;;) {
				if (! isdigit(*s))
					goto bail_out;
					
				/* don't feed this to strtol(),
				 * do the ascii -> long conversion by 
				 * hand for efficency
				 */
				idx += *s++ - '0';
				if (*s)
					idx = (idx << 3) + (idx << 1);
				else
					break;
			}
		
			if (idx < __libc_argc)
				*(__libc_argv[idx]) = 0;
			else
				goto bail_out;
		}
	}

bail_out:
	return count+4;
}
