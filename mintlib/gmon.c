/*
 * monitor(3), mcount() and profil(2) clones for gcc-Tos library
 *
 * Note: these routines need tuning up. they are very space
 * inefficient. the implementation is totally biased towards support
 * for gprof rather than prof (does anyone use prof anymore? why?)
 *
 *	++jrb	bammi@cadence.com
 */
 
/* Changed May 99 to support gprof 2.9.1.  The new format is incompatible
   to the old one.  To revert to the old format set the envariable
   "OLD_GMON" while the program is running.  */
   
/* Changed again March 2000 to remove external references that will 
   cause an infinite loop when profiling the library itself.  */
   
#include <stddef.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#define NDEBUG
#include <assert.h>
#include <mintbind.h>
#include <basepage.h>
#include <sysvars.h>
#include <xbra.h>
#include <string.h>
#include <stdlib.h>
#include <mint/ssystem.h>

/* gmon header */
struct gm_header {
    void		*low;		/* low pc  */
    void		*high;		/* hi  pc  */
    unsigned long	nbytes;		/* bytes in header + histo size */
};

typedef unsigned short CHUNK; /* type of each histogram entry */

struct gm_call {	/* gm call record */
    void	*from;	/* the caller 				*/
    void	*to;	/* the called function (callee)		*/
    unsigned long ncalls; /* # of calls from FROM to  TO	*/
};

#define	GMON_FILE	"gmon.out"	/* name of GMON file */

/* format of gmon file
 *	gm_header
 *	((gm_header.nbytes - sizeof(gm_header))/sizeof(CHUNK)) histo entries
 *	gm_call records upto EOF
 */


/* histogram variables and defines */
#define	HIST_SCALE	2 /* text space scaled into size/HIST_SCALE  CHUNKS */
#define HIST_SHIFT	1 /* HIST_SCALE == 2 ** HIST_SHIFT (assumption) */
			  /* 1 <= HIST_SHIFT <= 8          (assumption) */

static CHUNK *hist_buffer;	/* histogram buffer */
static unsigned long hist_size; /* size of histogram in bytes */

/* call graph variables and defines */
typedef struct  {	/* a to chain element */
    void	*selfpc;	/* the callee's pc */
    unsigned long count;	/* number of times called */
    unsigned short link;	/* link to next in chain (an index) */
} tostruct ;

tostruct       *tos;		/* pool of to chain elements */
unsigned short *froms;		/* called from hash chain heads (an index) */
 /* inherent assumption: typeof froms == typeof CHUNK, otherwise
    change code in monstartup() */

#define MINARCS	64		/* min # of to's, a rand() # */
#define ARCDENSITY 2		/* scaling of to's (as a % of  textsize) */
#define HASHFRACTION 1		/* scaling of froms over textsize. 
				   note this is very memory wasteful,
				   but the alternatives are worse 
				   beacuse of two reasons:
				   - increase compute requirements(in mcount)
				   - bsr, followed by bsr will loose!
				   the coding of mcount below almost
				   assumes that HASHFRACTION==1
				   anyone else have some brilliant ideas?
				   */
#define HASH_SHIFT 0	/* HASHFRACTION = 2 ** HASH_SHIFT (assumption) */

/* housekeeping variables */
static long	      profiling;	/* profiling flag */
static unsigned long  textsize;		/* size of profiled text area */
static unsigned short tolimit;		/* max to == 65534, min == MINARCS */
static unsigned short toalloc;		/* next free to record index  */
static void 	      *s_lowpc;		/* low  pc rounded down to multiples
					   of histo density =
					   (CHUNK size * HIST_SCALE)
					   (assumption: its mult of 2)
					 */

#define USL(X)	((unsigned long)(X))	/* cast X to unsigned long */

/* round X down to last multiple of Y */ /* see assumption above */
#define ROUNDDOWN(X,Y)	( USL(X) & (~(USL((Y)-1))) ) 

/* round X up to next multiple of Y */
#define ROUNDUP(X,Y)	( USL((X)+((Y)-1)) & (~(USL((Y)-1))) )

