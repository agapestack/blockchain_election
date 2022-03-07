#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "../ex1/miller_rabin.h"
#include "../ex1/exponentiation.h"
#include "keys.h"

void print_long_vector(long *result, int size)
{
  printf ( "Vector : [ " ) ;
  for ( int i =0; i < size ; i ++) {
      printf( "%lx \t", result[i]);
  }
  printf ( " ]\n" ) ;
}

int main() {
  srand(time(NULL));

  long p = random_prime_number(3, 7, 5000);
  long q = random_prime_number(3, 7, 5000);
  while(p == q) {
    q = random_prime_number(3, 7, 5000);
  }

  printf("%lx\t%lx\n", p, q);

  long n, s, u;
  generate_key_values(p, q, &n, &s, &u);
  printf("n=%lx\ts=%lx\tu=%lx\n", n, s, u);

  if(u < 0) {
    long t = (p - 1) * (q - 1);
    u = u + t;
  }

  printf("cle publique = (%ld, %ld) \n", s, n);
  printf("cle privee = (%ld, %ld) \n", u, n);

  // Chiffrement
  char mess[10] = "Hello";
  int len = strlen(mess);
  long *crypted = encrypt(mess, s, n);
  
  printf("Initial message: %s\n", mess);
  printf("Encoded representation : \n");
  print_long_vector(crypted, len);

  // Dechiffrement
  char* decoded = decrypt(crypted, len, u, n);
  printf("Decoded: %s\n", decoded);

  return 0;
}