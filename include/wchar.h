#ifndef _WCHAR_H
#define _WCHAR_H

/* Get size_t, wchar_t, wint_t and NULL from <stddef.h>.  */
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_wint_t
#include <stddef.h>

#ifndef WEOF
# define WEOF (0xffffffffu)
#endif

typedef struct
{
	unsigned __opaque1, __opaque2;
} mbstate_t;

wchar_t *wcscpy (wchar_t *, const wchar_t *);
wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t);

wchar_t *wcscat (wchar_t *, const wchar_t *);
wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t);

int wcscmp (const wchar_t *, const wchar_t *);
int wcsncmp (const wchar_t *, const wchar_t *, size_t);

wchar_t *wcschr (const wchar_t *, wchar_t);
wchar_t *wcsrchr (const wchar_t *, wchar_t);

size_t wcscspn (const wchar_t *, const wchar_t *);
size_t wcsspn (const wchar_t *, const wchar_t *);

wchar_t *wcstok (wchar_t *, const wchar_t *, wchar_t **);

size_t wcslen (const wchar_t *);

wchar_t *wcsstr (const wchar_t *, const wchar_t *);

int mbsinit (const mbstate_t *);
size_t mbrtowc (wchar_t *, const char *, size_t, mbstate_t *);
size_t wcrtomb (char *, wchar_t, mbstate_t *);

size_t mbrlen (const char *, size_t, mbstate_t *);

size_t mbsrtowcs (wchar_t *, const char **, size_t, mbstate_t *);
size_t wcsrtombs (char *, const wchar_t **, size_t, mbstate_t *);

#endif /* _WCHAR_H */
