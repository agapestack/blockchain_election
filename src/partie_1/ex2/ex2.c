#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "keys.h"
#include "../../params.h"
#include "../ex1/miller_rabin.h"

int main(void)
{

  srand(time(NULL));

  int nb_erreur = 0;

  for (int i = 0; i < NB_TEST_EX2; i++)
  {
    long u, s, n;
    long prime1, prime2;
    
    // Generation des deux nombres premiers puis des pairs cle publique/secrete
    prime1 = random_prime_number(LOW_SIZE, UP_SIZE, NB_TEST_MILLER_RABIN);
    prime2 = random_prime_number(LOW_SIZE, UP_SIZE, NB_TEST_MILLER_RABIN);
    while (prime1 == prime2)
    {
      prime2 = random_prime_number(LOW_SIZE, UP_SIZE, NB_TEST_MILLER_RABIN);
    }
    generate_key_values(prime1, prime2, &n, &s, &u);

    // Generation d'une chaine aléatoirement
    char *chaine = (char *)malloc(sizeof(char) * (TAILLE_CHAINE + 1));

    if (!chaine)
      exit(12);

    for (int j = 0; j < TAILLE_CHAINE; j++)
    {
      chaine[j] = rand() % 26 + 'a';
    }
    chaine[TAILLE_CHAINE] = '\0';

    // Chiffrement / Dechiffrement
    long *crypted = encrypt(chaine, s, n);
    char *decrypted = decrypt(crypted, strlen(chaine), u, n);

    if(rand() % 1000 == 1) {
      printf("Clé publique :  %ld %ld\n", s, n);
      printf("Clé secrète  :  %ld %ld\n", u, n);
      printf("Chaine generee aleatoirement:\n%s\n", chaine);
      print_long_tab(crypted, TAILLE_CHAINE);
      printf("Chaine dechiffre:\n%s\n\n\n", decrypted);
    }

    if (strcmp(chaine, decrypted) != 0)
      nb_erreur++;

    free(crypted);
    free(decrypted);
    free(chaine);
  }

  printf("Nombre de chaines chiffrees puis dechiffrees non corespondantes: %d sur %d test (affichage 1/1000)\n", nb_erreur, NB_TEST_EX2);

  return 0;
}
