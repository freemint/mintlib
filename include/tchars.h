/*
 *		Cross Development System for Atari ST 
 *     Copyright (c) 1988, Memorial University of Newfoundland
 *
 *  The TC defines are indices into the __tchars array.
 *
 */
#ifndef _TCHARS_H
#define _TCHARS_H

#ifdef __cplusplus
extern "C" {
#endif

#define	TC_ERASE	0
#define	TC_KILL		1
#define	TC_INTRC	2
#define	TC_QUITC	3
#define	TC_EOFC		4
#define	TC_BRKC		5
#define	TC_RPRNTC	6
#define	TC_WERASC	7
#define	TC_LNEXTC	8
#define TC_RUBOUT	9
#define TC_SUSPC	10
#define TC_DSUSPC	11
#define TC_FLUSHC	12
#define TC_STARTC	13
#define TC_STOPC	14
#define	TC_UNDEF	-1

#if 0 /* for now */
typedef struct {
	unsigned char	*unshift;
	unsigned char	*shift;
	unsigned char	*capslock;
} KEYTAB;
#endif

#if 0 /* for now */
extern	long	*_ttymode;
extern	char	__tchars_defaults[];
extern	KEYTAB	*__keytab;
#else
extern	int	__ttymode;
extern	char	__tchars[];
#endif

#ifdef __cplusplus
}
#endif

#endif /* _TCHARS_H */
