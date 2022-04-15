#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash.h"
#include "../../params.h"

int main(void)
{

  srand(time(NULL));

  printf("----------START READ_PROTECTED----------\n");
  CellProtected **lp = read_protected(FILE_DECLARATIONS);
  printf("----------END READ_PROTECTED----------\n\n\n");

  printf("----------START PRINT_LIST_KEYS----------\n");
  print_list_protected(*lp);
  printf("----------END PRINT_LIST_KEYS----------\n\n\n");

  printf("----------START VERIFY_LIST_PROTECTED----------\n");
  verify_list_protected(lp);
  printf("----------END VERIFY_LIST_PROTECTED----------\n\n\n");

  // A present toutes les declarations sont bien verifier

  printf("----------START TEST HASH FUNCTIONS----------\n");
  // on supprime pas les cles invalides ici pour faciliter les tests
  CellKey **lk = read_public_keys(FILE_KEYS);
  HashTable *ht = create_hashtable(*lk, NB_KEYS);

  printf("\n-----START TEST FIND POSITION-----\n");
  for (int i = 0; i < NB_TEST_FINDPOSITION; i++)
  {
    int random = rand() % NB_KEYS;
    CellKey *cursor = *lk; 
    for(int j=0; j < random; j++) {
      cursor = cursor->next;
    }

    int pos = find_position(ht, cursor->data);
    char *key_str = key_to_str(cursor->data);
    printf("  Cle %-20sPosition %-4d\n", key_str, pos);
    free(key_str);
  }
  printf("-----END TEST FIND POSITION-----\n\n\n");

  delete_hashtable(ht);
  delete_list_keys(lk);
  delete_list_protected(lp);
  // free(list_decla);
  printf("----------END TEST HASH FUNCTIONS----------\n");

  printf("----------START COMPUTE WINNER TEST----------\n");
  // lc == liste candidat
  CellKey **lc = read_public_keys(FILE_CANDIDATES);
  // lv == liste votant
  CellKey **lv = read_public_keys(FILE_KEYS);
  // ld == liste declaration
  CellProtected **ld = read_protected(FILE_DECLARATIONS);

  Key *winner_key = compute_winner(*ld, *lc, *lv, NB_CANDIDATS, NB_KEYS);

  delete_list_protected(ld);
  delete_list_keys(lc);
  delete_list_keys(lv);

  printf("----------END COMPUTE WINNER TEST----------\n");

  return 0;
}