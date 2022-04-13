#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#include "block.h"
#include "../../params.h"

int main(void)
{
  printf("----------START BLOCK SERIALIZATION TEST----------\n");
  // generation cles author
  char *str_key = "(4056d,6c4e1)";
  Key *pKey = str_to_key(str_key);

  // generation des declaration
  CellProtected **lp = read_protected(FILE_DECLARATIONS);

  Block *b = (Block *)malloc(sizeof(Block));
  if (!b)
    exit(12);

  // on met des donnees random juste pour test
  b->author = pKey;
  b->hash = strdup("hash");
  b->nonce = 0;
  b->previous_hash = strdup("previous_hash");
  b->votes = *lp;
  free(lp);

  printf("-----START COMPUTE_PROOF_OF_WORK (BE PATIENT)-----\n\n");
  compute_proof_of_work(b, 2);
  printf("-----END COMPUTE_PROOF_OF_WORK-----\n\n");

  write_block(FILE_BLOCKS, b);

  Block *b_read = read_block(FILE_BLOCKS);

  // write_block(FILE_BLOCKS_TEST, b_read);

  printf("-----START BLOCK_TO_STR-----\n\n");
  char *str_b = block_to_str(b_read);
  printf("%s\n", str_b);
  printf("-----END BLOCK_TO_STR-----\n\n");

  free(str_b);
  delete_block(b_read);
  delete_block(b);

  printf("----------END BLOCK SERIALIZATION TEST----------\n\n\n");

  // printf("----------START TEST OPENSSL----------\n");
  // const char *s = "Rosetta code";
  // unsigned char *d = SHA256(s, strlen(s), 0);

  // printf("Affichage SHA256: \n");
  // for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  // {
  //   printf("%02x ", d[i]);
  // }
  // printf("\n");

  // printf("Affichage de notre SHA256: \n");
  // char *s2 = "Rosetta code";
  // unsigned char *res = hash_sha256(s2);
  // for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  // {
  //   printf("%02x", res[i]);
  // }
  // printf("\n");
  // printf("%ld\n", sizeof(unsigned char));
  // free(res);

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
