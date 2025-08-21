#ifndef _WCHAR_H
#define _WCHAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#ifndef __MINT__
#define __need_FILE
#define __need___va_list
#endif
#define __need_NULL
#define __need_size_t
#define __need_wchar_t
#define __need_wint_t

#ifndef __MINT__
#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE)
#define __need_locale_t
#endif
#endif

#include <stddef.h>

#ifndef WEOF
# define WEOF (0xffffffffu)
#endif

typedef struct
{
  long __count;
  union
  {
    unsigned long __wch;
    char __wchb[4];
  } __value;		/* Value so far.  */
} mbstate_t;

wchar_t *wcscpy (wchar_t *__restrict, const wchar_t *__restrict);
wchar_t *wcsncpy (wchar_t *__restrict, const wchar_t *__restrict, size_t);

wchar_t *wcscat (wchar_t *__restrict, const wchar_t *__restrict);
wchar_t *wcsncat (wchar_t *__restrict, const wchar_t *__restrict, size_t);

int wcscmp (const wchar_t *, const wchar_t *);
int wcsncmp (const wchar_t *, const wchar_t *, size_t);

int wcscoll(const wchar_t *, const wchar_t *);
size_t wcsxfrm (wchar_t *__restrict, const wchar_t *__restrict, size_t n);

wchar_t *wcschr (const wchar_t *, wchar_t);
wchar_t *wcsrchr (const wchar_t *, wchar_t);

size_t wcscspn (const wchar_t *, const wchar_t *);
size_t wcsspn (const wchar_t *, const wchar_t *);
wchar_t *wcspbrk (const wchar_t *, const wchar_t *);

wchar_t *wcstok (wchar_t *__restrict, const wchar_t *__restrict, wchar_t **__restrict);

size_t wcslen (const wchar_t *);

wchar_t *wcsstr (const wchar_t *__restrict, const wchar_t *__restrict);
wchar_t *wcswcs (const wchar_t *, const wchar_t *);

wchar_t *wmemchr (const wchar_t *, wchar_t, size_t);
int wmemcmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *wmemcpy (wchar_t *__restrict, const wchar_t *__restrict, size_t);
wchar_t *wmemmove (wchar_t *, const wchar_t *, size_t);
wchar_t *wmemset (wchar_t *, wchar_t, size_t);

wint_t btowc (int);
int wctob (wint_t);

int mbsinit (const mbstate_t *);
size_t mbrtowc (wchar_t *__restrict, const char *__restrict, size_t, mbstate_t *__restrict);
size_t wcrtomb (char *__restrict, wchar_t, mbstate_t *__restrict);

size_t mbrlen (const char *__restrict, size_t, mbstate_t *__restrict);

size_t mbsrtowcs (wchar_t *__restrict, const char **__restrict, size_t, mbstate_t *__restrict);
size_t wcsrtombs (char *__restrict, const wchar_t **__restrict, size_t, mbstate_t *__restrict);

float wcstof (const wchar_t *__restrict, wchar_t **__restrict);
double wcstod (const wchar_t *__restrict, wchar_t **__restrict);
long double wcstold (const wchar_t *__restrict, wchar_t **__restrict);

long wcstol (const wchar_t *__restrict, wchar_t **__restrict, int);
unsigned long wcstoul (const wchar_t *__restrict, wchar_t **__restrict, int);

long long wcstoll (const wchar_t *__restrict, wchar_t **__restrict, int);
unsigned long long wcstoull (const wchar_t *__restrict, wchar_t **__restrict, int);



#ifndef	__FILE_defined

/* The opaque type of streams.  */
typedef struct __stdio_file FILE;

#define	__FILE_defined	1
#endif /* FILE not defined.  */

#define	__need___va_list
#include <stdarg.h>
#ifndef	__GNUC_VA_LIST
#define	__gnuc_va_list	__ptr_t
#endif

int fwide (FILE *, int);


int wprintf (const wchar_t *__restrict, ...);
int fwprintf (FILE *__restrict, const wchar_t *__restrict, ...);
int swprintf (wchar_t *__restrict, size_t, const wchar_t *__restrict, ...);

int vwprintf (const wchar_t *__restrict, __gnuc_va_list);
int vfwprintf (FILE *__restrict, const wchar_t *__restrict, __gnuc_va_list);
int vswprintf (wchar_t *__restrict, size_t, const wchar_t *__restrict, __gnuc_va_list);

wint_t fputwc (wchar_t, FILE *);
wint_t putwc (wchar_t, FILE *);
wint_t putwchar (wchar_t);

#ifndef __MINT__ /* not yet */
int wscanf (const wchar_t *__restrict, ...);
int fwscanf (FILE *__restrict, const wchar_t *__restrict, ...);
int swscanf (const wchar_t *__restrict, const wchar_t *__restrict, ...);

int vwscanf (const wchar_t *__restrict, __gnuc_va_list);
int vfwscanf (FILE *__restrict, const wchar_t *__restrict, __gnuc_va_list);
int vswscanf (const wchar_t *__restrict, const wchar_t *__restrict, __gnuc_va_list);

wint_t fgetwc (FILE *);
wint_t getwc (FILE *);
wint_t getwchar (void);

wchar_t *fgetws (wchar_t *__restrict, int, FILE *__restrict);
int fputws (const wchar_t *__restrict, FILE *__restrict);

wint_t ungetwc (wint_t, FILE *);

struct tm;
size_t wcsftime (wchar_t *__restrict, size_t, const wchar_t *__restrict, const struct tm *__restrict);
#endif

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE)
#ifndef __MINT__
FILE *open_wmemstream(wchar_t **, size_t *);
#endif
size_t mbsnrtowcs(wchar_t *__restrict, const char **__restrict, size_t, size_t, mbstate_t *__restrict);
size_t wcsnrtombs(char *__restrict, const wchar_t **__restrict, size_t, size_t, mbstate_t *__restrict);
wchar_t *wcsdup(const wchar_t *);
size_t wcsnlen (const wchar_t *, size_t);
wchar_t *wcpcpy (wchar_t *__restrict, const wchar_t *__restrict);
wchar_t *wcpncpy (wchar_t *__restrict, const wchar_t *__restrict, size_t);
int wcscasecmp(const wchar_t *, const wchar_t *);
#ifndef __MINT__
int wcscasecmp_l(const wchar_t *, const wchar_t *, locale_t);
#endif
int wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
#ifndef __MINT__
int wcsncasecmp_l(const wchar_t *, const wchar_t *, size_t, locale_t);
int wcscoll_l(const wchar_t *, const wchar_t *, locale_t);
size_t wcsxfrm_l(wchar_t *__restrict, const wchar_t *__restrict, size_t n, locale_t);
#endif
#endif

/* The following functions are extensions found in X/Open CAE.  */
#ifdef __USE_XOPEN
/* Determine number of column positions required for C.  */
extern int wcwidth (wchar_t __c) __THROW;

/* Determine number of column positions required for first N wide
   characters (or fewer if S ends before this) in S.  */
extern int wcswidth (const wchar_t *__s, size_t __n) __THROW;
#endif	/* Use X/Open.  */


#ifdef __cplusplus
}
#endif

#endif
