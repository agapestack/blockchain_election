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
  Key *pKey, *sKey;
  char* tmp;
  Signature *signature;
  FILE *keys = fopen(FILE_KEYS ,"w");
  FILE *candidates = fopen(FILE_CANDIDATES, "w");
  FILE *declarations = fopen(FILE_DECLARATIONS, "w");
  int index_candidates[nc], size = 0, rand_cand, index_choix;

  if(!pKey_tab || !sKey_tab || !keys || !candidates || !declarations)
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

  // On choisit des nombres aléatoire différent < nv; ces nombres correspondent aux index des candidats tirés au sort dans pKey_tab
  while(size < nc) {
    rand_cand = rand() % nv;
    // on retire un nombre tant qu'il n'est pas différent de tout ceux tirés auparavent
    while(is_in(index_candidates, rand_cand, size)) {
      rand_cand = rand() % nv;
    }
    index_candidates[size] = rand_cand;
    size++;
  }
  // index_candidates --> tableaux des index des candidats dans pKey_tab

  // écriture des clés publique des candidats dans candidates.txt
  printf("Liste des clés publiques des candidats: \n");
  for(int i=0; i < nc; i++) {
    tmp = key_to_str(pKey_tab[index_candidates[i]]);
    printf("%s\n", tmp);
    fprintf(candidates, "%s \n", tmp);
    free(tmp);
  }

  // Générations de déclaration signés pour chaque electeur pour un candidat choisis au hasard
  for(int i=0; i < nv; i++) {
    char *str_pKey, *str_pKey_cand, *str_sign;

    index_choix = rand() % nc;
    str_pKey = key_to_str(pKey_tab[i]);
    str_pKey_cand = key_to_str(pKey_tab[index_candidates[index_choix]]);
    
    signature = sign(str_pKey_cand, sKey_tab[i]);
    str_sign = signature_to_str(signature);
    // printf("%s %s %s\n", str_pKey, str_pKey_cand, str_sign);
    fprintf(declarations, "%s %s %s \n", str_pKey, str_pKey_cand, str_sign);


    free(str_pKey);
    free(str_pKey_cand);
    free(str_sign);
    
    free_signature(signature);
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

  printf("----------DEBUT GENERATION DONNEE ALEATOIRE----------\n");
  generate_random_data(NB_KEYS, NB_CANDIDATS);
  printf("----------FIN GENERATION DONNEE ALEATOIRE----------\n");

  return 0;
}
