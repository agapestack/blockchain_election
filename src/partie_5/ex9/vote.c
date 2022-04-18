#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../../params.h"
#include "./vote.h"

// Ajoute au fichier pending_votes la declaration de vote associe a p
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
  if (!dernier_node)
  {
    b->previous_hash = NULL;
  }
  else
  {
    // todo: strcpy dernier hash
    b->previous_hash = (char*)malloc(sizeof(char) * strlen(dernier_node->block->hash) + 1);

    for(int i=0; i < strlen(dernier_node->block->hash); i++) {
      b->previous_hash[i] = dernier_node->block->hash[i];
    }
    b->previous_hash[strlen(b->previous_hash)] = '\0';
  }
  b->hash = NULL;
  b->nonce = 0;

  b->votes = *list_protected;
  // calcul de nonce et de hash
  compute_proof_of_work(b, d);

  // char *tmp_block = block_to_str(b);
  // printf("%s\n", tmp_block);
  // free(tmp_block);

  write_block(FILE_PENDING_BLOCK, b);

  // Ajout d'un noeud contenant le block dans tree
  CellTree *nouv_tree = create_node(b);
  // print_tree(nouv_tree);
  add_child(dernier_node, nouv_tree);

  // delete_block(b);

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

    printf("%s\n", name);
    write_block(name, b);

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

  // ----------ETAPE 1: creation du tableau contenant les noeuds de l'arbre----------
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

  // ----------ETAPE 2: Ajout des liens peres/fils entres les noeuds du tableau T----------
  for (int i = 0; i < nb_block_file; i++)
  {
    for (int j = 0; j < nb_block_file; j++)
    {
      // si T[j] est un fil des T[i], on ajoute
      if (strcmp(T[i]->block->hash, T[j]->block->previous_hash) == 0)
      {
        add_child((T[i]), T[j]);
      }
    }
  }

  // ----------ETAPE 3: Extraction de la racine du tableau T----------
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
  // ----------ETAPE 1: Extraction de la liste des declarations de vote----------
  // on prend le fils le plus profond (car on recupere les blocs de la chaine la plus longues --> règle de confiance)
  CellTree *dernier_child = highest_child(tree);
  CellProtected **list_decla = NULL;

  while (dernier_child)
  {
    // fusion de la liste de declaration du fils avec cell du pere
    list_decla = merge_list_decla(list_decla, &dernier_child->block->votes);
    // On passe au pere
    dernier_child = dernier_child->father;
  }

  // ----------ETAPE 2: Suppression des declarations de vote non valide----------
  verify_list_protected(list_decla);

  // ----------ETAPE 3: Declaration du vainqueur de l'election----------
  Key *res = compute_winner(*list_decla, candidates, voters, sizeC, sizeV);
  return res;
}

CellTree *init_tree(Key *author, int d)
{
  CellTree *tree = NULL;
  Block *b_racine = (Block *)malloc(sizeof(Block));
  CellProtected **list_protected = read_protected(FILE_PENDING_VOTES);
  if (!b_racine)
    exit(12);

  b_racine->author = author;
  b_racine->hash = NULL;
  b_racine->previous_hash = NULL;
  b_racine->votes = *list_protected;
  b_racine->nonce = 0;

  remove(FILE_PENDING_VOTES);
  compute_proof_of_work(b_racine, d);
  write_block(FILE_PENDING_BLOCK, b_racine);
  tree = create_node(b_racine);
  // print_tree(tree);

  return tree;
}

char *generate_uuid()
{
  char *buffer = (char *)malloc(sizeof(char) * 256);
  if (!buffer)
    exit(12);

  char random_str[16];
  for (int i = 0; i < 15; i++)
  {
    random_str[i] = rand() % 10 + 'a';
  }

  snprintf(buffer, 256, "%s%s.dat", DIR_BLOCKCHAIN, random_str);

  return buffer;
}
