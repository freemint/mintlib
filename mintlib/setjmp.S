|
| setjmp.S
|

	.globl ___mint

	.text
	.even
	.globl _sigsetjmp
_sigsetjmp:
	movel	sp@(4), a0		| address of sigjmp_buf[]
#ifdef __MSHORT__
	movew	sp@(8), a1
#else
	movel	sp@(8), a1
#endif
	movel	a1, a0@(52)		| save sigmask for siglongjmp?
	jeq	SETJMP			| no -- call common code
	movel	__sigmask, d0		| save tos emulation signal mask
#ifdef __MSHORT__
	tstw	___mint			| see if MiNT is active
#else
	tstl	___mint
#endif
	jeq	nomint			| no -- call common code
	
	movel	a0, sp@-		| save register a0
	
	clrl	sp@-			| add no signals to sigmask
	movew	#0x116, sp@-		| Psigblock() system call
	trap	#1			|
	addql	#6, sp
	
	movel	sp@+, a0		| restore register a0
	
nomint:
#ifdef __mcoldfire__
	orl	#1,d0			| make it != 0 (SIGNULL is unmaskable)
#else
	orw	#1,d0			| make it != 0 (SIGNULL is unmaskable)
#endif
	movel	d0, a0@(52)		| save signal mask
	jra	SETJMP			| call common code

	.globl _setjmp
_setjmp:
	movel	sp@(4),a0		| address of jmp_buf[]
	clrl	a0@(52)			| do not restore sigmask on longjmp
SETJMP:
	movel	sp@,a0@			| save return address
	moveml	d2-d7/a2-a7,a0@(4)	| save registers d2-d7/a2-a7
	clrl	d0			| return value is 0
	rts

	.globl _siglongjmp
_siglongjmp:
	.globl _longjmp
_longjmp:
#ifdef __MSHORT__
	tstw	___mint			| see if MiNT is active
#else
	tstl	___mint
#endif
	jeq	NOMINT			| no -- do not call sigreturn
	movew	#0x11a, sp@-		| Psigreturn() system call
	trap	#1			| (ignored if not in a sig handler)
	addql	#2, sp
NOMINT:
	movel	sp@(4),a0		| address of jmp_buf[]
	movel	a0@(52),d0		| want to restore sigmask?
	jeq	NORESTORE		| no -- skip restore code
#ifdef __mcoldfire__
	andl	#-2,d0
#else
	andw	#-2,d0
#endif
	movel	d0, __sigmask		| restore tos emulation signal mask
#ifdef __MSHORT__
	tstw	___mint			| see if MiNT is active
#else
	tstl	___mint
#endif
	jeq	NORESTORE		| no -- do not call sigsetmask
	
	movel	a0, sp@-		| save register a0
	
	movel	d0, sp@-		| restore signal mask
	movew	#0x117, sp@-		| Psigsetmask() system call
	trap	#1			|
	addql	#6, sp
	
	movel	sp@+, a0		| restore register a0
	
NORESTORE:
#ifdef __MSHORT__
	movew	sp@(8),d0		| value to return
#else
	movel	sp@(8),d0		| value to return
#endif
	jne	L1			| may not be 0
	movql	#1, d0
L1:
	moveml	a0@(4),d2-d7/a2-a7	| restore saved reggies
	movl	a0@,sp@			| and the saved return address
	rts
