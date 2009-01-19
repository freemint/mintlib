/* This implements the wc* and mb* ANSI/ISO functions.
   They're in the "DUMB" locale ;), and in the public domain.
*/

#include <stdlib.h>
#include <stddef.h>

extern const wchar_t *_wnull;

int
mblen(mbstr, n)
const char *mbstr;
size_t n;
{
	/* Locale test: no shift states. */
	if(mbstr == NULL || *mbstr == '\0') return 0;
	
	if(n == 0) return -1;
	
	/* There are no multibytesequences... */
	return 1;
}

size_t
mbstowcs(wstr, mbstr, maxlen)
wchar_t *wstr;
const char *mbstr;
size_t maxlen;
{
	size_t revcnt = maxlen;
	
	if(mbstr == NULL) mbstr = "";
	
	while(revcnt && ((*wstr++ = *mbstr++) != 0)) revcnt--;
	
	return maxlen - revcnt;
}

int
mbtowc(wstr, mbstr, n)
wchar_t *wstr;
const char *mbstr;
size_t n;
{
	/* Locale test: no shift states. */
	if(mbstr == NULL) return 0;
	
	if(n == 0) return -1;
	
	if(wstr) *wstr = *mbstr;

	return (*mbstr != '\0');
}


size_t
wcstombs(mbstr, wstr, maxlen)
char *mbstr;
const wchar_t *wstr;
size_t maxlen;
{
	size_t revcnt = maxlen;
	
	if(wstr == NULL) wstr = _wnull; /* Better avoid L"". */
	
	while(revcnt && ((*mbstr++ = (char) *wstr++) != 0)) revcnt--;
	
	return maxlen - revcnt;
}

int
wctomb(mbstr, wchar)
char *mbstr;
wchar_t wchar;
{
	/* Nope, still no statedependencies. */
	if(mbstr == NULL) return 0;
	
	*mbstr = (char) wchar;
	return 1;
}
