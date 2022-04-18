#ifndef __VOTE__
#define __VOTE__

#include "../../params.h"
#include "../../partie_4/ex7/block.h"
#include "../../partie_4/ex8/tree.h"
#include "../../partie_3/ex6/hash.h"
#include "../../partie_2/ex3/keys_struct.h"
#include "../../partie_2/ex4/generate_data.h"
#include <openssl/sha.h>

void submit_vote(Protected *p);
void create_block(CellTree *tree, Key *author, int d);
CellTree *init_tree(Key *author, int d);
void add_block(int d, char *name);
char* generate_uuid();
CellTree* read_tree();
Key* compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);


#endif