/*  test-iioscanf.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* This scanf test checks some basic features of scanf and friends.
   More sophisticated checks should be checked with the float
   version.  */
   
#ifdef	BSD
#include </usr/include/stdio.h>
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>


int
main (int argc, char **argv)
{
	char buf[BUFSIZ];
	int x;
	int result = 0;

	fputs ("Test 1\n", stdout);
  	if (sscanf ("0", "%d", &x) != 1) {
      		fputs ("test failed!\n", stdout);
      		result = 1;
    	}

	fputs ("Test 2\n", stdout);
	sscanf ("conversion] Zero flag Ze]ro#\n", "%*[^]] %[^#]\n", buf);
  	if (strcmp (buf, "] Zero flag Ze]ro") != 0) {
		fputs ("test failed!\n", stdout);
      		result = 1;
    	}

	fputs ("Test 3\n", stdout);
  	{
    		char name[50];
    		fprintf (stdout,
	     		 "sscanf (\"thompson\", \"%%s\", name) == %d, name == \"%s\"\n",
	     		 sscanf ("thompson", "%s", name),
	     		 name);
    		if (strcmp (name, "thompson") != 0) {
			fputs ("test failed!\n", stdout);
			result = 1;
      		}
  	}

  	fputs ("Test 4:\n", stdout);
	{
    		int res, val, n;

    		res = sscanf ("-242", "%3o%n", &val, &n);
    		printf ("res = %d, val = %d, n = %d\n", res, val, n);
    		if (res != 1 || val != -20 || n != 3) {
			fputs ("test failed!\n", stdout);
			result = 1;
      		}
  	}

  	fputs ("Test 5:\n", stdout);
  	{
    		char* p = (char*) -1;
    		int res;

    		sprintf (buf, "%p", NULL);
    		res = sscanf (buf, "%p", &p);
    		printf ("sscanf (\"%s\", \"%%p\", &p) = %d, p == %p\n", buf, res, p);

    		if (res != 1 || p != NULL) {
			fputs ("test failed!\n", stdout);
			result = 1;
      		}
  	}

  	fputs ("Test 6:\n", stdout);
	{
		int i, n, r;
	
	  	n = i = r = -1;
	  	r = sscanf ("1234:567", "%d%n", &i, &n);
	  	printf ("%d %d %d\n", r, n, i);
	  	if (r != 1 || i != 1234 || n != 4) {
	    		fputs ("test failed!\n", stdout);
	    		result = 1;
	    	}
	}
	
	exit (result);
}
