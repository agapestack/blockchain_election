#include <stdio.h>
#include <stdlib.h>

#include "./tree.h"
#define NB_BLOCKS 10
#define TEST_NB_KEYS 20
#define TEST_NB_CANDIDATS 2

// fichier particulier car les tests sont hard-coded ici pour des raisons pratique
// Ce main sert juste a verifier l'implementation de l'arbre et pas autres choses
// Les tests dynamiques sont l'objet de l'exercice suivant

int main(void)
{
  printf("----------START CREATION BLOCKS----------\n");
  // creation d'un tableau de blocs
  Block **tab_block;
  tab_block = (Block **)malloc(sizeof(Block *) * NB_BLOCKS);
  for (int i = 0; i < NB_BLOCKS; i++)
  {
    tab_block[i] = NULL;
  }


  // generations de blocks aleatoire
  for (int i = 0; i < NB_BLOCKS; i++)
  {
    generate_random_data_test(TEST_NB_KEYS, TEST_NB_CANDIDATS);
    tab_block[i] = read_block(FILE_TEST_DECLARATIONS);
    // printf("%s\n", block_to_str(tab_block[i]));
  }
  printf("----------FIN CREATION BLOCKS----------\n");


  printf("----------START CREATION NODE----------\n");
  // Creation d'un tableau de noeud
  CellTree **tab_node = (CellTree **)malloc(sizeof(CellTree *) * NB_BLOCKS);
  for (int i = 0; i < NB_BLOCKS; i++)
  {
    tab_node[i] = create_node(tab_block[i]);
  }

  for(int i=0; i < NB_BLOCKS; i++) {
    print_node(tab_node[i]);
  }

  printf("----------END CREATION NODE----------\n");

  printf("----------START TEST ADD CHILD----------\n");

  add_child(tab_node[0], tab_node[1]);
  add_child(tab_node[1], tab_node[2]);
  add_child(tab_node[2], tab_node[3]);
  add_child(tab_node[2], tab_node[4]);
  add_child(tab_node[0], tab_node[5]);
  add_child(tab_node[5], tab_node[6]);
  add_child(tab_node[6], tab_node[7]);
  add_child(tab_node[8], tab_node[9]);

  // Pour le test de delete tree il faut que les nodes soient tous liés
  // add_child(tab_node[0], tab_node[1]);
  // add_child(tab_node[1], tab_node[2]);
  // add_child(tab_node[2], tab_node[3]);
  // add_child(tab_node[3], tab_node[4]);
  // add_child(tab_node[4], tab_node[5]);
  // add_child(tab_node[5], tab_node[6]);
  // add_child(tab_node[6], tab_node[7]);
  // add_child(tab_node[7], tab_node[8]);
  // add_child(tab_node[8], tab_node[9]);
  // delete_tree(tab_node[0]);

  print_clean_tree(tab_node[0], tab_node[0]->height);

  printf("----------END TEST ADD CHILD----------\n");
  printf("----------START TEST HIGHEST CHILD----------\n");
  print_node(highest_child(tab_node[0]));
  printf("----------END TEST HIGHEST CHILD----------\n");

  printf("----------START CLEANNING----------\n");
  for(int i=0; i < NB_BLOCKS; i++) {
    if(tab_node[i]) {
      delete_tree_cell(tab_node[i]);
    }
  }
  free(tab_node);
  free(tab_block);

  // ces fichiers ne sont la que pour les tests statique de cette exo on les suppriment donc après
  remove(FILE_TEST_DECLARATIONS);
  remove(FILE_TEST_KEYS);
  remove(FILE_TEST_CANDIDATES);
  printf("----------END CLEANNING----------\n");

  return 0;
}
