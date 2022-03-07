#ifndef __KEYS__
#define __KEYS__

long extended_gcd(long s, long t, long *u, long *v);
void generate_key_values(long p, long q, long* n, long *s, long *u);
char* decrypt(long* crypted, int size, long u, long n);
long* encrypt(char* chaine, long s, long n);

#endif