/* functions */
__EXTERN void monstartup __PROTO((void *lowpc, void *highpc));
__EXTERN void monitor __PROTO((void *lowpc, void *highpc, void *buffer,
		 unsigned long bufsize,  unsigned int nfunc));
__EXTERN void moncontrol __PROTO((long flag));
__EXTERN void _mcleanup __PROTO((void));
__EXTERN int profil __PROTO((void *buff, unsigned long bufsiz, unsigned long offset,
	       int shift));
/* static */ void tick __PROTO((void));
static void term __PROTO((void));
static void install_handlers __PROTO((void));
static void remove_handlers __PROTO((void));
static void unlink_handler __PROTO((xbra_struct *me, int exc));
static void build_graph __PROTO((void *caller, void *callee));
static long mon_get_sysvar __PROTO((void* var));

#define MON_WRITE(fd, buf, size) Fwrite (fd, size, buf)

extern int __has_no_ssystem;

static
long mon_get_sysvar (void* var)
{
	long ret;
    	long save_ssp;

	if(__has_no_ssystem) {
    		save_ssp = (long) Super((void *) 0L);
    	/* note: dont remove volatile, otherwise gcc will reorder these
       	statements and we get bombs */
    		ret = *((volatile long *)var);
    		(void)Super((void *) save_ssp);
    		return ret;
	} else
		return Ssystem(S_GETLVAL, var, NULL);
}

/*
 * allocate space for histogram and call graph given the sampling
 * range. call monitor to start up profiling.
 */

void monstartup(lowpc, highpc)
void *lowpc, *highpc;
{
    unsigned long	monsize; /* size of hist buffer + gm_header rounded */
    void		*buf;    /* hist + gm_header space */
    unsigned long	i;

    assert(USL(lowpc) < USL(highpc));

#if 0	/* dont define: screws up gmon because of reloc assumptions */
    s_lowpc = lowpc = (void *)
	(ROUNDDOWN(USL(lowpc), sizeof(CHUNK)<<HIST_SHIFT ));
#else
    s_lowpc = lowpc;
#endif
    highpc = (void *)
	(ROUNDUP(USL(highpc), sizeof(CHUNK)<<HIST_SHIFT ));
    textsize = USL(highpc) - USL(lowpc);

    /* allocate histogram buffer + gm_header buffer */
    monsize = (textsize >> HIST_SHIFT) * sizeof(CHUNK) +
	       sizeof(struct gm_header);
    monsize = ROUNDUP(monsize, sizeof(short));

    if((buf = (CHUNK *)Malloc(monsize)) == (CHUNK *)0)
    {
	Cconws("monitor: No memory for histogram buffer\r\n");
	froms = (unsigned short *)0;
	tos = (tostruct *)0;

	return;
    }
    __bzero(buf, monsize);

    /* allocate space for graph data structs */
    i = (textsize>>HASH_SHIFT) * sizeof(*froms);
    i = ROUNDUP(i, sizeof(long));
    if((froms = (unsigned short *)Malloc(i)) == (unsigned short *)0)
    {
	Cconws("monitor: No memory for FROMs\r\n");
	Mfree(buf);
	tos = (tostruct *)0;
	return;
    }
    __bzero(froms, i);
    
    i = textsize * ARCDENSITY / 100;
    if( i < MINARCS)
	i = MINARCS;
    else if ( i > 65534)
	i = 65534;
    tolimit = (unsigned short)i;
    i = ROUNDUP(i*sizeof(tostruct), sizeof(long));
    if((tos = (tostruct *)Malloc(i)) == (tostruct *)0)
    {
	Cconws("monitor: No memory for TOs pool\r\n");
	Mfree(froms);
	Mfree(buf);
	froms = (unsigned short *)0;
	return;
    }
    __bzero(tos, i);
    toalloc = 0;	/* index of next available element in TOs pool */

    monitor(lowpc, highpc, buf, monsize, (unsigned int)tolimit);
}

    
/*
 * monitor(3) interface to profil(2)
 * last arg is silly and not used
 */
