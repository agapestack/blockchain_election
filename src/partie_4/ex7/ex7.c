#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#include "block.h"

int main(void)
{
  printf("----------START TEST OPENSSL----------\n");
  const char *s = "Rosetta code";
  unsigned char *d = SHA256(s, strlen(s), 0);

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    printf("%02x", d[i]);
  }
  putchar('\n');
  printf("----------END TEST OPENSSL----------\n\n\n");

  printf("----------START CUSTOM SHA256----------\n");
  char *str_test = "Rosetta code";
  unsigned char *res = hash_sha256(str_test);
  printf("%s\n", res);
  free(res);
  printf("----------END CUSTOM SHA256----------\n\n\n");

  // printf("----------DEBUT COMPARAISON----------\n");
  // clock_t temps_initial, temps_final;
  // double temps_cpu, tps_1, tps_2, tps_cpu_last_prime;
  // int i = 0, save_time = 0;
  // int last_prime = 2;

  // temps_cpu = 0;
  // while (temps_cpu < 0.002)
  // {
  //   temps_initial = clock();
  //   if (is_prime_naive(i) == 1)
  //   {
  //     last_prime = i;
  //     save_time = 1;
  //   }
  //   temps_final = clock();
  //   temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

  //   if (save_time == 1 && temps_cpu < 0.002)
  //   {
  //     printf("Nombre premier trouvé: %d\ttemps=%f\n", last_prime, temps_cpu);
  //     tps_cpu_last_prime = temps_cpu;
  //     save_time = 0;
  //   }

  //   i++;
  // }
  // printf("Dernier nombre premier trouver en 2ms par is_prime_naive: %d\ttemps=%fs\n", last_prime, tps_cpu_last_prime);
  // printf("----------FIN COMPARAISON----------\n\n\n");

  return 0;
}
