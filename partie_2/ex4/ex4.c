#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../ex3/keys_struct.h"
#include "../../params.h"

void generate_random_data(int nv, int nc)
{
  Key **pKey_tab = (Key**)malloc(sizeof(Key*) * nv);
  Key **sKey_tab = (Key**)malloc(sizeof(Key*) * nv);
  Key **candKey_tab = (Key**)malloc(sizeof(Key*) * nc);
  Key *pKey, *sKey;
  FILE *keys = fopen("../../data/keys.txt", "w");
  FILE *candidates = fopen("../../data/candidates.txt", "w");
  FILE *declarations = fopen("../../data/declarations.txt", "w");

  if(!pKey_tab || !sKey_tab || !candKey_tab || !keys || !candidates || !declarations)
    exit(12);

  for(int i=0; i < nv; i++) {
    pKey = (Key*)malloc(sizeof(Key));
    sKey = (Key*)malloc(sizeof(Key));
    if(!pKey || !sKey)
      exit(12);

    init_pair_keys(pKey, sKey, LOW_SIZE, UP_SIZE);
    pKey_tab[i] = pKey;
    sKey_tab[i] = sKey;

    fprintf(keys, "%d %s %s", i, key_to_str(pKey), key_to_str(sKey));
  }

  for(int i=0; i < nv; i++) {
    free(pKey_tab[i]);
    free(sKey_tab[i]);
  }
  free(pKey_tab);
  free(sKey_tab);

  fclose(keys);
  fclose(candidates);
  fclose(declarations);

}

int main(void)
{

  srand(time(NULL));
  printf("test\n");
  generate_random_data(5, 1);

  return 0;
}
