#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <openssl/sha.h>

#include "./block.h"
#include "../../partie_2/ex3/keys_struct.h"
#include "../../partie_3/ex5/linked_list.h"
#include "../../params.h"

void write_block(char *file_name, Block *b)
{
  FILE *fic = fopen(file_name, "w");
  if (!fic)
    exit(12);

  char *key_str;
  key_str = key_to_str(b->author);
  fprintf(fic, "%s ", key_str);
  free(key_str);

  fprintf(fic, "%s ", b->hash);
  fprintf(fic, "%s ", b->previous_hash);
  fprintf(fic, "%d ", b->nonce);

  CellProtected *cursor = b->votes;

  while (cursor)
  {
    Protected *pr = cursor->data;
    char *pr_str = protected_to_str(pr);
    // @ nous sert de delimiter
    fprintf(fic, "%s ", pr_str);
    free(pr_str);
    cursor = cursor->next;
  }
  fprintf(fic, "\n");

  fclose(fic);

  return;
}

Block *read_block(char *file_name)
{
  FILE *fic = fopen(file_name, "r");
  if (!fic)
    exit(12);

  char buffer_bloc[65536], author_str[128], votes_str[64512];
  unsigned char hash_str[256], previous_hash_str[256];
  int nonce;

  Block *b = (Block *)malloc(sizeof(Block));
  b->author = NULL;
  b->votes = NULL;
  if (!b)
    exit(12);

  // normalement qu'un bloc a lire --> besoin du while?
  while (fgets(buffer_bloc, 65536, fic))
  {
    sscanf(buffer_bloc, "%s %s %s %d %s", author_str, hash_str, previous_hash_str, &nonce, votes_str);

    Key *key = str_to_key(author_str);
    unsigned char *hash, *previous_hash;
    hash = strdup(hash_str);
    previous_hash = strdup(previous_hash_str);

    // obtention de la liste de declaration de vote
    char delimiter[2] = "@";
    char *pr_token;

    pr_token = strtok(votes_str, delimiter);
    Protected *pr = str_to_protected(pr_token);
    CellProtected *list_pr = create_cell_protected(pr);

    while (pr_token != NULL)
    {
      // obtention de la prochaine string contenant une declaration
      pr_token = strtok(NULL, delimiter);
      Protected *pr2 = str_to_protected(pr_token);
      CellProtected *nouv = create_cell_protected(pr);
      nouv->next = list_pr;
      list_pr = nouv;
    }

    b->author = key;
  }
}

char *block_to_str(Block *block)
{
  char buffer[65536];

  char *key_str = key_to_str(block->author);
  sprintf(buffer, "%s %s ", key_str, block->previous_hash);

  CellProtected *cursor = block->votes;
  while (cursor)
  {
    char *pr_str = protected_to_str(cursor->data);
    sprintf(buffer, "%s@", pr_str);
    free(pr_str);
    cursor = cursor->next;
  }

  sprintf(buffer, " %d", block->nonce);

  char *res;
  res = strdup(buffer);

  return res;
}

unsigned char *hash_sha256(char *str)
{
  unsigned char *tmp = SHA256(str, strlen(str), 0);
  unsigned char *res;

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    sprintf(res + 2 * i, "%02x", tmp[i]);
  }

  return res;
}

void compute_proof_of_work(Block *B, int d)
{
  int nonce = 0;
  while (1)
  {
    B->nonce = nonce;
    char *str_block = block_to_str(B);
    unsigned char *hash_block = hash_sha256(str_block);

    // verification du nombre de 0, --> MOYEN DETRE PLUS RAPIDE EN REPRESENTATION BINAIRE???
    int compteur = 0;
    for (int i = 0; i < d; i++)
    {
      if (hash_block[i] == '0')
      {
        compteur += 1;
      }
    }

    // si on a le bon nombre de 0 on quitte la boucle, on a trouve la bonne valeur de nonce
    if (compteur == d)
      break;

    nonce += 1;
  }
}

int verify_block(Block *b, int d)
{
  char *str_block = block_to_str(b);
  unsigned char *hash_block = hash_sha256(str_block);

  for(int i=0; i < d; i++) {
    if(hash_block[i] != '0')
      return 0;
  }

  return 1;
}