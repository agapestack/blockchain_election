#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys.h"
#include "../ex1/miller_rabin.h"

long extended_gcd(long s, long t, long *u, long *v) {
  if(s == 0) {
    *u = 0;
    *v = 1;
    return t;
  }

  long uPrim, vPrim;
  long gcd = extended_gcd(t%s, s, &uPrim, &vPrim);
  *u = vPrim - (t/s) * uPrim;
  *v = uPrim;

  return gcd;
}

void generate_key_values(long p, long q, long *n, long *s, long *u) {
  *n = p * q;
  long t = (p - 1) * (q - 1);
  long v;

  do {
    *s = rand_long(1, t);
  } while(extended_gcd(*s, t, u, &v) != 1);

  if (*u < 0)
  {
    *u = *u + t;
  }

  // printf("n=%ld\tu=%ld\ts=%ld\tt=%ld\t(s*u)(mod t)=%ld\n", *n, *u, *s, t, (*s**u) % t);

  return;
}

long* encrypt(char* chaine, long s, long n) {
  long* res = (long*)malloc(sizeof(long) * strlen(chaine));
  if(!res)
    exit(12);

  long mod;
  int i = 0;
  while(chaine[i] != '\0') {
    mod = modpow((int)chaine[i], s, n);
    res[i++] = mod;
  }

  return res;
}

char* decrypt(long* crypted, int size, long u, long n) {
  char* res = (char*)malloc(sizeof(char) * (size + 1));
  if(!res)
    exit(12);

  for(int i=0; i < size; i++) {
    res[i] = modpow(crypted[i], u, n);
  }

  res[size] = '\0';

  return res;
}

void print_long_tab(long* tab, int size) {
  printf("Chiffrement: \n");
  for(int i=0; i < size; i++) {
    printf("%ld ", tab[i]);
  }
  printf("\n");
}
