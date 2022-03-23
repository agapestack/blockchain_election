#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "keys_struct.h"
#include "../../partie_1/ex1/miller_rabin.h"

int main(void)
{

  srand(time(NULL));

  Key *pKey = malloc(sizeof(Key));
  Key *sKey = malloc(sizeof(Key));
  init_pair_keys(pKey, sKey, 3, 7);
  printf("pKey: %ld, %ld\n", pKey->val, pKey->n);
  printf("pKey: %lx, %lx\n", pKey->val, pKey->n);

  printf("sKey: %ld, %ld\n", sKey->val, sKey->n);
  printf("sKey: %lx, %lx\n", sKey->val, sKey->n);

  char *chaine = key_to_str(pKey);
  printf("key_to_str : %s\n", chaine);
  Key *k = str_to_key(chaine);
  printf("str_to_key : %lx, %lx\n", k->val, k->n);

  Key *pKeyC = malloc(sizeof(Key));
  Key *sKeyC = malloc(sizeof(Key));
  init_pair_keys(pKeyC, sKeyC, 3, 7);

  // Declaration:
  char *mess = key_to_str(pKeyC);
  printf("%s vote pour %s \n", key_to_str(pKey), mess);
  Signature *sgn = sign(mess, sKey);
  printf("signature: ");
  print_long_vector(sgn->content, sgn->size);
  chaine = signature_to_str(sgn);
  printf("signature_to_str: %s \n", chaine);
  sgn = str_to_signature(chaine);
  printf("str_to_signature: \n");
  print_long_vector(sgn->content, sgn->size);

  // Testing protected:
  Protected *pr = init_protected(pKey, mess, sgn);
  // Verification:
  if (verify(pr))
  {
    printf("Signature valide\n");
  }
  else
  {
    printf("Signature non valide\n");
  }
  // OK
  chaine = protected_to_str(pr);
  printf("protected_to_str: %s \n", chaine);
  pr = str_to_protected(chaine);
  printf("str_to_protected: %s %s %s\n", key_to_str(pr->pKey), pr->declaration_vote, signature_to_str(pr->sgn));

  free(pKey);
  free(sKey);
  free(pKeyC);
  free(sKeyC);
  free(chaine);
  free(sgn->content);
  free(sgn->mess);
  free(sgn);
  free(k);
  free(mess);
  free(pr->declaration_vote);
  free(pr->pKey);
  free(pr->sgn->content);
  free(pr->sgn->mess);
  free(pr);

  return 0;
}
