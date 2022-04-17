#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ex7/block.h"
#include "./tree.h"
#include "../../params.h"

CellTree *create_node(Block *b)
{
  CellTree *ct = (CellTree *)malloc(sizeof(CellTree));
  if (!ct)
    exit(12);

  ct->block = b;
  ct->father = NULL;
  ct->firstChild = NULL;
  ct->nextBro = NULL;
  ct->height = 0;

  return ct;
}

// 0: pas changer 1: changer              nouvelle hauteur = max(current_height, child_height + 1)
int update_height(CellTree *father, CellTree *child)
{
  if (!father || !child)
    return 0;
  int dbt_hauteur = father->height;

  if ((child->height + 1) > father->height)
    father->height = (child->height + 1);

  return !(father->height == dbt_hauteur);
}

// ajoute un child, update tous les noeuds ascendants(avant)
void add_child(CellTree *father, CellTree *child)
{
  if (!father || !child)
  {
    return;
  }

  // on annonce au fils qu'il a un père
  child->father = father;
  // on annonce au pere qu'il a un autre fils
  child->nextBro = father->firstChild;
  father->firstChild = child;

  CellTree *tmp_father, *tmp_child;
  tmp_father = father;
  tmp_child = child;
  // update de la hauteur
  while (tmp_father)
  {
    update_height(tmp_father, tmp_child);
    tmp_father = tmp_father->father;
    tmp_child = tmp_child->father;
  }
  update_height(father, child);

  return;
}

void print_node(CellTree *node)
{
  if (!node)
    return;
  printf("Hauteur: %2d %s\n", node->height, node->block->hash);
  return;
}

// on suppose que ct est la racine, pas de frère;
void print_tree(CellTree *ct)
{
  if (ct == NULL)
    return;

  CellTree *firstBro, *firstChild;
  firstBro = ct->nextBro;
  firstChild = ct->firstChild;

  // affichage de la cellule courant
  print_node(ct);

  // appel recursif sur le premier frere et le premier fils
  print_tree(firstChild);
  print_tree(firstBro);

  return;
}

void print_clean_tree(CellTree *ct, int max_height)
{
  if (ct == NULL)
    return;

  CellTree *firstBro, *firstChild;
  firstBro = ct->nextBro;
  firstChild = ct->firstChild;

  // affichage de la cellule courant
  for(int i = max_height; i > ct->height; i--) {
    printf("\t");
  }
  print_node(ct);

  // appel recursif sur le premier frere et le premier fils
  print_clean_tree(firstChild, max_height);
  print_clean_tree(firstBro, max_height);

  return;
}

void delete_tree_cell(CellTree *node)
{
  delete_block(node->block);
  free(node);
}

void delete_tree(CellTree *ct)
{
  if (!ct)
    return;

  CellTree *firstBro, *firstChild;

  firstBro = ct->nextBro;
  firstChild = ct->firstChild;

  // supression du blcok associe a ct
  delete_tree_cell(ct);
  // appel recursif sur le premier frere et le premier fils
  delete_tree(firstBro);
  delete_tree(firstChild);

  return;
}

// On suppose que cell est la racine
CellTree *highest_child(CellTree *cell)
{
  if (!cell || !cell->firstChild)
    return NULL;

  CellTree *res = cell->firstChild;
  int max_height = res->height;

  CellTree *cursor = res->nextBro;
  // on compare la hauteur de tous les fils et on renvoi celui qui a la plus grande
  while (cursor)
  {
    if (cursor->height > max_height)
    {
      max_height = cursor->height;
      res = cursor;
    }
    cursor = cursor->nextBro;
  }

  return res;
}

CellTree *last_node(CellTree *tree)
{
  if (!tree)
  {
    return NULL;
  }
  if (!tree->firstChild)
  {
    return tree;
  }

  CellTree *max_child = highest_child(tree);
  return last_node(max_child);
}

// Fusion en O(1) => On peut utiliser une liste doublement chainee, comme ca on aura l'adresses du derniner element de la premiere liste, sinon on range la liste simplement chainee dans une structure contenant un pointeur vers la tete et le dernier element de la liste chainee
CellProtected **merge_list_decla(CellProtected **l1, CellProtected **l2)
{
  if (l1 == NULL)
    return l2;
  if (l2 == NULL)
    return l1;

  CellProtected *cursor = *l1;
  while (cursor->next)
  {
    cursor = cursor->next;
  }
  cursor->next = *l2;

  return l1;
}

// on suppose que le premier appel est bien sur la racine --> pas besoin de se charger des freres
CellProtected **longest_list_decla(CellTree *tree)
{
  if (!tree)
    return NULL;

  CellProtected **res = (CellProtected **)malloc(sizeof(CellProtected *));
  if (!res)
    exit(12);

  *res = tree->block->votes;
  CellTree *max_child = highest_child(tree);
  CellProtected **to_merge = longest_list_decla(max_child);
  merge_list_decla(res, to_merge);

  return res;
}