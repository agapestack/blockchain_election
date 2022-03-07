#ifndef __MILLER_RABIN__
#define __MILLER_RABIN__

#include "exponentiation.h"

int witness(long a, long b, long d, long p);
long rand_long(long low, long up);
int is_prime_miller(long p, int k);
long random_prime_number(int low_size, int up_size, int k);

#endif
