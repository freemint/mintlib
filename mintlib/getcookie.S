| getcookie.S -- MiNTLib.
|
| This file is part of the MiNTLib project, and may only be used
| modified and distributed under the terms of the MiNTLib project
| license, COPYMINT.  By continuing to use, modify, or distribute
| this file you indicate that you have read the license and
| understand and accept it fully.

| int Getcookie(long cookie, long *p_value);
|
| Get the value of a system Cookie.
|
| WARNING: This function is called from the startup code before knowing the
| actual CPU type. So it must be compatible with any processor (including
| 680x0 and ColdFire models). So it must be written carefully by using only
| instructions common to all of the supported processors. Especially, gas
| pseudo-jump instructions must be avoided (jbsr, jbra...), because they may
| be translated to unsupported jump instructions.

#include "libc-symbols.h"

	.extern	C_SYMBOL_NAME(__has_no_ssystem)	| int __has_no_ssystem;
	.extern	C_SYMBOL_NAME(get_sysvar)		| long get_sysvar(const volatile void *var);

	.globl	C_SYMBOL_NAME(Getcookie)
C_SYMBOL_NAME(Getcookie):
	lea	%sp@(-16),%sp
	movml	%d2/%d3/%a2/%a3,%sp@		| ColdFire compatibility

#ifdef __FASTCALL__
	movel	%d0,%d3		| cookie
	movel	%a0,%a3		| p_value
#else
	movel	%sp@(16+4),%d3		| cookie
	movel	%sp@(16+8),%a3		| p_value
#endif

	tstl	C_SYMBOL_NAME(__has_no_ssystem)
	beqs	.get_with_ssystem

#ifdef __FASTCALL__
	movew	#0x5a0,%a0			| _p_cookies
	jsr	C_SYMBOL_NAME(get_sysvar)
#else
	pea	0x5a0			| _p_cookies
	jsr	C_SYMBOL_NAME(get_sysvar)
	addql	#4,%sp
#endif

	tstl	%d0
	beqs	.error			| No cookie jar

	movl	%d0,%a0

.nextcookie:
	tstl	%a0@
	beqs	.error			| End of Cookie Jar

	movel	%a0@+,%d0			| Cookie name
	movel	%a0@+,%d1			| Cookie value

	cmpl	%d3,%d0			| Right cookie ?
	bnes	.nextcookie

	moveq	#0,%d0			| E_OK

.return:
	cmpl	#0,%a3
	beqs	.restore		| p_value == NULL

	movl	%d1,%a3@			| *p_value = value;

.restore:
	movml	%sp@,%d2/%d3/%a2/%a3		| ColdFire compatibility
	lea	%sp@(16),%sp
	rts

.error:
	moveq	#-1,%d0			| EERROR
	moveq	#0,%d1			| Cookie value

	bras	.return

.get_with_ssystem:
	pea	-42			| Local variable for cookie value

	pea	%sp@			| Pointer to the output variable
	movl	%d3,%sp@-			| cookie
	movew	#8,%sp@-			| S_GETCOOKIE
	movew	#0x154,%sp@-		| Ssystem()
	trap	#1
	lea	%sp@(12),%sp

	movel	%sp@+,%d1			| Cookie value

	cmpl	#-1,%d0
	beqs	.error			| Fail

	| Backward compatibility for MiNT 1.14.7:
	| Ssystem() returns cookie value and ignores arg2!!
	cmpl	#-42,%d1
	bnes	.return

	movl	%d0,%d1			| Get value from return value

	bras	.return

#include "elfattr.S"