void monitor(lowpc, highpc, buffer, bufsize, nfunc)
void *lowpc, *highpc, *buffer;
unsigned long bufsize;
unsigned int nfunc;
{
	struct gm_header *hdr;

	if(lowpc == 0)
	{ /* finished */
	    moncontrol(0L);
	    _mcleanup();
	    return;
	}

	s_lowpc = lowpc;	/* in case user is calling */
	/* initialize gm_header */
	hdr = (struct gm_header *)buffer;
	hdr->low = lowpc;
	hdr->high = highpc;
	hdr->nbytes = bufsize;

	hist_size = bufsize - sizeof(struct gm_header); /* sizof hist buffer */
	hist_buffer = (CHUNK *)(USL(buffer) + sizeof(struct gm_header));

	/* integ. check, (user can call monitor) */
	if((hist_size == 0) ||
           (hist_size <
	    (((USL(highpc) - USL(lowpc))>>HIST_SHIFT)*sizeof(CHUNK))) )
	{
	    return;
	}
	/* note: difference in scaling semantics from unix */
	moncontrol(1L); /* begin */
}

/*
 * control profiling
 */
void moncontrol(flag)
long flag;
{
    if(flag)
    { /* start */
	profil(hist_buffer, hist_size, (unsigned long)s_lowpc, HIST_SHIFT);
	profiling = 0;
    }
    else
    {
	/* stop */
	profil((void *)0, 0L, 0L, 0);
	profiling = 3;
    }
}

/*
 * mcount
 *	called as a part of the entry prologue of a profiled function.
 *	the function that calls mcount is the CALLEE, and the function
 *	that called the CALLEE is the CALLER. mcount grabs the
 *	address of the CALLEE and the address of the CALLER off the
 *	stack, and then calls build_graph that incrementally
 * 	constructs the call graphs in the FROMs and TOs structures,
 *	keeping track of the number of times the CALLER called CALLEE.
 *	on entry the stack look like:
 *
 *		sp-> |	ret address of CALLEE	|
 *		     |--------------------------|
 *		     .  CALLEE's locals		.
 *		     .__________________________.
 * CALLEEs	fp-> |  CALLERS saved fp	|
 *		     |--------------------------|
 *		     |  ret address of CALLER	|
 *		     |--------------------------|
 *
 * Note: 
 *	-this is true becuase -fomit-frame-pointer and -pg are
 *	 incompatible flags (gcc will say so if you try)
 *
 *	-on the 68k, the address of a long count location is passed in a0
 *	 we dont use this, it was a convention for the old prof stuff.
 */

#if __GNUC__ > 1
void mcount (void) asm ("mcount");

