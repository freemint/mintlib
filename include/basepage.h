/*
 *	BASEPAGE.H	Definition of the basepage structure
 */

#ifndef _BASEP_H
#define	_BASEP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct basep {
    char	*p_lowtpa;	/* pointer to self (bottom of TPA) */
    char	*p_hitpa;	/* pointer to top of TPA + 1 */
    char	*p_tbase;	/* base of text segment */
    long	p_tlen;		/* length of text segment */
    char	*p_dbase;	/* base of data segment */
    long	p_dlen;		/* length of data segment */
    char	*p_bbase;	/* base of BSS segment */
    long	p_blen;		/* length of BSS segment */
    char	*p_dta;		/* (UNOFFICIAL, DON'T USE) */
    struct basep *p_parent;	/* pointer to parent's basepage */
    char	*p_reserved;	/* reserved for future use */
    char	*p_env;		/* pointer to environment string */
#if 0
/* none of these are documented by Atari. If you try to use them under MiNT,
 * MiNT will laugh at you. So will I.
 */
    char	devx[6];	/* real handles of the standard devices */
    char	res2;		/* reserved */
    char	defdrv;		/* default drv */
#else
    char	p_junk[8];
#endif
    long	p_undef[18];	/* scratch area... don't touch */
    char	p_cmdlin[128];	/* command line image */
} BASEPAGE;

extern	BASEPAGE	*_base;

#ifdef __cplusplus
}
#endif

#endif /* _BASEP_H */
