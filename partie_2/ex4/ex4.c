#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../ex3/keys_struct.h"

void generate_random_data(int nv, int nc)
{
}

int main(void)
{

  srand(time(NULL));

  // test init key
  Key *pKey = malloc(sizeof(Key));
  Key *sKey = malloc(sizeof(Key));

  init_pair_keys(pKey, sKey, 3, 7);
  printf("pKey : %lx  %lx\n", pKey->val, pKey->n);
  printf("sKey : %lx, %lx\n", sKey->val, sKey->n);

  // test key serialization
  char *chaine = key_to_str(pKey);
  printf("keytostr: % s\n", chaine);
  Key *k = str_to_key(chaine);
  printf("strtokey: %lx, %lx \n", k->val, k->n);

  // candidate keys
  Key *pKeyC = malloc(sizeof(Key));
  Key *sKeyC = malloc(sizeof(Key));
  init_pair_keys(pKeyC, sKeyC, 3, 7);

  // declaration
  char *mess = key_to_str(pKeyC);
  printf("% s vote pour % s \n", key_to_str(pKey), mess);
  Signature *sgn = sign(mess, sKey);
  printf("signature: ");
  print_long_vector(sgn->content, sgn->size);
  chaine = signature_to_str(sgn);
  printf("signaturetostr: %s\n", chaine);
  sgn = str_to_signature(chaine);
  printf("strtosignature: ");
  print_long_vector(sgn->content, sgn->size);

  // test protected
  Protected *pr = init_protected(pKey, mess, sgn);

  if (verify(pr))
  {
    printf("Signature valide!\n");
  }
  else
  {
    printf("Signature invalide\n");
  }
  chaine = protected_to_str(pr);
  printf("protectedtostr: %s\n", chaine);
  pr = str_to_protected(chaine);
  printf("strtoprotected: % s % s % s\n", key_to_str(pr->pKey), pr->mess, signature_to_str(pr->sgn));

  free(pKey);
  free(sKey);
  free(pKeyC);
  free(sKeyC);

  return 0;
}
