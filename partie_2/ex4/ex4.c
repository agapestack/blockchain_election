#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../ex3/keys_struct.h"
#include "../../params.h"

int is_in(int* tab, int val, int size) {
  for(int i=0; i < size; i++) {
    if(tab[i] == val)
      return 1;
  }

  return 0;
}

void generate_random_data(int nv, int nc)
{
  if(nc > nv) {
    printf("Il ne peut pas y avoir plus de candidats que d'electeurs\n");
    exit(13);
  }

  Key **pKey_tab = (Key**)malloc(sizeof(Key*) * nv);
  Key **sKey_tab = (Key**)malloc(sizeof(Key*) * nv);
  Key **candKey_tab = (Key**)malloc(sizeof(Key*) * nc);
  Key *pKey, *sKey;
  Signature *signature;
  FILE *keys = fopen("../../data/keys.txt", "w");
  FILE *candidates = fopen("../../data/candidates.txt", "w");
  FILE *declarations = fopen("../../data/declarations.txt", "w");
  int index_candidates[nc], size = 0, rand_cand, index_choix;

  if(!pKey_tab || !sKey_tab || !candKey_tab || !keys || !candidates || !declarations)
    exit(12);

  // Générations de pairs de clés aléatoire qui correspondent aux électeurs + écriture dans le fichier keys.txt
  for(int i=0; i < nv; i++) {
    pKey = (Key*)malloc(sizeof(Key));
    sKey = (Key*)malloc(sizeof(Key));
    if(!pKey || !sKey)
      exit(12);

    init_pair_keys(pKey, sKey, LOW_SIZE, UP_SIZE);
    pKey_tab[i] = pKey;
    sKey_tab[i] = sKey;

    char *strP = key_to_str(pKey);
    char *strS = key_to_str(sKey);
    fprintf(keys, "%s %s\n", strP, strS);
    free(strP);
    free(strS);
  }

  // On choisit des nombres aléatoire différent < nv; ces nombres correspondent aux index des candidats tiré au sort dans pKey_tab
  while(size < nc) {
    rand_cand = rand() % nv;
    
    // on retire un nombre tant qu'il n'est pas différent de tout ceux tirés auparavent
    while(is_in(index_candidates, rand_cand, size)) {
      rand_cand = rand() % nv;
    }

    index_candidates[size] = rand_cand;
    size++;
  }

  // écriture des clés publique des candidats dans declarations.txt
  for(int i=0; i < nc; i++) {
    char *tmp = key_to_str(pKey_tab[index_candidates[i]]);
    fprintf(candidates, "%s\n", tmp);
    free(tmp);
  }

  // Générations de déclaration signés pour chaque electeur pour un candidat choisis au hasard
  for(int i=0; i < nv; i++) {
    index_choix = rand() % nc;
    signature = sign(key_to_str(pKey_tab[index_choix]), sKey_tab[i]);
    // declaration == pKey electeur, pKey candidat choisis, signature
    char *str_pKey = key_to_str(pKey_tab[i]);
    char *str_pKey_cand = key_to_str(pKey_tab[index_choix]);
    char *str_sign = signature_to_str(signature);
    fprintf(declarations, "%s %s %s\n", str_pKey, str_pKey_cand, str_sign);

    free(str_pKey);
    free(str_pKey_cand);
    free(str_sign);
    
    free_signature(signature);
  }

  for(int i=0; i < nv; i++) {
    free(pKey_tab[i]);
    free(sKey_tab[i]);
  }

  for(int i=0; i < nc; i++) {
    free(candKey_tab[i]);
  }
  
  free(pKey_tab);
  free(sKey_tab);
  free(candKey_tab);

  fclose(keys);
  fclose(candidates);
  fclose(declarations);

}

int main(void)
{

  srand(time(NULL));
  generate_random_data(NB_KEYS, NB_CANDIDATS);

  return 0;
}
