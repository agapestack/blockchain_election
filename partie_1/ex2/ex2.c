#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "../ex1/miller_rabin.h"
#include "../ex1/exponentiation.h"
#include "keys.h"

#define NB_TEST_RSA 10

void print_long_vector(long *result, int size)
{
  printf("Encoded representation : \n");
  printf ( "Vector : [ " ) ;
  for ( int i =0; i < size ; i ++) {
      printf( "%lx \t", result[i]);
      printf( "%ld \t", result[i]);
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

  // printf("%lx\t%lx\n", p, q);

  long n, s, u;
  generate_key_values(p, q, &n, &s, &u);
  // printf("n=%lx\ts=%lx\tu=%lx\n", n, s, u);

  if(u < 0) {
    long t = (p - 1) * (q - 1);
    u = u + t;
  }

  // printf("cle publique = (%lx, %lx) \n", s, n);
  // printf("cle privee = (%lx, %lx) \n", u, n);

  // Chiffrement
  char mess[256] = "Les codes de la bombe nucléaire sont (ZLBr8pfTRHu86YvQ782Wsbf23x6j6EU5d2ycs6EQ4Er2P788T3v3j7BpSDLzjp4M)";
  int len = strlen(mess);
  long *crypted = encrypt(mess, s, n);
  
  printf("Message: %s\n", mess);
  print_long_vector(crypted, len);

  // Dechiffrement
  char* decoded = decrypt(crypted, len, u, n);
  printf("Decoded: %s\n\n", decoded);

  free(crypted);
  free(decoded);

  // randomisation des test automatiques
  for(int i=0; i < NB_TEST_RSA; i++) {
    // génération d'un message aléatoire
    for(int j=0; j < 255; j++) {
      mess[j] = rand() % 26 + 'a';
    }
    mess[255] = '\0';
    len = strlen(mess);

    crypted = encrypt(mess, s, n);
    decoded = decrypt(crypted, len, u, n);

    printf("Message: %s\n", mess);
    print_long_vector(crypted, len);
    printf("Decoded: %s\n", decoded);

    // Il est possible que cette assert ne marche pas, on est alors tomber sur un cas ou notre génération probabiliste de nombre premier a échoué, mais dans la pratique avec des nombre premiers suffisamment eleve ce cas est extremement rare!
    if(strcmp(mess, decoded) == 0) {
      printf("------------------Les chaînes correspondent bien!------------------\n\n\n");
    }
    assert(strcmp(mess, decoded) == 0);

    free(crypted);
    free(decoded);
  }

  return 0;
}