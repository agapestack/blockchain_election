#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "./miller_rabin.h"
#include "../../params.h"

int main(void)
{
  srand(time(NULL));

  // QUESTION 1.1
  assert(is_prime_naive(2) == 1);
  assert(is_prime_naive(173) == 1);
  assert(is_prime_naive(7643) == 1);
  assert(is_prime_naive(2851) == 1);
  assert(is_prime_naive(223) == 1);
  assert(is_prime_naive(1) == 0);
  assert(is_prime_naive(7234) == 0);
  assert(is_prime_naive(976) == 0);
  assert(is_prime_naive(936497) == 0);
  assert(is_prime_naive(38) == 0);

  // QUESTION 1.2
  clock_t temps_initial, temps_final;
  double temps_cpu, tps_1, tps_2, tps_cpu_last_prime;
  int i = 0, save_time = 0;
  int last_prime = 2;

  temps_cpu = 0;
  printf("----------DEBUT MAX PREMIER < 0.002s----------\n");
  while (temps_cpu < 0.002)
  {
    temps_initial = clock();
    if (is_prime_naive(i) == 1)
    {
      last_prime = i;
      save_time = 1;
    }
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

    if (save_time == 1 && temps_cpu < 0.002)
    {
      printf("Nombre premier trouvé: %d\ttemps=%f\n", last_prime, temps_cpu);
      tps_cpu_last_prime = temps_cpu;
      save_time = 0;
    }

    i++;
  }
  printf("Dernier nombre premier trouver en 2ms par is_prime_naive: %d\ttemps=%fs\n", last_prime, tps_cpu_last_prime);
  printf("----------FIN MAX PREMIER < 0.002s----------\n\n\n");

  // QUESTION 1.3
  assert(modpow_naive(2, 10, 255) == 4);
  assert(modpow_naive(5, 10, 56) == 9);
  assert(modpow_naive(7, 11, 33) == 7);
  assert(modpow_naive(3, 24, 22) == 15);
  assert(modpow_naive(53534, 0, 232) == 1);
  assert(modpow_naive(6, 4, 1296) == 0);
  assert(modpow_naive(8, 5, 7) == 1);
  assert(modpow_naive(12, 5, 2) == 0);

  // QUESTION 1.4
  assert(modpow(2, 10, 255) == 4);
  assert(modpow(5, 10, 56) == 9);
  assert(modpow(7, 11, 33) == 7);
  assert(modpow(3, 24, 22) == 15);
  assert(modpow(53534, 0, 232) == 1);
  assert(modpow(6, 4, 1296) == 0);
  assert(modpow(8, 5, 7) == 1);
  assert(modpow(12, 5, 2) == 0);

  // QUESTION 1.5
  FILE *fic = fopen(FILE_COMPARAISON_EXPONENTIATION, "w");
  if (!fic)
  {
    printf("Erreur ouverture du fichier\n");
    exit(12);
  }

  int nb_alea = rand() % RAND_MAX;
  int mod_alea = rand() % 1024;

  // comparaison de modpow et modpow_naive
  printf("----------DEBUT COMPARAISON MODPOW----------\n");
  for (int i = 2; i < NB_TEST_MODPOW; i++)
  {
    temps_initial = clock();
    for (int j = 0; j < ECART_TOUR_EXPONENTIATION; j++)
    {
      modpow_naive(nb_alea, i, mod_alea);
    }
    temps_final = clock();
    tps_1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

    temps_initial = clock();
    for (int j = 0; j < ECART_TOUR_EXPONENTIATION; j++)
    {
      modpow(nb_alea, i, mod_alea);
    }
    temps_final = clock();
    tps_2 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

    if (rand() % 10 == 5)
    {
      printf("Temps modpow_naive = %fs\tTemps modpow = %fs\n", tps_1, tps_2);
    }

    fprintf(fic, "%d %f %f\n", i, tps_1, tps_2);
  }

  printf("----------FIN COMPARAISON MODPOW----------\n\n\n");

  fclose(fic);

  // Test fonction miller_rabin
  printf("----------DEBUT GENERATION NB PREMIER----------\n");
  long random_prime;

  for (int i = 0; i < NB_PREMIER_MILLER_RABIN; i++)
  {
    random_prime = random_prime_number(LOW_SIZE, UP_SIZE, NB_TEST_MILLER_RABIN);
    printf("Nombre premier Aleatoire trouve: %ld\tPremier: ", random_prime);

    if (is_prime_naive(random_prime) == 1)
    {
      printf("Oui\n");
    }
    else
    {
      printf("Non\n");
    }
  }
  printf("----------FIN GENERATION NB PREMIER----------\n\n\n");

  return 0;
}
