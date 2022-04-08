#ifndef __HASH__
#define __HASH__

#include "../ex5/linked_list.h"

typedef struct hashcell {
  Key *key;
  int val;
} HashCell;

typedef struct hashtable {
  HashCell **tab;
  int size;
} HashTable;

void verify_list_protected(CellProtected **cp);

HashCell *create_hashcell(Key* key);
int hash_function(Key *key, int size);
int find_position(HashTable *t, Key* key);
HashTable* create_hashtable(CellKey* key, int size); 
void delete_hashtable(HashTable *t);

Key* compute_winner(CellProtected* decl, CellKey *candidates, CellKey* voters, int sizeC, int sizeV);

#endif
