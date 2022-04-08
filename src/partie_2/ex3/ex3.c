#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "keys_struct.h"
#include "../../partie_1/ex1/miller_rabin.h"
#include "../../params.h"

int main(void)
{

  srand(time(NULL));

  printf("----------DEBUT TEST EX3----------\n");
  for (int i = 0; i < NB_TEST_EX3; i++)
  {
    // TEST INIT_PAIR_KEYS
    Key *pKey = malloc(sizeof(Key));
    Key *sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, LOW_SIZE, UP_SIZE);
    printf("pKey: %lx, %lx\n", pKey->val, pKey->n);
    printf("sKey: %lx, %lx\n", sKey->val, sKey->n);

    // KEY SERIALIZATION TESTING
    char *chaine = key_to_str(pKey);
    Key *key_tmp;
    key_tmp = str_to_key(chaine);
    printf("key_to_str : %s\n", chaine);
    printf("str_to_key : %lx, %lx\n", key_tmp->val, key_tmp->n);
    free(key_tmp);
    free(chaine);

    // SIGNATURE
    // generation de cle d'un candidat
    Key *pKeyC = malloc(sizeof(Key));
    Key *sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, LOW_SIZE, UP_SIZE);

    char *str_pKeyC, *str_pKey;
    str_pKeyC = key_to_str(pKeyC);
    str_pKey = key_to_str(pKey);
    printf("%s VOTE POUR %s\n", str_pKey, str_pKeyC);

    Signature *sgn = sign(str_pKeyC, sKey);
    printf("Signature:\t\t");
    print_long_vector(sgn->content, sgn->size);
    char *str_sgn = signature_to_str(sgn);
    printf("str_to_signature:      %s\n", str_sgn);
    Signature *sgn2 = str_to_signature(str_sgn);
    printf("signature_to_str: \t");
    print_long_vector(sgn2->content, sgn2->size);

    // PROTECTED
    printf("_____PROTECTED_____\n");
    Protected *pr = init_protected(pKey, str_pKeyC, sgn);
    if (verify(pr))
    {
      printf("--Signature valide--\n");
    }
    else
    {
      printf("--Signature non valide--\n");
    }

    char *str_pr = protected_to_str(pr);
    printf("protected_to_str:\t%s\n", str_pr);
    Protected *pr2 = str_to_protected(str_pr);
    char *pKey_pr2, *sgn_pr2;
    pKey_pr2 = key_to_str(pr2->pKey);
    sgn_pr2 = signature_to_str(pr2->sgn);
    printf("str_to_protected:\t%s %s %s", pKey_pr2, pr2->declaration_vote, sgn_pr2);



    free(sKey);
    free(pKeyC);
    free(sKeyC);
    free(str_pKey);
    free(str_sgn);
    free(pKey_pr2);
    free(sgn_pr2);
    free(str_pr);
    free_signature(sgn2);
    free_protected(pr);
    free_protected(pr2);

    printf("\n\n");
  }

  printf("----------FIN TEST EX3----------\n\n\n");

  return 0;
}