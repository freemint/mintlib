/*
 * Routines for handling the local environment.
 * WARNING: This probably isn't in accord with the pANS standard yet.
 *
 * Written by Eric R. Smith and placed in the public domain.
 *
 */

#include <stddef.h>
#include <string.h>
#include <locale.h>

static char *C_mth_name[] =
{ "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

static char *C_day_name[] =
{
"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

static struct lconv C_locale = {
        ".",    /* decimal point for ordinary numbers */
        ",",    /* thousands separator */
        "",      /* how digits in ordinary numbers are grouped */
        "$",    /* international currency symbol */
        "$",    /* currency symbol for ordinary use */
        ".",    /* decimal point for money */
        ",",    /* thousands separator for money */
        "",      /* how digits in a monetary value are grouped */
        "",     /* symbol for positive amount of money */
        "-",    /* symbol for negative amount of money */
        4,      /* International: number of places after '.' for money*/
        2,      /* local: number of places after '.' for money */
        1,      /* currency symbol 1 precedes 0 succeeds positive value */
        1,      /* 1=space 0=no space between currency symbol and pos. value */
        1,      /* currency symbol 1 precedes 0 succeeds neg. value */
        0,      /* 1=space 0=no space between currency symbol and neg. value */
        1,      /* position of sign in postive money values (???) */
        1       /* position of sign in negative money values (???) */
};

/* current locale info */
static struct lconv _LC_Curlocale;

/* time names for current locale: used by strftime.c */
char **_LC_Mth_name = C_mth_name;
char **_LC_Day_name = C_day_name;

/* localeconv: return current locale information */

struct lconv *localeconv()
{
  _LC_Curlocale = C_locale;
  return &_LC_Curlocale;
}
