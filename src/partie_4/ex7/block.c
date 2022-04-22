#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <openssl/sha.h>

#include "./block.h"
#include "../../partie_2/ex3/keys_struct.h"
#include "../../partie_3/ex5/linked_list.h"
#include "../../params.h"

void delete_block(Block *b)
{
  free(b->author);
  free(b->hash);
  free(b->previous_hash);

  while (b->votes)
  {
    CellProtected *tmp = b->votes;
    b->votes = b->votes->next;
    delete_cell_protected(tmp);
  }
  free(b);
}

void delete_block_v2(Block *b)
{
  free(b->hash);
  free(b->previous_hash);

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
  printf("DEBUT READ BLOCK SUR %s\n", file_name);
  FILE *fic = fopen(file_name, "r");
  Block *b = (Block *)malloc(sizeof(Block));
  if (!b || !fic)
    exit(12);

  char buffer[512];
  // recuperation cle
  fgets(buffer, 512, fic);
  printf("%s\n", buffer);
  Key *key = str_to_key(buffer);

  // recuperation hash
  unsigned char *hash = NULL;
  fgets(buffer, 512, fic);
  buffer[strlen(buffer) - 1] = '\0';
  // printf("buffer %s\n", buffer);
  if (buffer)
  {
    hash = (unsigned char *)malloc(sizeof(unsigned char) * (SHA256_DIGEST_LENGTH + 1));
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
      hash[i] = buffer[i];
    }
    hash[SHA256_DIGEST_LENGTH] = '\0';
  }

  // recuperation previous_hash
  fgets(buffer, 512, fic);
  buffer[strlen(buffer) - 1] = '\0';
  unsigned char *previous_hash = NULL;
  if (buffer)
  {
    previous_hash = (unsigned char *)malloc(sizeof(unsigned char) * (SHA256_DIGEST_LENGTH + 1));
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
      previous_hash[i] = buffer[i];
    }
    previous_hash[SHA256_DIGEST_LENGTH] = '\0';
  }

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
  printf("FIN READ BLOCK\n");
  return b;
}

char *block_to_str(Block *block)
{
  char buffer[5096];

  char *key_str = key_to_str(block->author);
  sprintf(buffer, "%s\n%s\n", key_str, block->previous_hash);
  free(key_str);

  CellProtected *cursor = block->votes;
  while (cursor)
  {
    char *pr_str = protected_to_str(cursor->data);
    sprintf(buffer + strlen(buffer) + 1, "%s\n", pr_str);
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

char *hash_sha256(char *str)
{
  char *res = (char *)malloc(sizeof(char) * 256);
  unsigned char *tmp = SHA256(str, strlen(str), 0);

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    sprintf(res + 2 * i, "%02x", tmp[i]);
  }

  return res;
}

void compute_proof_of_work(Block *B, int d)
{
  if (!B)
    return;
  // generation d'une chaine pour la comparaison
  char *str_zero = (char *)malloc(sizeof(char) * (d + 1));
  for (int i = 0; i < d; i++)
  {
    str_zero[i] = '0';
  }
  str_zero[d] = '\0';

  // si la valeur du hash est deja satifaisante ne rien faire
  if (B->hash && strncmp(str_zero, B->hash, d) == 0 && B->nonce)
  {
    printf("\n");
    free(str_zero);
    return;
  }

  // pour test verify block
  // printf("VERIFY BLOCK = %d\n", verify_block(B, d));

  int nonce = 0;
  while (1)
  {
    B->nonce = nonce;
    char *block_str = block_to_str(B);
    unsigned char *new_hash = hash_sha256(block_str);
    free(block_str);
    // printf("%s\n", new_hash);
    free(B->hash);
    B->hash = new_hash;

    // verification du nombre de 0 au debut de val_hash_block
    if (strncmp(str_zero, B->hash, d) == 0)
    {
      printf("%s\n", B->hash);
      // pour test verify block
      // printf("VERIFY BLOCK = %d\n", verify_block(B, d));
      free(str_zero);
      return;
    }

    nonce += 1;
  }
}

// retourne 1 si le block est valide 0 sinon
int verify_block(Block *b, int d)
{
  int res;
  char *str_block = block_to_str(b);
  unsigned char *hash_block = hash_sha256(str_block);

  char *str_zero = (char *)malloc(sizeof(char) * d);
  for (int i = 0; i < d; i++)
  {
    str_zero[i] = '0';
  }

  res = strncmp(str_zero, b->hash, d);

  free(str_block);
  free(hash_block);
  free(str_zero);

  return res;
}