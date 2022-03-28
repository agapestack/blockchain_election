#ifndef __KEYS_STRUCT__
#define __KEYS_STRUCT__

typedef struct Key {
  // u ou s
  long val;
  // n = p*q
  long n;
} Key;

typedef struct Signature {
  // content == message que Bob a chiffré avec sa clé secrète pour pouvoir être authentifier
  long *content;
  int size;
  // mess == Message que Bob a chiffré avec la clé publique d'Alice
  char *mess;
} Signature;

typedef struct Protected {
  Key* pKey;
  // message pas chiffré
  char* declaration_vote;
  Signature *sgn;
} Protected;

void free_signature(Signature *s);
void free_protected(Protected *p);

void init_key(Key* key, long val, long n);
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);

char* key_to_str(Key* key);
Key* str_to_key(char* str);

Signature* init_signature(long* content, int size);
Signature* sign(char* mess, Key* sKey);
char *signature_to_str(Signature *sgn);
Signature *str_to_signature(char *str);

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);
int verify(Protected* pr);
char* protected_to_str(Protected *pr);
Protected* str_to_protected(char* str);

void print_long_vector(long *result, int size);

#endif
