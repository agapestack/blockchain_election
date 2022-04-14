#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ex7/block.h"
#include "./tree.h"
#include "../../params.h"

CellTree* create_node(Block *b) {
  CellTree *ct = (CellTree*)malloc(sizeof(CellTree));
  if(!ct) 
    exit(12);

  ct->block = b;
  ct->father = NULL;
  ct->firstChild = NULL;
  ct->nextBro = NULL;
  ct->height = 0;

  return ct;
}

// nouvelle hauteur = max(current_height, child_height + 1)
int update_height(CellTree *father, CellTree *child) {
  int dbt_hauteur = father->height;

  if((child->height + 1) > father->height)
    father->height = (child->height + 1);

  return !(father->height == dbt_hauteur);
}

// ajoute un child, update tous les noeuds ascendants(avant)
void add_child(CellTree *father, CellTree *child) {
  // placement du fils
  if(father->firstChild == NULL) {
    father->firstChild = child;
  } else {
    CellTree *last_son = father->firstChild;
    while(last_son->nextBro != NULL) {
      last_son = last_son->nextBro;
    }
    last_son->nextBro = child;
  }
  
  // update de la hauteur
  CellTree *to_update = father;
  while(to_update) {
    update_height(to_update, child);
    to_update = to_update->father;
  }

  return;
} 

// on suppose que ct est la racine;
void print_tree(CellTree *ct) { 
  CellTree *cursor = ct;

}

void delete_node(CellTree *node) {
  
}

void delete_tree(CellTree *ct) {

}
