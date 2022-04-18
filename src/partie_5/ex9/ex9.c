#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "./vote.h"

int main(void)
{
  srand(time(NULL));

  // ----------ETAPE 1: GENERATION DATA
  printf("----------START GENERATION DATA----------\n");

  generate_random_data(MOCK_NB_VOTERS, MOCK_NB_CANDIDATS);

  printf("----------END GENERATION DATA----------\n");

  // ----------ETAPE 2: LECTURE DATA
  printf("----------START READ DATA----------\n");

  CellKey **list_cand = read_public_keys(FILE_CANDIDATES);
  CellKey **list_voters = read_public_keys(FILE_KEYS);
  CellProtected **list_decla = read_protected(FILE_DECLARATIONS);

  printf("----------END READ DATA----------\n");

  // cle de l'accesseur (gars qui verifie)
  Key *pKey, *sKey;
  pKey = (Key *)malloc(sizeof(Key));
  sKey = (Key *)malloc(sizeof(Key));
  init_pair_keys(pKey, sKey, LOW_SIZE, UP_SIZE);

  // ----------ETAPE 3: Soumission des votes (creations des block)
  // on itere sur les declarations
  printf("----------START SOUMISSION VOTES----------\n");
  CellTree *tree = NULL;
  CellProtected *cursor = *list_decla;
  int has_root = 0;

  int taille_block = 0;
  while (cursor)
  {
    submit_vote(cursor->data);
    taille_block += 1;

    cursor = cursor->next;
    if (taille_block == NB_VOTE_PER_BLOCK || !cursor)
    {
      taille_block = 0;
      if (has_root == 0)
      {
        has_root += 1;
        tree = init_tree(pKey, D_VALUE);
      }
      else
      {
        create_block(tree, pKey, D_VALUE);
      }
      sleep(1);
      char *tmp_name = generate_uuid();
      add_block(D_VALUE, tmp_name);
      free(tmp_name);
    }
  }

  printf("\n\nTREE: \n");
  print_tree(tree);
  delete_tree(tree);

  printf("----------END SOUMISSION VOTES----------\n");

  free(pKey);
  free(sKey);

  return 0;
}
