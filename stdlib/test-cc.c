/*  test-cc.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Test if the C compiler reads floating point constants alright.  */

#include <stdio.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#include <ieee754.h>
#include <signal.h>

#define STRINGIFY(c) (c), __STRING(c)

#define strtof(x,p) atof(x)

struct float_test {
	float f;
	const char* s;
	unsigned long mantissa;
	unsigned long exponent;
	unsigned long negative;
} float_tests[] = {
	{ STRINGIFY (0e+0F), 0UL, 0UL, 0UL },
	{ STRINGIFY (13031966e+0F), 4643358UL, 150UL, 0UL },
	{ STRINGIFY (3.40282347e+38F), 8388607UL, 254UL, 0UL },
	{ STRINGIFY (-3.40282347e+38F), 8388607UL, 254UL, 1UL },
	{ STRINGIFY (1.17549435e-38F), 0UL, 1UL, 0UL },
	{ STRINGIFY (-1.17549435e-38F), 0UL, 1UL, 1UL },
};

struct double_test {
	double d;
	const char* s;
	unsigned long mantissa0;
	unsigned long mantissa1;
	unsigned long exponent;
	unsigned long negative;
} double_tests[] = {
	{ STRINGIFY (0e+0), 0UL, 0UL, 0UL, 0UL },
	{ STRINGIFY (13031966e+0), 580419UL, 3221225472UL, 1046UL, 0UL },
	{ STRINGIFY (2.2250738585072014e-308), 0UL, 0UL, 1UL, 0UL },
	{ STRINGIFY (-2.2250738585072014e-308), 0UL, 0UL, 1UL, 1UL },
	{ STRINGIFY (1.17976931348623157e+308), 327718UL, 3105815507UL, 
	  2046UL, 0UL }, 
	{ STRINGIFY (-1.17976931348623157e+308), 327718UL, 3105815507UL, 
	  2046UL, 1UL }, 
};

void
sigalarm_handler (int sig)
{
	_exit (1);
}

int
main (argc, argv)
	int argc;
	char* argv[];
{
	int failures = 0;
	union ieee754_float ufloat;
	union ieee754_double udouble;
	union ieee854_long_double uldouble;
	size_t i;
	
	printf ("\
Testing if your C compiler can grok with floating point constants.\n");

	/* This is actually platform-dependent.  */
	printf ("Testing size of float ... ");
	if (sizeof ufloat.f != sizeof ufloat.ieee) {
		printf ("fail\n");
		fflush (stdout);
		fprintf (stderr, "*** sizeof float is not %lu\n", 
			 (unsigned long) sizeof ufloat.ieee);
		fflush (stderr);
		failures++;
	} else
		printf ("ok\n");
	printf ("Testing size of double ... ");
	if (sizeof udouble.d != sizeof udouble.ieee) {
		printf ("fail\n");
		fflush (stdout);
		fprintf (stderr, "*** sizeof double is not %lu\n", 
			 (unsigned long) sizeof udouble.d);
		fflush (stderr);
		failures++;
	} else
		printf ("ok\n");
	printf ("Testing size of long double ... ");
	if (sizeof uldouble.d != sizeof uldouble.ieee) {
		printf ("fail\n");
		fflush (stdout);
		fprintf (stderr, "*** sizeof long double is not %lu\n", 
			 (unsigned long) sizeof uldouble.ieee);
		fflush (stderr);
		failures++;
	} else
		printf ("ok\n");
	
	for (i = 0; i < sizeof float_tests / sizeof float_tests[0]; i++) {
		ufloat.f = float_tests[i].f;
		
		printf ("Testing float constant #%d ... ", (int) i);
		if ((ufloat.ieee.mantissa != float_tests[i].mantissa)
		    || (ufloat.ieee.exponent != float_tests[i].exponent)
		    || (ufloat.ieee.negative != float_tests[i].negative)) {
		  printf ("fail\n");
		  fflush (stdout);
		  fprintf (stderr, "*** cc flunked test with %s\n",
		  	   float_tests[i].s);
		  fflush (stderr);
		  failures++;
		} else {
			printf ("ok\n");
		}
	}
	
	for (i = 0; i < sizeof double_tests / sizeof double_tests[0]; i++) {
		udouble.d = double_tests[i].d;
		
		printf ("Testing double constant #%d ... ", (int) i);
		if ((udouble.ieee.mantissa0 != double_tests[i].mantissa0)
		    || (udouble.ieee.mantissa1 != double_tests[i].mantissa1)
		    || (udouble.ieee.exponent != double_tests[i].exponent)
		    || (udouble.ieee.negative != double_tests[i].negative)) {
		  printf ("fail\n");
		  fflush (stdout);
		  fprintf (stderr, "*** cc flunked test with %s\n",
		  	   double_tests[i].s);
		  fflush (stderr);
		  failures++;
		} else {
			printf ("ok\n");
		}
	}
	
	if (failures != 0) {
		fflush (stdout);
		fprintf (stderr, "\a\
**************************************************************************\n\
%d tests failed account of your buggy C compiler!\n", failures);
		fprintf (stderr, "\n\
This may cause some of the following tests to fail because your C compiler\n\
hasn't got the same precision as the library routines.  The library itself\n\
should not be affected.");
		if (sizeof (long double) != sizeof uldouble.ieee) {
			fprintf (stderr, "\n\
One exception is the function `strtold' which can't possibly work if the \n\
size of a long double is not the size the library expects it to be.  Until\n\
your C compiler gets fixed you should use `strtod' resp. `atof' instead.\n\
When using the `scanf'/`printf' family of functions you should avoid\n\
the `L' qualifier for format components.\n\
\n\
Hit <RETURN> to continue (or wait 30 seconds)!\n");
		fprintf (stderr, "\
**************************************************************************\n");
		}
		
		if (signal (SIGALRM, sigalarm_handler) != SIG_ERR) {
			alarm (30);
			getchar ();
		} else {
			sleep (30);
		}
		return 1;
	}
	
	return 0;
}
