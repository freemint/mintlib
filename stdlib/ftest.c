#include <stdio.h>
#include <stdlib.h>
#include <ieee754.h>
#include <errno.h>

int 
main (int argc, char* argv[])
{
  int i;

  if (argc < 2) {
    fprintf ("usage: %s STRING ...\n", argv[0]);
    return 1;
  }
  
  for (i = 1; i < argc; i++) {
    union ieee754_float ufloat;

    __set_errno (0);
    ufloat.f = atof (argv[i]);
    
    if (errno != 0)
      printf ("%s: conversion error: %s\n", argv[i], strerror (errno));

    printf ("%g: mantissa: %lu, exponent: %lu, negative: %lu\n",
	    ufloat.f, ufloat.ieee.mantissa, ufloat.ieee.exponent,
	    ufloat.ieee.negative);
  }
  return 0;
}
