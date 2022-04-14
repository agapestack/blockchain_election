#ifndef __VOTE__
#define __VOTE__

#include "../../params.h"
#include "../../partie_4/ex7/block.h"
#include "../../partie_4/ex8/tree.h"

void submit_vote(Protected *p);
void create_block(CellTree *tree, Key *author, int d);
void add_block(int d, char *name);


#endif