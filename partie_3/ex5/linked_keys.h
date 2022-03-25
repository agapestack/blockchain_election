#ifndef __LINKED_KEYS__
#define __LINKED_KEYS__

#include "../../partie_2/ex3/keys_struct.h"

typedef struct cellKey {
  Key *data;
  struct cellKey* next;
} CellKey;

CellKey* create_cell_key(Key* key);
CellKey* ajout_cell_tete(Key* key, CellKey *next);

CellKey* read_public_keys(char* nomfic);

#endif
