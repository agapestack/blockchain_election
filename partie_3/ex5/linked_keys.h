#ifndef __LINKED_KEYS__
#define __LINKED_KEYS__

#include "../../partie_2/ex3/keys_struct.h"

typedef struct cellKey {
  Key *data;
  struct cellKey* next;
} CellKey;

typedef struct cellProtected{
  Protected* data;
  struct cellProtected* next;
} CellProtected;


CellKey* create_cell_key(Key* key);
CellKey* inserer_cell_tete(Key* key, CellKey *next);

CellKey* read_public_keys(char* nomfic);
void print_list_keys(CellKey* c);
void delete_cell_key(CellKey* c);
void free_list_key(CellKey *c);

CellProtected* inserer_list_protected(Protected *pr, CellProtected *next);
CellProtected* create_cell_protected(Protected *pr);
CellProtected* read_declarations(char* nomfic);
void print_list_protected(CellProtected *pr);
void delete_cell_protected(CellProtected *pr);
void free_cell_protected(CellProtected *pr);

#endif
