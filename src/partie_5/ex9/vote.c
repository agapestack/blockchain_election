#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./vote.h"

void submit_vote(Protected *p)
{
    FILE *fic = fopen(FILE_PENDING_VOTES, 'a');
    char *vote = p->declaration_vote;
    char *pKey_voter = key_to_str(p->pKey);

    fprintf(fic, "%s vote for %s\n", pKey_voter, vote);

    free(pKey_voter);
    fclose(fic);
}
void create_block(CellTree *tree, Key *author, int d)
{
    FILE *fic = fopen(FILE_PENDING_VOTES, 'r');
}
void add_block(int d, char *name)
{
}
