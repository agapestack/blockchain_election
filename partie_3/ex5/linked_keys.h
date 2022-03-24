#ifndef __LINKED_KEYS__
#define __LINKED_KEYS__

#include "../../partie_2/ex3/keys_struct.h"

typedef struct cellKey {
  Key *data;
  struct cellKey* next;
} CellKey;

#endif
