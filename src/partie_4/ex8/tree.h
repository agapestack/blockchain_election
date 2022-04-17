#ifndef __TREE__
#define __TREE__

#include "../../params.h"
#include "../ex7/block.h"
#include "../../partie_2/ex4/generate_data.h"

typedef struct block_tree_cell
{
  Block *block;
  struct block_tree_cell *father;
  struct block_tree_cell *firstChild;
  struct block_tree_cell *nextBro;
  int height;
} CellTree;

CellTree *create_node(Block *b);

int update_height(CellTree *father, CellTree *child);
void add_child(CellTree *father, CellTree *child);
void print_node(CellTree *node);
void print_tree(CellTree *ct);
void print_clean_tree(CellTree *ct, int max_height);
void delete_tree_cell(CellTree *node);
void delete_tree(CellTree *ct);

CellTree *highest_child(CellTree *cell);
CellTree *last_node(CellTree *tree);

CellProtected **merge_list_decla(CellProtected **l1, CellProtected **l2);

#endif
