/*
 * locale.h (ansi draft sec 4.4)
 *      not implemented
 */

#ifndef _LOCALE_H
# define _LOCALE_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

/* Get NULL from <stddef.h>.  */
#define	__need_NULL
#include <stddef.h>

#define LC_ALL          0x003F
#define LC_COLLATE      0x0001
#define LC_CTYPE        0x0002
#define LC_MONETARY     0x0004
#define LC_NUMERIC      0x0008
#define LC_TIME         0x0010
#define LC_MESSAGES	0x0020

struct lconv {
        char    *decimal_point;
        char    *thousands_sep;
        char    *grouping;
        char    *int_curr_symbol;
        char    *currency_symbol;
        char    *mon_decimal_point;
        char    *mon_thousands_sep;
        char    *mon_grouping;
        char    *positive_sign;
        char    *negative_sign;
        char    int_frac_digits;
        char    frac_digits;
        char    p_cs_precedes;
        char    p_sep_by_space;
        char    n_cs_precedes;
        char    n_sep_by_space;
        char    p_sign_posn;
        char    n_sign_posn;
};

extern char *setlocale (int category, const char *locale) __THROW;
/* default is supposed to be setlocale(LC_ALL, "C") */

extern struct lconv *localeconv (void) __THROW;

__END_DECLS

#endif /* _LOCALE_H */
