#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys_struct.h"
#include "../../partie_1/ex2/keys.h"
#include "../../partie_1/ex1/miller_rabin.h"
#include "../../params.h"

void init_key(Key *key, long val, long n)
{
  key->val = val;
  key->n = n;

  return;
}

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size) {
  long p = random_prime_number(low_size, up_size, NB_VALIDATION_MILLER);
  long q = random_prime_number(low_size, up_size, NB_VALIDATION_MILLER);
  long n, s, u;

  generate_key_values(p, q, &n, &s, &u);

  init_key(pKey, s, n);
  init_key(sKey, u, n);

  return;
}

char* key_to_str(Key* key) {
  char *str = malloc(sizeof(char) * 512);
  if(!str) 
    exit(12);

  sprintf(str, "(%lx, %lx)", key->val, key->n);

  return str;
}

Key* str_to_key(char* str) {
  Key *res = (Key*)malloc(sizeof(Key));

  if(!res) 
    exit(12);

  sscanf(str, "(%lx, %lx)", &res->val, &res->n);

  return res;
}

Signature* init_signature(long* content, int size) {
  Signature *res = (Signature*)malloc(sizeof(Signature));
  if(!res) 
    exit(12);

  res->content = content;
  res->size = size;

  return res;
}

Signature* sign(char* mess, Key* sKey) {
  Signature *res = init_signature(encrypt(mess, sKey->val, sKey->n), strlen(mess));
  res->mess = mess;
  
  return res;
}

char *signature_to_str(Signature *sgn)
{
  char *result = malloc(10 * sgn->size * sizeof(char));
  result[0] = '#';
  int pos = 1;
  char buffer[156];
  for (int i = 0; i < sgn->size; i++)
  {
    sprintf(buffer, "%lx", sgn->content[i]);
    for (int j = 0; j < strlen(buffer); j++)
    {
      result[pos] = buffer[j];
      pos = pos + 1;
    }
    result[pos] = '#';
    pos = pos + 1;
  }
  result[pos] = '\0';
  result = realloc(result, (pos + 1) * sizeof(char));
  return result;
}

Signature *str_to_signature(char *str)
{
  int len = strlen(str);
  long *mess = (long *)malloc(sizeof(long) * len);
  int num = 0;
  char buffer[256];
  int pos = 0;

  for (int i = 0; i < len; i++)
  {
    if (str[i] != '#')
    {
      buffer[pos] = str[i];
      pos = pos + 1;
    }
    else
    {
      if (pos != 0)
      {
        buffer[pos] = '\0';
        sscanf(buffer, "%lx", &(mess[num]));
        num = num + 1;
        pos = 0;
      }
    }
  }

  mess = realloc(mess, num * sizeof(long));
  
  return init_signature(mess, num);
}

Protected* init_protected(Key* pKey, char *mess, Signature* sgn) {
  Protected *res = (Protected*)malloc(sizeof(Protected));
  if(!res)
    exit(12);

  res->pKey = pKey;
  res->declaration_vote = mess;
  res->sgn = sgn;

  return res;
} 

int verify(Protected* pr) {
  char *dechiffre = malloc(sizeof(char) * 256);
  if(!dechiffre) 
    exit(12);
  dechiffre = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n);

  return strcmp(dechiffre, pr->declaration_vote);
}

char* protected_to_str(Protected *pr) {
  char *res = malloc(sizeof(char) * 512);
  sprintf("%s %s %s", key_to_str(pr->pKey), pr->declaration_vote, signature_to_str(pr->sgn));
  return res;
}

Protected* str_to_protected(char* str) {

  // Protected *res = (Protected*)malloc(sizeof(Protected));
  // sscanf(str, "%s %s %s", str_to_key())
}