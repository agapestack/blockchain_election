#include <stdio.h>
#include <stdlib.h>

#include "keys_struct.h"
#include "../../partie_1/ex1/miller_rabin.h"  

int main(void) {
  Key *pKey, *sKey, *testKey;
  long tab[100];
  Signature *sgn1, *sgn2;
  pKey = (Key*)malloc(sizeof(Key));
  sKey = (Key*)malloc(sizeof(Key));
  testKey = (Key*)malloc(sizeof(Key));

  if(!pKey || !sKey || !testKey)
    exit(12);

  init_pair_keys(pKey, sKey, 8, 16);
  printf("%ld\t%ld\n", pKey->n, pKey->val);

  printf("%s\n", key_to_str(pKey));
  testKey = str_to_key(key_to_str(pKey));
  printf("%s\n", key_to_str(testKey));

  for(int i=0; i < 100; i++) {
    tab[i] = rand_long(2, 100000);
  }
  sgn1 = init_signature(tab, 100);
  printf("%s\n", signature_to_str(sgn1));
  


  free(testKey);
  free(pKey);
  free(sKey);

  return 0;
}
