#include <stdio.h>
#include <stdlib.h>

#include "linked_keys.h"

CellKey* create_cell_key(Key* key) {
  CellKey *c = (CellKey*)malloc(sizeof(CellKey));

  c->data = key;
  c->next = NULL;

  return c;
}

CellKey* ajout_cell_tete(Key* key, CellKey* next) {
  CellKey *new = create_cell_key(key);

  new->next = next;

  return new;
}

CellKey* read_public_keys(char* nomfic) {
  
}