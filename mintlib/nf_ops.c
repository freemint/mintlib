#include <stdarg.h>
#include <stdio.h>
#include <mint/arch/nf_ops.h>
#include <mint/cookie.h>
#include <mint/osbind.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>

#ifndef __mint_sighandler_t_defined
#define __mint_sighandler_t_defined 1
#ifdef __NO_CDECL
typedef void *__mint_sighandler_t;
#else
typedef void __CDECL (*__mint_sighandler_t) (long signum);
#endif
#endif

#ifndef UNUSED
# define UNUSED(x) ((void)(x))
#endif

#ifndef FALSE
#define FALSE   0
#define TRUE    1
#endif

#ifndef __MINT_SIGSYS
#define __MINT_SIGILL		4		/* illegal instruction */
#define __MINT_SIGSYS		12		/* bad system call */
#endif

/*** ---------------------------------------------------------------------- ***/

static int sigsys;

static void __CDECL sigsys_handler(long sig)
{
	UNUSED(sig);
	sigsys = 1;
}

void nf_catch_sigsys(void)
{
	sigsys = 0;
	(void)Psignal(__MINT_SIGSYS, sigsys_handler);
}

/*** ---------------------------------------------------------------------- ***/

#define NATFEAT_ID   0x7300
#define NATFEAT_CALL 0x7301

#pragma GCC optimize "-fomit-frame-pointer"
#pragma GCC diagnostic ignored "-Wclobbered"

#define ASM_NATFEAT3(opcode) "\t.word " #opcode "\n"
#define ASM_NATFEAT2(opcode) ASM_NATFEAT3(opcode)
#define ASM_NATFEAT(n) ASM_NATFEAT2(n)

static long __attribute__((noinline)) __CDECL _nf_get_id(const char *feature_name)
{
	register long ret __asm__ ("d0");
	UNUSED(feature_name);
	__asm__ volatile(
		ASM_NATFEAT(NATFEAT_ID)
	: "=g"(ret)  /* outputs */
	: /* inputs  */
	: __CLOBBER_RETURN("d0") "d1", "cc" AND_MEMORY /* clobbered regs */
	);
	return ret;
}


static long __attribute__((noinline)) __CDECL _nf_call(long id, ...)
{
	register long ret __asm__ ("d0");
	UNUSED(id);
	__asm__ volatile(
		ASM_NATFEAT(NATFEAT_CALL)
	: "=g"(ret)  /* outputs */
	: /* inputs  */
	: __CLOBBER_RETURN("d0") "d1", "cc" AND_MEMORY /* clobbered regs */
	);
	return ret;
}


/*
 * on ColdFire, the NATFEAT_ID opcode is actually
 * "mvs.b d0,d1",
 * which means the following code will NOT detect
 * the presence of an emulator (should there ever
 * be an emulator capable of emulating a ColdFire processor).
 * Luckily, executing the code on a CF processor is still
 * harmless since all it does is clobber D1.
 */
static long _nf_detect_tos(void)
{
	register long ret __asm__ ("d0");
	register const char *nf_version_id __asm__("a1") = NF_ID_VERSION;
	
	__asm__ volatile(
	"\tmove.l	%1,-(%%sp)\n"
	"\tmoveq	#0,%%d0\n"			/* assume no NatFeats available */
	"\tmove.l	%%d0,-(%%sp)\n"
	"\tlea		(1f:w,%%pc),%%a1\n"
	"\tmove.l	(0x0010).w,%%a0\n"	/* illegal instruction vector */
	"\tmove.l	%%a1,(0x0010).w\n"
	"\tmove.l	%%sp,%%a1\n"		/* save the ssp */

	"\tnop\n"						/* flush pipelines (for 68040+) */

	ASM_NATFEAT(NATFEAT_ID)			/* Jump to NATFEAT_ID */
	"\ttst.l	%%d0\n"
	"\tbeq.s	1f\n"
	"\tmoveq	#1,%%d0\n"			/* NatFeats detected */
	"\tmove.l	%%d0,(%%sp)\n"

"1:\n"
	"\tmove.l	%%a1,%%sp\n"
	"\tmove.l	%%a0,(0x0010).w\n"
	"\tmove.l	(%%sp)+,%%d0\n"
	"\taddq.l	#4,%%sp\n"			/* pop nf_version argument */

	"\tnop\n"						/* flush pipelines (for 68040+) */
	: "=g"(ret)  /* outputs */
	: "g"(nf_version_id)		/* inputs  */
	: __CLOBBER_RETURN("d0") "a0", "d1", "cc" AND_MEMORY
	);
	return ret;
}

