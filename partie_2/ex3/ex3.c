#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "keys_struct.h"
#include "../../partie_1/ex1/miller_rabin.h"

int main(void)
{

  srand(time(NULL));

  // Testing Init Keys
  Key *pKey = malloc(sizeof(Key));
  Key *sKey = malloc(sizeof(Key));
  init_pair_keys(pKey, sKey, 3, 7);
  printf("pKey: %ld, %ld\n", pKey->val, pKey->n);
  printf("pKey: %lx, %lx\n", pKey->val, pKey->n);

  printf("sKey: %ld, %ld\n", sKey->val, sKey->n);
  printf("sKey: %lx, %lx\n", sKey->val, sKey->n);


  // // Testing Key Serialization
  char *chaine = key_to_str(pKey);
  Key *key_tmp;
  printf("key_to_str : %s\n", chaine);
  key_tmp = str_to_key(chaine); 
  printf("str_to_key : %lx, %lx\n", key_tmp->n, key_tmp->val);
  

  // //Testing signature
  Key *pKeyC = malloc(sizeof(Key));
  Key *sKeyC = malloc(sizeof(Key));
  init_pair_keys(pKeyC, sKeyC, 3, 7);

  // // Declaration:
  char* mess = key_to_str(pKeyC);
  // free(mess);

  char *char_tmp;
  char_tmp = key_to_str(pKey);
  printf("%s vote pour %s \n", char_tmp, mess);
  
  Signature *sgn = sign(mess, sKey);

  print_long_vector(sgn->content, sgn->size);

  char *tmp = signature_to_str(sgn);
  printf("signature_to_str: %s \n", tmp);
  
  Signature *sgn2 = str_to_signature(chaine);
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

  char *temp = protected_to_str(pr);
  printf("protected_to_str: %s \n", temp);
  free(temp);


  //  TODO MEMORY LEAK HERE
  // pr = str_to_protected(chaine);

  // char *c_tmp1 = key_to_str(pr->pKey);
  // char *c_tmp2 = signature_to_str(pr->sgn);
  // printf("str_to_protected: %s %s %s \n", c_tmp1, pr->declaration_vote, c_tmp2);
  // free(c_tmp2);
  // free(c_tmp1);

  // free(pr->sgn->mess);
  // free(pr->sgn->content);
  // free(pr->sgn);
  

  free(pr);
  free(mess);
  free(sgn->content);
  free(sgn);
  free(sgn2->content);
  free(sgn2);
  free(tmp);
  free(char_tmp);
  free(key_tmp);
  free(sKey);
  free(pKey);
  free(chaine);
  free(pKeyC);
  free(sKeyC);

  return 0;
}
