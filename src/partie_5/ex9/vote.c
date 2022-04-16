#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../../params.h"
#include "./vote.h"

void submit_vote(Protected *p)
{
  if (!p)
    return;
  FILE *fic = fopen(FILE_PENDING_VOTES, "a");
  if (!fic)
    exit(12);

  char *str_protected = protected_to_str(p);
  fprintf(fic, "%s\n", str_protected);

  free(str_protected);
  fclose(fic);

  return;
}
void create_block(CellTree *tree, Key *author, int d)
{
  Block *b = (Block *)malloc(sizeof(Block));
  if (!b)
    exit(12);

  // recuperation des votes
  CellProtected **list_protected = read_protected(FILE_PENDING_VOTES);
  // suppression du fichier des votes en attentes
  remove(FILE_PENDING_VOTES);

  CellTree *dernier_node = last_node(tree);
  // initialisation du block
  b->author = author;
  b->previous_hash = dernier_node->block->hash;
  b->votes = *list_protected;
  // calcul de nonce et de hash
  compute_proof_of_work(b, d);

  write_block(FILE_PENDING_BLOCK, b);
  delete_block(b);

  return;
}

void add_block(int d, char *name)
{
  Block *b = read_block(FILE_PENDING_BLOCK);
  if (!b)
    return;

  if (verify_block(b, d) == 1)
  { // le bloc est valide
    // creation du fichier
    FILE *fic = fopen(name, "w");
    if (!fic)
      exit(12);

    write_block(strcat(DIR_BLOCKCHAIN, name), b);

    fclose(fic);
  }
  else
  {
    printf("Le Block en attente n'est pas valide\n");
  }

  // suppression du fichier
  remove(FILE_PENDING_BLOCK);
  return;
}

CellTree *read_tree()
{
  DIR *rep = opendir(DIR_BLOCKCHAIN);
  struct dirent *dir;
  if (!rep)
    exit(12);

  int nb_block_file = 0;

  // compter le nombre de fichier block
  while ((dir = readdir(rep)))
  {
    if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
    {
      nb_block_file += 1;
    }
  }

  // ----------ETAPE 1----------
  // Allocation T: tableau de pointeur sur arbre
  CellTree **T = (CellTree **)malloc(sizeof(CellTree *) * nb_block_file);
  if (!T)
    exit(12);
  for (int i = 0; i < nb_block_file; i++)
  {
    T[i] = NULL;
  }

  int index_T = 0;
  // on met les noeuds associes aux blocks contenus dans les fichiers dans le tableau T
  while ((dir = readdir(rep)))
  {
    if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
    {
      // printf("Chemin du fichier: ./blockchain/%s\n", dir->d_name);

      // recuperation du block
      Block *b = read_block(dir->d_name);
      // creation du noeud associé
      CellTree *ct = create_node(b);
      // stockage dans le tableau
      T[index_T++] = ct;
    }
  }
  closedir(rep);

  // ----------ETAPE 2----------
  for (int i = 0; i < nb_block_file; i++)
  {
    for (int j = 0; j < nb_block_file; j++)
    {
      // si T[j] est un fil des T[i], on ajoute
      if (strcmp(T[i]->block->hash, T[j]->block->previous_hash) == 0)
      {
        add_child(T[i], T[j]);
      }
    }
  }

  // ----------ETAPE 3----------
  CellTree *racine = NULL;
  for (int i = 0; i < nb_block_file; i++)
  {
    if (T[i]->father == NULL)
    {
      racine = T[i];
    }
  }

  return racine;
}

Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{ 
  
}
