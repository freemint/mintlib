|
| setjmp.S
|

#include "libc-symbols.h"

	.globl C_SYMBOL_NAME(__mint)

	.text
	.even
	.globl C_SYMBOL_NAME(sigsetjmp)
C_SYMBOL_NAME(sigsetjmp):
#ifdef __FASTCALL__
	movew	%d0,%a1
#else
	movel	4(%sp), %a0		| address of sigjmp_buf[]
#ifdef __MSHORT__
	movew	8(%sp), %a1
#else
	movel	8(%sp), %a1
#endif
#endif
	movel	%a1, 52(%a0)		| save sigmask for siglongjmp?
	jeq	SETJMP			| no -- call common code
	movel	C_SYMBOL_NAME(_sigmask), %d0		| save tos emulation signal mask
#ifdef __MSHORT__
	tstw	C_SYMBOL_NAME(__mint)			| see if MiNT is active
#else
	tstl	C_SYMBOL_NAME(__mint)
#endif
	jeq	nomint			| no -- call common code
	
	movel	%a0, -(%sp)		| save register a0
	
	clrl	-(%sp)			| add no signals to sigmask
	movew	#0x116, -(%sp)		| Psigblock() system call
	trap	#1			|
	addql	#6, %sp
	
	movel	(%sp)+, %a0		| restore register a0
	
nomint:
	bset	#0,%d0			| make it != 0 (SIGNULL is unmaskable)
	movel	%d0, 52(%a0)		| save signal mask
	jra	SETJMP			| call common code

	.globl C_SYMBOL_NAME(setjmp)
C_SYMBOL_NAME(setjmp):
#ifndef __FASTCALL__
	movel	4(%sp),%a0		| address of jmp_buf[]
#endif
	clrl	52(%a0)			| do not restore sigmask on longjmp
SETJMP:
	movel	(%sp),(%a0)			| save return address
	moveml	%d2-%d7/%a2-%a7,4(%a0)	| save registers d2-d7/a2-a7
	clrl	%d0			| return value is 0
	rts

	.globl C_SYMBOL_NAME(siglongjmp)
C_SYMBOL_NAME(siglongjmp):
	.globl C_SYMBOL_NAME(longjmp)
C_SYMBOL_NAME(longjmp):
#ifndef __FASTCALL__
	movel	4(%sp),%a0		| address of jmp_buf[]
#else
	movew	%d0,-(%sp)		| save register d0
#endif
#ifdef __MSHORT__
	tstw	C_SYMBOL_NAME(__mint)			| see if MiNT is active
#else
	tstl	C_SYMBOL_NAME(__mint)
#endif
	jeq	NOMINT			| no -- do not call sigreturn
	movel	%a0,-(%sp)	| save register a0
	movew	#0x11a, -(%sp)		| Psigreturn() system call
	trap	#1			| (ignored if not in a sig handler)
	addql	#2, %sp
	movel	(%sp)+,%a0	| restore register a0
NOMINT:
	movel	52(%a0),%d0		| want to restore sigmask?
	jeq	NORESTORE		| no -- skip restore code
#ifdef __mcoldfire__
	andl	#-2,%d0
#else
	andw	#-2,%d0
#endif
	movel	%d0, C_SYMBOL_NAME(_sigmask)		| restore tos emulation signal mask
#ifdef __MSHORT__
	tstw	C_SYMBOL_NAME(__mint)			| see if MiNT is active
#else
	tstl	C_SYMBOL_NAME(__mint)
#endif
	jeq	NORESTORE		| no -- do not call sigsetmask
	
	movel	%a0, -(%sp)		| save register a0
	
	movel	%d0, -(%sp)		| restore signal mask
	movew	#0x117, -(%sp)		| Psigsetmask() system call
	trap	#1			|
	addql	#6, %sp
	
	movel	(%sp)+, %a0		| restore register a0
	
NORESTORE:
#ifdef __FASTCALL__
	movew	(%sp)+,%d0		| restore register d0
#else
#ifdef __MSHORT__
	movew	8(%sp),%d0		| value to return
#else
	movel	8(%sp),%d0		| value to return
#endif
#endif
	jne	L1			| may not be 0
	movql	#1, %d0
L1:
	moveml	4(%a0),%d2-%d7/%a2-%a7	| restore saved reggies
	movl	(%a0),(%sp)			| and the saved return address
	rts

#include "elfattr.S"
