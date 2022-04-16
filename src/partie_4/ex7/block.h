#ifndef __BLOCK__
#define __BLOCK__

#include "../../partie_2/ex3/keys_struct.h"
#include "../../partie_3/ex5/linked_list.h"

typedef struct block {
  Key *author;  // pKey du createur
  CellProtected *votes; // liste de declaration de vote
  unsigned char* hash; // valeur hachee du bloc
  unsigned char* previous_hash;  // valeur hachee du bloc precedent 
  int nonce;  // preuve de travail
} Block;

void delete_block(Block *b);
void write_block(char* file_name, Block *b);
Block* read_block(char *file_name);
char* block_to_str(Block *block);

char* hash_sha256(char* str);
void compute_proof_of_work(Block *B, int d);
int verify_block(Block *b, int d);



#endif