static void _nf_detect_mint(void)
{
	register const char *nf_version_id = NF_ID_VERSION;
	
	__asm__ volatile(
	"\tmove.l	%0,-(%%sp)\n"
	"\tmoveq	#0,%%d0\n"			/* assume no NatFeats available */
	"\tmove.l	%%d0,-(%%sp)\n"
	ASM_NATFEAT(NATFEAT_ID)			/* Jump to NATFEAT_ID */
	"\taddq.l	#8,%%sp\n"			/* pop nf_version argument */
	"\tnop\n"						/* flush pipelines (for 68040+) */
	:  /* outputs */
	: "g"(nf_version_id)		/* inputs  */
	: __CLOBBER_RETURN("d0") "a0", "d1", "cc" AND_MEMORY
	);
}


static struct nf_ops _nf_ops = { _nf_get_id, _nf_call, { 0, 0, 0 } };
static struct nf_ops *nf_ops;

/* NatFeat code */
typedef struct {
	long magic;
	long __CDECL(*nfGetID) (const char *);
	long __CDECL(*nfCall) (long ID, ...);
} NatFeatCookie;

static int _nf_detect_cookie(void)
{
	NatFeatCookie *nf_ptr = NULL;

	if (Getcookie(C___NF, (long *)&nf_ptr) != C_FOUND ||		/* "__NF" */
		nf_ptr == NULL)
	{
		return FALSE;
	}

	if (nf_ptr->magic != 0x20021021L)		/* NatFeat magic constant */
	{
		return FALSE;
	}
	_nf_ops.get_id = nf_ptr->nfGetID;
	_nf_ops.call = nf_ptr->nfCall;
	return TRUE;
}


static jmp_buf ill_jmp;
static void __CDECL catch_ill(long sig)
{
	(void) sig;
	Psigreturn();
	longjmp(ill_jmp, 1);
}


struct nf_ops *nf_init(void)
{
	long ret;
	int got_ill;
	
	/*
	 * The __NF cookie is deprecated, but there is currently
	 * no standard defined what to do e.g. on ColdFire, where the
	 * NF opcodes are not illegal, and the detection would fail.
	 * So there is currently no choice but to check for the cookie,
	 * until we find a better solution.
	 */
	if (nf_ops == NULL)
	{
		if (_nf_detect_cookie())
			nf_ops = &_nf_ops;
		nf_catch_sigsys();
		ret = Supexec(_nf_detect_tos);
		if (ret == 1)
		{
			nf_ops = &_nf_ops;
		} else if (ret == -38) /* EPERM */
		{
			if ((ret = (long)Psignal(__MINT_SIGILL, catch_ill)) != -32L)
			{
				if ((got_ill = setjmp(ill_jmp)) == 0)
					_nf_detect_mint();
				(void)Psignal(__MINT_SIGILL, (__mint_sighandler_t)ret);
				if (got_ill == 0)
					nf_ops = &_nf_ops;
			}
		}
	}
	return nf_ops;
}


long nf_get_id(const char *feature_name)
{
	struct nf_ops *ops;
	long id = 0;
	
	if ((ops = nf_init()) != NULL)
	{
		id = NF_GET_ID(ops, feature_name);
	}
	return id;
}
