#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <openssl/sha.h>

#include "./block.h"
#include "../../partie_2/ex3/keys_struct.h"
#include "../../partie_3/ex5/linked_list.h"
#include "../../params.h"

void delete_block(Block *b) {
  free(b->author);
  free(b->hash);
  free(b->previous_hash);
  while(b->votes) {
    CellProtected *tmp = b->votes;
    b->votes = b->votes->next;
    delete_cell_protected(tmp);
  }
  free(b);
}

void write_block(char *file_name, Block *b)
{
  FILE *fic = fopen(file_name, "w");
  if (!fic)
    exit(12);

  char *key_str;
  key_str = key_to_str(b->author);
  fprintf(fic, "%s\n", key_str);
  free(key_str);

  fprintf(fic, "%s\n", b->hash);
  fprintf(fic, "%s\n", b->previous_hash);
  fprintf(fic, "%d\n", b->nonce);

  CellProtected *cursor = b->votes;

  while (cursor)
  {
    Protected *pr = cursor->data;
    char *pr_str = protected_to_str(pr);
    fprintf(fic, "%s\n", pr_str);
    free(pr_str);
    cursor = cursor->next;
  }
  fprintf(fic, "\n");

  fclose(fic);

  return;
}

// Renvoie le block correspondant au fichier avec une liste chaine de declaration de votes inverser car on insere en tete dans notre liste chainee (ordre inversee mais meme donne donc pas de probleme)
Block *read_block(char *file_name)
{
  FILE *fic = fopen(file_name, "r");
  if (!fic)
    exit(12);
  Block *b = (Block *)malloc(sizeof(Block));
  if(!b)
    exit(12);
  char buffer[512];


  // recuperation cle
  fgets(buffer, 512, fic);
  Key *key = str_to_key(buffer);

  // recuperation hash
  fgets(buffer, 512, fic);
  unsigned char *hash = strdup(buffer);
  hash[strlen(hash) - 1] = '\0';

  // recuperation previous_hash
  fgets(buffer, 512, fic);
  unsigned char *previous_hash = strdup(buffer);
  previous_hash[strlen(previous_hash) - 1] = '\0';

  // recuperation nonce
  fgets(buffer, 512, fic);
  int nonce;
  sscanf(buffer, "%d", &nonce);

  b->author = key;
  b->hash = hash;
  b->previous_hash = previous_hash;
  b->nonce = nonce;

  CellProtected **res = (CellProtected **)malloc(sizeof(CellProtected *));
  *res = NULL;

  Protected *pr = NULL;
  // recuperation de la liste chainee de declaration
  while (fgets(buffer, 512, fic) != NULL)
  {
    char pKey_str[128], decla_str[128], sgn_str[256];
    // obtention des chaines bien correspondantes à la donnee souhaite (eviter pb de \0 \n etc)
    sscanf(buffer, "%s %s %s", pKey_str, decla_str, sgn_str);
    sprintf(buffer, "%s %s %s", pKey_str, decla_str, sgn_str);

    pr = str_to_protected(buffer);
    inserer_protected(res, pr);
  }

  b->votes = *res;
  free(res);

  fclose(fic);
  return b;
}

char *block_to_str(Block *block)
{
  char buffer[65536];

  char *key_str = key_to_str(block->author);
  sprintf(buffer, "%s\n%s\n", key_str, block->previous_hash);

  free(key_str);

  CellProtected *cursor = block->votes;
  while (cursor)
  {
    char *pr_str = protected_to_str(cursor->data);

    sprintf(buffer + strlen(buffer), "%s\n", pr_str);
    free(pr_str);
    cursor = cursor->next;
  }

  char str_nonce[256];
  sprintf(str_nonce, "%d", block->nonce);
  strcat(buffer, str_nonce);

  char *res;
  res = strdup(buffer);
  return res;
}

unsigned char *hash_sha256(char *str)
{
  unsigned char *res = SHA256(str, strlen(str), 0);

  // pour retourner en format classique (non hexa) l'énoncé était incompréhensible...
  // unsigned char *res = (char *)malloc(sizeof(char) * 255);
  // int offset = 0;
  // for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  // {
  //   offset += snprintf(res + 2 * i, 255 - offset, "%02x", tmp[i]);
  // }

  return res;
}

void compute_proof_of_work(Block *B, int d)
{
  int nonce = 0;

  while(1) {
    int compteur = 0;

    B->nonce = nonce;
    char *str_block = block_to_str(B);
    char *val_hash_block = hash_sha256(str_block);
    // free(B->previous_hash);
    B->previous_hash = B->hash;
    B->hash = val_hash_block;

    // verification du nombre de 0 au debut de val_hash_block
    for(int i=0; i < d; i++) {
      if(val_hash_block[i] != '0') {
        break;
      } else {
        compteur += 1;
      }
    }

    free(str_block);
    if(compteur == d) {
      return;
    }

    nonce += 1;
  }
}

int verify_block(Block *b, int d)
{
  char *str_block = block_to_str(b);
  unsigned char *hash_block = hash_sha256(str_block);

  for (int i = 0; i < d; i++)
  {
    if (hash_block[i] != '0')
      return 0;
  }

  return 1;
}