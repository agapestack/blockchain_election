#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include "../../partie_2/ex3/keys_struct.h"

typedef struct cellKey {
  Key *data;
  struct cellKey *next;
} CellKey;

typedef struct cellProtected {
  Protected *data;
  struct cellProtected *next;
} CellProtected;

CellKey* create_cell_key(Key* key);
void inserer_key(CellKey** list_keys, Key* key);
CellKey** read_public_keys(char *fic); 

void print_list_keys(CellKey *LCK); 
void delete_cell_key(CellKey *ck); 
void delete_list_keys(CellKey **lk); 

CellProtected* create_cell_protected(Protected *pr);
void inserer_protected(CellProtected **list_protected, Protected *pr);
CellProtected** read_protected(char *fic);
void print_list_protected(CellProtected *lp);
void delete_cell_protected(CellProtected *c);
void delete_list_protected(CellProtected **cp);

#endif
