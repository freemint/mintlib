#include <stdio.h>
#include <stdlib.h>
#include <ieee754.h>

int 
main (int argc, char* argv[])
{
  int i;

  if (argc < 2) {
    fprintf ("usage: %s STRING ...\n", argv[0]);
    return 1;
  }
  
  for (i = 1; i < argc; i++) {
    union ieee754_double udouble;

    udouble.d = atof (argv[i]);
    printf ("%g: mantissa0: %u, mantissa1: %u, exponent: %u, negative: %u\n",
	    udouble.d, udouble.ieee.mantissa0, udouble.ieee.mantissa1,
	    udouble.ieee.exponent, udouble.ieee.negative);
  }
  return 0;
}
