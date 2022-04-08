#ifndef _DETERMINER_GAGNANT_
#define _DETERMINER_GAGNANT_

#include "../ex5/linked_keys.h"

typedef struct hashcell
{
    Key *key;
    int val;
} HashCell;

typedef struct hashtable
{
    HashCell **tab;
    int size;
} HashTable;

HashCell *create_hashCell(Key *key);
int hash_function(Key *key, int size);
int find_position(HashTable *t, Key *key);
HashTable *create_hashTable(CellKey *keys, int size);
void delete_hashTable(HashTable *t);

#endif