#ifndef __KEYS_STRUCT__
#define __KEYS_STRUCT__

typedef struct Key {
  long val;
  long n;
} Key;

typedef struct Signature {
  long* tab;
  int size;
  char* content;
} Signature;

typedef struct Protected {
  Key* pKey;
  char* mess;
  Signature * sgn;
} Protected;

void init_key(Key* key, long val, long n);
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);

char* key_to_str(Key* key);
Key* str_to_key(char* str);

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);
int verify(Protected* pr);
char* protected_to_str(Protected *pr);
Protected* str_to_protected(char* str);

#endif
