/* This program tests the macros and functions in <ctype.h>.  It is
   considered to fail if the output differs from the output on a
   reference system.
   
   Implicitely it is also tested whether the macros in <ctype.h> are
   free of side-effects.  The counter variable in the for-loops is 
   incremented within the macro call.  
*/
   
#include <ctype.h>
#include <stdio.h>
#include <locale.h>

static void test_isalnum (void);
static void test_isalpha (void);
static void test_isascii (void);
static void test_iscntrl (void);
static void test_isdigit (void);
static void test_isgraph (void);
static void test_isprint (void);
static void test_ispunct (void);
static void test_isspace (void);
static void test_isupper (void);
static void test_isxdigit (void);
static void test_isgraph (void);
static void test_isblank (void);

static void test_isalnum_macro (void);
static void test_isalpha_macro (void);
static void test_isascii_macro (void);
static void test_iscntrl_macro (void);
static void test_isdigit_macro (void);
static void test_isgraph_macro (void);
static void test_isprint_macro (void);
static void test_ispunct_macro (void);
static void test_isspace_macro (void);
static void test_isupper_macro (void);
static void test_isxdigit_macro (void);
static void test_isblank_macro (void);

static void test_toascii (void);
static void test__toupper (void);
static void test__tolower (void);

static void test_toascii_macro (void);
static void test__toupper_macro (void);
static void test__tolower_macro (void);

/* The MiNTLib also has these macros.  */
#ifdef __MINT__
static void test_toint_macro (void);
static void test_isodigit_macro (void);
static void test_iscymf_macro (void);
static void test_iscym_macro (void);
#endif

static void test_toupper (void);
static void test_tolower (void);

int
main (int argc, char* argv[])
{
#if __FUNCTION__ != main
# error your compiler system does not define __FUNCTION__.
#endif
	/* Avoid NLS nuisances.  */
	(void) setlocale (LC_ALL, "POSIX");
	
	test_isalnum_macro ();
	test_isalpha_macro ();
	test_isascii_macro ();
	test_iscntrl_macro ();
	test_isdigit_macro ();
	test_isgraph_macro ();
	test_isprint_macro ();
	test_ispunct_macro ();
	test_isspace_macro ();
	test_isupper_macro ();
	test_isxdigit_macro ();
	test_isblank_macro ();
	
	test_isalnum ();
	test_isalpha ();
	test_isascii ();
	test_iscntrl ();
	test_isdigit ();
	test_isgraph ();
	test_isprint ();
	test_ispunct ();
	test_isspace ();
	test_isupper ();
	test_isxdigit ();
	test_isblank ();
	
	test_toascii_macro ();
	test__toupper_macro ();
	test__tolower_macro ();
	
	test_toascii ();
	test__toupper ();
	test__tolower ();

#ifdef __MINT__	
	test_toint_macro ();
	test_isodigit_macro ();
	test_iscymf_macro ();
	test_iscym_macro ();
#endif
	
	test_toupper ();
	test_tolower ();
	
	return 0;
}

static void
test_isalnum_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isalnum (i++) ?
			1 : 0);
}

static void
test_isalpha_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isalpha (i++) ?
			1 : 0);
}

static void
test_isascii_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isascii (i++) ?
			1 : 0);
}

static void
test_iscntrl_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, iscntrl (i++) ?
			1 : 0);
}

static void
test_isdigit_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isdigit (i++) ?
			1 : 0);
}


static void
test_isgraph_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isgraph (i++) ?
			1 : 0);
}

static void
test_isprint_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isprint (i++) ?
			1 : 0);
}

static void
test_ispunct_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, ispunct (i++) ?
			1 : 0);
}

static void
test_isspace_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isspace (i++) ?
			1 : 0);
}

static void
test_isupper_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isupper (i++) ?
			1 : 0);
}

static void
test_isxdigit_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isxdigit (i++) ?
			1 : 0);
}

static void
test_isblank_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isblank (i++) ?
			1 : 0);
}

#undef isalnum
#undef isalpha
#undef isascii
#undef iscntrl
#undef isdigit
#undef isgraph
#undef isprint
#undef ispunct
#undef isspace
#undef isupper
#undef isxdigit
#undef isblank

static void
test_isalnum (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isalnum (i++) ?
			1 : 0);
}

static void
test_isalpha (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isalpha (i++) ?
			1 : 0);
}

static void
test_isascii (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isascii (i++) ?
			1 : 0);
}

static void
test_iscntrl (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, iscntrl (i++) ?
			1 : 0);
}

static void
test_isdigit (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isdigit (i++) ?
			1 : 0);
}

static void
test_isgraph (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isgraph (i++) ?
			1 : 0);
}

static void
test_isprint (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isprint (i++) ?
			1 : 0);
}

static void
test_ispunct (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, ispunct (i++) ?
			1 : 0);
}

static void
test_isspace (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isspace (i++) ?
			1 : 0);
}

static void
test_isupper (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isupper (i++) ?
			1 : 0);
}

static void
test_isxdigit (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isxdigit (i++) ?
			1 : 0);
}

static void
test_isblank (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isblank (i++) ?
			1 : 0);
}

static void
test_toascii_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, toascii (i++));
}

static void
test__toupper_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, _toupper (i++));
}

static void
test__tolower_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, _tolower (i++));
}

#undef toascii
#undef _toupper
#undef _tolower

static void
test_toascii (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, toascii (i++));
}

static void
test__toupper (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, _toupper (i++));
}

static void
test__tolower (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, _tolower (i++));
}

#ifdef __MINT__
static void
test_toint_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, toint (i++));
}

static void
test_isodigit_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, isodigit (i++) ?
			1 : 0);
}

static void
test_iscymf_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, iscymf (i++) ?
			1 : 0);
}

static void
test_iscym_macro (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, iscym (i++) ?
			1 : 0);
}
#endif  /* not __MINT__ */

static void
test_toupper (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, toupper (i++));
}

static void
test_tolower (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, tolower (i++));
}