void
mcount ()
{
  void *callee, *caller;
  callee = (void *) __builtin_return_address (0);
  caller = (void *) __builtin_return_address (1);
  build_graph (caller, callee);
}
#else
    __asm__("\
  		.text; .even
 		.globl mcount	/* note: no `_' */
 	mcount:
 		movl	sp@,d0		/* CALLEE's address */
 		movl	d0,sp@-
 		movl	a6@(4),d0	/* CALLERs  address */
 		movl	d0,sp@-
 		jbsr	_build_graph	/* build_graph(caller, callee) */
 		addqw	#8,sp
 		rts
 	    ");
#endif

/*
 * build_graph
 *	incrementally build the call graph. at each call the CALLER
 *	and CALLEE are specified. this function builds an arc from
 *	CALLER to CALLEE, or increments the arc count if it already
 *	exists.
 *	the graph is maintianed in the structures FROMs and TOs. each
 *	entry in FROMs is the head of a chain of records of all
 *	functions called from FROM. The CALLERs address is hashed
 *	into FROMs
 */
static void build_graph(caller, callee)
void *caller, *callee;
{
    unsigned short	*fromp;	  /* hashed ptr into froms 		*/
    tostruct		*top;	  /* current hash chain element		*/
    unsigned short	ti;	  /* index of current chain element	*/
    tostruct		*last;	  /* previous element	   		*/
    
    if(profiling)
	return;	/* out if we are not profiling or this is a recursive call */
    profiling++;
    
    /* hash callee, to a pointer into FROMs */
    fromp = (unsigned short *)(USL(caller) - USL(s_lowpc)); /* lowpc orig */
    if(USL(fromp) > textsize)
    {	/* not within profiled text area */
	profiling--;
	return;
    }
    /* scale to an index */
    fromp = (unsigned short *)(USL(fromp) >> (HASH_SHIFT + sizeof(*froms)));
    fromp = &froms[((long)fromp)]; /* hash bucket pointer */
    ti = *fromp;	/* head of the chain */
    if(ti == 0)
    {	/* head is null, first time in the bucket, start a new chain */
	if((ti = ++toalloc) >= tolimit) /* allocate an element from tos pool */
	{	/* ran out */
	    profiling = 3; /* give up profiling */
	    return;
	}
	*fromp = ti;
	top = &tos[ti];
	top->selfpc = callee;
	top->count  = 1;
	top->link   = 0;
	profiling--;
	return;
    }
    /* otherwise  search the chain */
    for(last = top = &tos[ti]; top->link != 0;  last = top,
						top = &tos[top->link])
    {
	if(top->selfpc == callee)
	{ /* found it */
	    top->count++;	/* increment call count */
	    if(top == last)
	    { /* at the head of the chain already */
		profiling--;
		return;
	    }
	    /* otherwise bring it to the head */
	    ti = last->link;
	    last->link = top->link;
	    top->link = *fromp;
	    *fromp = ti;
	    profiling--;
	    return;
	}
    }
    /* not found */
    if((ti = ++toalloc) >= tolimit) /* allocate an element from tos pool */
    {	/* ran out */
	profiling = 3; /* give up profiling */
	return;
    }
    /* put it at head of the chain */
    top = &tos[ti];
    top->count = 1;
    top->selfpc = callee;
    top->link = *fromp;
    *fromp = ti;
    
    profiling--;
}

/*
 * _mcleanup
 *	dump out the gmon file
 */
void _mcleanup()
{
    int		fd;
    unsigned long   i;
    unsigned short  j;
    unsigned long   frompc;
    struct gm_call  arc;
    /* For new gmon.out format.  */
    unsigned long offset = (unsigned long) _base + 0x100;
    int new_format = 0;
    
    if((fd = Fcreate (GMON_FILE, 0)) < 0)
    {
	Cconws(GMON_FILE); Cconws(": error opening\r\n");
	return;
    }

    if (__secure_getenv ("OLD_GMON") == NULL)
      new_format = 1;
    
    if (new_format)
    {
      /* Convert the header and the call graph to the format that
         gprof 2.9.1 expects.  We only have to subtract the address
         of the text start segment from every entry.  */
      struct gm_header* hdr = (struct gm_header*) (USL (hist_buffer)
                               - sizeof (struct gm_header));
      hdr->low = (void*) ((char*) hdr->low - offset);
      hdr->high = (void*) ((char*) hdr->high - offset);
    }
        
    /* dump the header + histogram */
    if(MON_WRITE(fd, (void *)(USL(hist_buffer) - sizeof(struct gm_header)),
	   hist_size + sizeof(struct gm_header)) != 
       (hist_size + sizeof(struct gm_header)) )
    {
	Cconws(GMON_FILE); Cconws(": error writing\r\n");
	Fclose(fd); return;
    }

    /* dump the call graph */
    for( i = 0; i < (textsize >> (HASH_SHIFT + sizeof(*froms))); i++)
    {
	if(froms[i] != 0)
	{
	    frompc = USL(s_lowpc) + ( i << (HASH_SHIFT + sizeof(*froms)));
	      
	    for(j = froms[i]; j != 0; j = tos[j].link)
	    {
		arc.from = (void *)frompc;
		arc.to   = tos[j].selfpc;
		
		/* For new format relative to text start.  */
		if (new_format)
		{
		  arc.from = (void*) (frompc - offset);
		  arc.to = (void*) ((char*) tos[j].selfpc - offset);
		} 
		
		arc.ncalls = tos[j].count;
		if(MON_WRITE(fd, &arc, sizeof(arc)) != sizeof(arc))
		{
		    Cconws(GMON_FILE); Cconws(": error writing\r\n");
		    Fclose(fd); return;
		}
	    }
	}
    }
    Fclose(fd);
}

#ifdef _USE_TIMER_C_
static unsigned short countdown;
#endif
static short installed = 0;	/* reset to 0 before exit */
static unsigned short *bufr;
static unsigned long maxidx;
static unsigned long off;
static unsigned long shift_val;

static xbra_struct tick_xbra = _XBRA_INIT(tick);
static xbra_struct term_xbra = _XBRA_INIT(term);

extern BASEPAGE *_base;
static BASEPAGE **act_pd;
static BASEPAGE *my_base;

/*
 * profil
 *	record pc every N ms into buffer
 *	index into buffer == (pc - offset) >> shift
 *		(note difference in scaling semantics)
 * 	turned off by shift == 0
 *	ineffective by bufsiz == 0
 *
 *	on the St, we hook into the Timer C interrupt, and record
 *	every 4'th tick (20 ms).
 *	this method was chosen over user Timer A, so that applications
 *	that use the timer can be profiled.
 *	vbl was not considered because we dont have the flexibility
 *	of changing the time resolution, and because its frequency is
 *	screen rez dependent (plus its harder to get at the user pc!)
 *
 *	xbra protocol to hook in/out handlers. we hook into the terminate
 *	vector independent of the rest of the library to make sure we
 *	unhook before process termination. this is also necessary because
 *	the user can call up these routines independent of gcrt0
 */
int profil(buff, bufsiz, offset, shift)
void *buff;
unsigned long bufsiz, offset;
int shift;
{
    if(shift == 0)
    {
	if(installed)
	    remove_handlers();
	installed = 0;
	return 0;
    }
    /* set the params atomically */
    Jdisint(5);
#ifdef _USE_TIMER_C_
    countdown = 4;
#endif
    bufr = (unsigned short *)buff;
    maxidx = bufsiz>>1;	/* max index into short array */
    off = offset;
    shift_val = shift;

    if(!installed)
    {
	installed = 1;
	install_handlers();
    }
    Jenabint(5);
    return 0;
}

#ifdef __MBASE__
#define Countdown __MBASESTR__ "@(_countdown:w)"
#define Off __MBASESTR__ "@(_off:w)"
#define Shift_val __MBASESTR__ "@(_shift_val:w)"
#define Maxidx __MBASESTR__ "@(_maxidx:w)"
#define Bufr __MBASESTR__ "@(_bufr:w)"
#define Tick_xbra __MBASESTR__ "@((_tick_xbra+8):w)"
#else
#define Countdown "_countdown"
#define Off "_off"
#define Shift_val "_shift_val"
#define Maxidx "_maxidx"
#define Bufr "_bufr"
#define Tick_xbra "_tick_xbra+8"
#endif
#ifdef _USE_TIMER_C_
/*
 * tick handler
 *	if countdown = 0, record pc
 */
__asm__ ("\
 	.text; .even
_tick:
 	subqw	#1," Countdown "
 	jne	1f

 	movw	#4," Countdown "
 	moveml	d0-d1/a0,sp@-
 	movl	sp@(14),d0	/* get user pc from exception frame */
 	subl	" Off ",d0
	jcs	2f		/* branch if below */
 	movl	" Shift_val ",d1	/* shift it */
 	lsrl	d1,d0
 	cmpl	" Maxidx ",d0	/* compare with max index */
 	jhi	2f		/* branch if out of range */

 	lsll	#1,d0		/* word index */
	movl	" Bufr ",a0
 	addl	d0,a0		/* incr hist word */
 	addqw	#1,a0@
2:
 	moveml	sp@+,d0-d1/a0
1:
	movl	" Tick_xbra ",sp@-
 	rts ");
#else
/*
 * tick handler
 *	in etv_timer timer handoff vector chain (called every 4th tick)
 *	stack at  this point:
 *	<exception frame user pc, sr>			2
 *	<saved d0-d7/a0-a6>				60
 *	<timer calibration .w>				2
 *	<return address to timer C intr routine>	4
 *							---
 *							68 (offset to user pc)
 */
__asm__ ("\
 	.text; .even
_tick:
 	movl	sp@(68),d0	/* get user pc from exception frame */
 	subl	" Off ",d0
	jcs	1f		/* branch if below */
 	movl	" Shift_val ",d1	/* shift it */
 	lsrl	d1,d0
 	cmpl	" Maxidx ",d0	/* compare with max index */
 	jhi	1f		/* branch if out of range */

 	lsll	#1,d0		/* word index */
	movl	" Bufr ",a0
 	addl	d0,a0		/* incr hist word */
 	addqw	#1,a0@
1:
	movl	" Tick_xbra ",sp@-	/* call next handler in chain */
 	rts ");
#endif

/*
 * terminate vector
 */
static void term()	
{
    /* validate  process id */
    if(_base != *act_pd)
    {
	__asm__ volatile("\
 			unlk	a6
 			jmp	%0@"
			 :
			 : "a"(term_xbra.next));
    }
    if(installed)
	    remove_handlers();
    /* go on to the next guy */
    __asm__ volatile("\
 			unlk	a6
 			jmp	%0@"
			 :
			 : "a"(term_xbra.next));
}

/*
 * install tick and terminate handlers at the head of the xbra chains
 *	coding thanks to edgar roeder
 */
static void  install_handlers()
{
    long	*sysbase;

    sysbase = (long *) mon_get_sysvar((void *) _sysbase);
    switch(sysbase[6])
    {
      case 0x11201985L:
      case 0x02061986L:
      case 0x04241986L:
	act_pd = (BASEPAGE **) 0x602CL;
	break;
      default:
	act_pd = (BASEPAGE **) sysbase[10];
    }

#ifdef _USE_TIMER_C_
    tick_xbra.next = (xptr) Setexc(276>>2, _XBRA_VEC(tick_xbra));
#else
    tick_xbra.next = (xptr) Setexc(0x100, _XBRA_VEC(tick_xbra));
#endif
    term_xbra.next = (xptr) Setexc(0x102, _XBRA_VEC(term_xbra));
    my_base = _base;
}

/*
 * unlink a handler in a xbra friendly manner from the exc chain
 */
static void unlink_handler(me, exc)
xbra_struct *me;
int exc;
{
    xbra_struct *this, *prev;
    long save_ssp;
    
    this = (xbra_struct *)	/* get head of chain */
	((unsigned long)Setexc(exc, -1L) - offsetof(xbra_struct, jump));
    if(this == me)
    {	/* at the head, just unlink */
	(void)Setexc(exc, me->next);
	return;
    }
    /* otherwise find me in the chain and unlink */
    save_ssp = Super(0L);
    for(prev = this; this && (this != me); prev = this,
        this = (xbra_struct *)((this->next)
	     ? (((char *)(this->next)) - offsetof(xbra_struct, jump)) : 0))
    {
	/* validate the xbra */
	if(this->xbra_magic != _XBRA_MAGIC) 
	{	/* shame on you */
	    Super(save_ssp);
	    (void)Setexc(exc, me->next); /* nuke it, otherwise it may call ME */
	    return;		   /* after i am deinstalled */
	}
    }
    
    if(this == me)
    { 	/* unlink me from middle of the chain */
	prev->next = this->next;
	Super(save_ssp);
	return;
    }
    /* we are screwed */
    Super(save_ssp);
    Cconws("\r\nwhat the fuck!\r\n\n");
}


static void remove_handlers()
{
    /* first validate pid */
    if(_base == *act_pd)
    {
	if(_base != my_base)	/* in vfork()ed parallel addr space */
	    _base -= 2;
	else
	{
	    /* do i need to Super and raise IPL here ?? */

#ifdef _USE_TIMER_C_
	    unlink_handler(&tick_xbra, 276>>2);
#else
	    unlink_handler(&tick_xbra, 0x100);
#endif
	    unlink_handler(&term_xbra, 0x102);
	    installed = 0;
	}
    }
}

