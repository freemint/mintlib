/*
 * function form of linea bindings
 *	++jrb
 */

#define __NO_INLINE__
#include <mint/linea.h>

void linea0()                                                   
{
        register __LINEA *__xaline __asm__ ("a0");
        register __FONT **__xfonts __asm__ ("a1");
        register short (**__xfuncs) (void) __asm__ ("a2");

        __asm__ volatile
        (
		".word	0xA000"
        : "=g"(__xaline), "=g"(__xfonts), "=g"(__xfuncs)  /* outputs */
        :                                                 /* inputs  */
        : __CLOBBER_RETURN("a0") __CLOBBER_RETURN("a1") __CLOBBER_RETURN("a2") "d0", "d1", "d2"       /* clobbered regs */
        );

        __aline = __xaline;
        __fonts = __xfonts;
        __funcs = __xfuncs;
}

void linea1() 							
{									
	__asm__ volatile
	(
		".word	0xA001"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

int linea2() 							
{									
	register long retvalue __asm__("d0");

	__asm__ volatile						
	(
		".word	0xA002"
	: "=r"(retvalue)				  /* outputs */	
	: 						  /* inputs  */	
	: __CLOBBER_RETURN("d0") "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								

	return (int) retvalue;
}

void linea3() 							
{									
	__asm__ volatile						
	(
		".word	0xA003"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void linea4() 							
{									
	__asm__ volatile						
	(
		".word	0xA004"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void linea5() 							
{									
	__asm__ volatile						
	(
		".word	0xA005"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void linea6() 							
{									
	__asm__ volatile						
	(
		".word	0xA006"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void linea7(BBPB *P) 							
{									
	__asm__ volatile						
	(
		"movml	d2/a2/a6, sp@-\n\t"
 		"movl	%0,a6\n\t"
		".word	0xA007\n\t"
		"movml	sp@+, d2/a2/a6"
	: 						  /* outputs */	
	: "r"(P)					  /* inputs  */	
	: "d0", "d1", "a0", "a1"		   /* clobbered regs */
	);								
}

void linea8() 							
{									
	__asm__ volatile						
	(
		".word	0xA008"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void linea9() 							
{									
	__asm__ volatile						
	(
		".word	0xA009"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void lineaa() 							
{
	__asm__ volatile						
	(
		".word	0xA00A"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void lineab() 							
{									
	__asm__ volatile						
	(
		".word	0xA00B"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void lineac(void *P) 							
{									
	__asm__ volatile						
	(
 		"movl	%0,a2\n\t"
		".word	0xA00C"
	: 						  /* outputs */	
	: "r"(P)					  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"              /* clobbered regs */	
	);								
}

void linead(int x, int y,  SFORM * sd, void *ss)
{									
	__asm__ volatile						
	(
 		"movw	%0,d0\n\t"
 		"movw	%1,d1\n\t"
 		"movl	%2,a0\n\t"
 		"movl	%3,a2\n\t"
		".word	0xA00D"
	: 						  /* outputs */	
	: "r"((short)x), "r"((short)y), "r"(sd), "r"(ss)  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"              /* clobbered regs */	
	);								
}

void lineae() 							
{									
	__asm__ volatile						
	(
		".word	0xA00E"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}

void lineaf() 							
{									
	__asm__ volatile						
	(
		".word	0xA00F"
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	);								
}
