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
  // placement du fils
  if (father->firstChild == NULL)
  {
    father->firstChild = child;
  }
  else
  {
    CellTree *last_son = father->firstChild;
    while (last_son->nextBro != NULL)
    {
      last_son = last_son->nextBro;
    }
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

// on suppose que ct est la racine;
void print_tree(CellTree *ct)
{
  if (ct == NULL)
    return;

  CellTree *cursor = ct;
  char *block = block_to_str(cursor->block);

  printf("Hauteur du bloc %s = %d\n", block, cursor->height);
  CellTree *child = cursor->firstChild;
  print_tree(child);

  CellTree *bros = child->nextBro;
  while (bros)
  {
    char *bros_block = block_to_str(bros->block);
    printf("Hauteur du bloc fere %s = %d\n", bros_block, bros->height);
    bros = bros->nextBro;
    free(bros_block);
  }

  free(block);
}

void delete_node(CellTree *node)
{
  delete_block(node->block);
  free(node);
}

// on suppose que ct est la racine;
void delete_tree(CellTree *ct)
{
  CellTree *node = ct;
  if (node == NULL)
  {
    return;
  }

  CellTree *child = node->firstChild;
  delete_tree(child);

  CellTree *bros = child->nextBro;
  while (bros)
  {
    CellTree *tmp = bros;
    bros = bros->nextBro;
    delete_node(bros);
  }
  delete_node(child);
  return;
}

// On suppose que cell est la racine
CellTree *highest_child(CellTree *cell)
{
  CellTree *child = cell->firstChild;
  int mx_height = child->height;
  CellTree *res;
  res = NULL;

  CellTree *bros = child->nextBro;
  while (bros)
  {
    if (bros->height > mx_height)
    {
      mx_height = bros->height;
      res = bros;
    }
    bros = bros->nextBro;
  }

  return res;
}

CellTree *last_node(CellTree *tree)
{
  if (tree == NULL)
  {
    return tree->father;
  }
  CellTree *mx_child = highest_child(tree);

  CellTree *child = mx_child->firstChild;
  CellTree *res = last_node(child);

  return res;
}