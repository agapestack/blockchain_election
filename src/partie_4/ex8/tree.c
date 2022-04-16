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

// nouvelle hauteur = max(current_height, child_height + 1)
int update_height(CellTree *father, CellTree *child)
{
  int dbt_hauteur = father->height;

  if ((child->height + 1) > father->height)
    father->height = (child->height + 1);

  return !(father->height == dbt_hauteur);
}

// ajoute un child, update tous les noeuds ascendants(avant)
void add_child(CellTree *father, CellTree *child)
{
  if(!father || !child)
    return;
  // placement du fils
  if (father->firstChild == NULL)
  {
    father->firstChild = child;
  }
  else
  {
    // obtention du dernier fils
    CellTree *last_son = father->firstChild;
    while (last_son->nextBro != NULL)
    {
      last_son = last_son->nextBro;
    }
    // placement du fils a la fin de la liste chainee des fils
    last_son->nextBro = child;
  }

  // update de la hauteur
  CellTree *to_update = father;
  while (to_update)
  {
    update_height(to_update, child);
    to_update = to_update->father;
  }

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

  // affichage de la cellule courante
  printf("Hauteur: %5d\tHash: %s\n", ct->height, ct->block->hash);

  // appel recursif sur le premier frere et le premier fils
  print_tree(firstChild);
  print_tree(firstBro);

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
  CellTree *child = cell->firstChild;
  int max_height = child->height;
  CellTree *res = NULL;

  // on compare la hauteur de tous les fils et on renvoi celui qui a la plus grande
  while (child)
  {
    if (child->height > max_height)
    {
      max_height = child->height;
      res = child;
    }
    child = child->nextBro;
  }

  return res;
}

CellTree *last_node(CellTree *tree)
{
  if (!tree)
  {
    return NULL;
  }
  if (tree->firstChild == NULL)
  {
    return tree;
  }
  CellTree *max_child = highest_child(tree);

  CellTree *res = last_node(max_child->firstChild);

  return res;
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