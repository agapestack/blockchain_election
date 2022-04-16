#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./generate_data.h"

int main(void)
{
  srand(time(NULL));

  printf("----------DEBUT GENERATION DONNEE ALEATOIRE----------\n");
  generate_random_data(NB_KEYS, NB_CANDIDATS);
  printf("----------FIN GENERATION DONNEE ALEATOIRE----------\n");

  return 0;
}
