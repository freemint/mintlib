
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>
#include <string.h>

static unsigned char table[] = {
#include "alpha.h"
};

static unsigned char punct_table[] = {
#include "punct.h"
};


int iswalnum(wint_t wc)
{
	return iswdigit(wc) || iswalpha(wc);
}

int iswalpha(wint_t wc)
{
	if (wc<0x20000U)
		return (table[table[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1;
	if (wc<0x2fffeU)
		return 1;
	return 0;
}

int iswblank(wint_t wc)
{
	return isblank(wc);
}

int iswcntrl(wint_t wc)
{
	return (unsigned)wc < 32
	    || (unsigned)(wc-0x7f) < 33
	    || (unsigned)(wc-0x2028) < 2
	    || (unsigned)(wc-0xfff9) < 3;
}

#undef iswdigit
int iswdigit(wint_t wc)
{
	return (unsigned)wc-'0' < 10;
}

int iswgraph(wint_t wc)
{
	/* ISO C defines this function as: */
	return !iswspace(wc) && iswprint(wc);
}

int iswlower(wint_t wc)
{
	return towupper(wc) != wc || wc == 0xdf;
}

int iswprint(wint_t wc)
{
	if (wc < 0xffU)
		return ((wc+1) & 0x7f) >= 0x21;
	if (wc < 0x2028U || wc-0x202aU < 0xd800-0x202a || wc-0xe000U < 0xfff9-0xe000)
		return 1;
	if (wc-0xfffcU > 0x10ffff-0xfffc || (wc&0xfffe)==0xfffe)
		return 0;
	return 1;
}

int iswpunct(wint_t wc)
{
	if (wc<0x20000U)
		return (punct_table[punct_table[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1;
	return 0;
}

int iswspace(wint_t wc)
{
	static const wchar_t spaces[] = {
		' ', '\t', '\n', '\r', 11, 12,  0x0085,
		0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005,
		0x2006, 0x2008, 0x2009, 0x200a,
		0x2028, 0x2029, 0x205f, 0x3000, 0
	};
	if (wcschr(spaces, wc)) return 1;
	return 0;
}

int iswupper(wint_t wc)
{
	return towlower(wc) != wc;
}

int iswxdigit(wint_t wc)
{
	return (unsigned)(wc-'0') < 10 || (unsigned)((wc|32)-'a') < 6;
}

#define WCTYPE_ALNUM  1
#define WCTYPE_ALPHA  2
#define WCTYPE_BLANK  3
#define WCTYPE_CNTRL  4
#define WCTYPE_DIGIT  5
#define WCTYPE_GRAPH  6
#define WCTYPE_LOWER  7
#define WCTYPE_PRINT  8
#define WCTYPE_PUNCT  9
#define WCTYPE_SPACE  10
#define WCTYPE_UPPER  11
#define WCTYPE_XDIGIT 12

int iswctype(wint_t wc, wctype_t type)
{
	switch (type) {
	case WCTYPE_ALNUM:
		return iswalnum(wc);
	case WCTYPE_ALPHA:
		return iswalpha(wc);
	case WCTYPE_BLANK:
		return iswblank(wc);
	case WCTYPE_CNTRL:
		return iswcntrl(wc);
	case WCTYPE_DIGIT:
		return iswdigit(wc);
	case WCTYPE_GRAPH:
		return iswgraph(wc);
	case WCTYPE_LOWER:
		return iswlower(wc);
	case WCTYPE_PRINT:
		return iswprint(wc);
	case WCTYPE_PUNCT:
		return iswpunct(wc);
	case WCTYPE_SPACE:
		return iswspace(wc);
	case WCTYPE_UPPER:
		return iswupper(wc);
	case WCTYPE_XDIGIT:
		return iswxdigit(wc);
	}
	return 0;
}

wctype_t wctype(const char *s)
{
	int i;
	const char *p;
	/* order must match! */
	static const char names[] =
		"alnum\0" "alpha\0" "blank\0"
		"cntrl\0" "digit\0" "graph\0"
		"lower\0" "print\0" "punct\0"
		"space\0" "upper\0" "xdigit";
	for (i=1, p=names; *p; i++, p+=6)
		if (*s == *p && !strcmp(s, p))
			return i;
	return 0;
}
