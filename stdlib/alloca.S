| 
|  alloca(nbytes) allocate junk in stack frame
|
|  void *alloca(size_t size)
| 

#include <libc-symbols.h>

	.text
 	.even

	.globl	___alloca
	weak_alias (__alloca, alloca)
	
___alloca:
	movel	sp@+,a0		| get return addr
#ifndef __SOZOBON__
	movel	sp@+,d0		| get size -- assist in bug fix, add 4 to sp
#else
	clrl	d0		| this size_t thing is getting to be
	movew	sp@+,d0		|  an annoyance...  -- sb
#endif

	addql	#1,d0		| ensure address even
	bclr	#0,d0		| lop off odd bit

	subl	d0,sp		| increase stack frame size by that much
	movel	sp,d0		| set up to return it

#ifndef __SOZOBON__
	lea	sp@(-4),sp	| new top of stack (real bug fix here)
#else
	lea	sp@(-2),sp	| hope this is correct...  -- sb
#endif

	jmp	a0@		| return by jmping via saved addr
