#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../ex5/linked_keys.h"
#include "../../params.h"
#include "./check_declaration.h"

#include "../../partie_1/ex2/keys.h"

int main(void) {

  // CellKey *list_keys = read_public_keys(FILE_KEYS);
  // print_list_keys(list_keys);

  // CellKey *list_cand = read_public_keys(FILE_CANDIDATES);
  // print_list_keys(list_cand);
  Protected *pr;
  CellProtected *cursor;
  char *buffer;

  printf("1\n");
  CellProtected *list_decla = read_declarations(FILE_DECLARATIONS);
  printf("2\n");
  // print_list_protected(list_decla);
  
  printf("-----------------DELETE FAKE SIGNATURE START----------------\n");
  cursor = list_decla;
  while(cursor != NULL) {
    pr = cursor->data;
    // printf("pkey = %s, decla = %s, sgn = %s\n", key_to_str(pr->pKey), pr->declaration_vote, signature_to_str(pr->sgn));
    buffer = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->n, pr->pKey->val);
    if(verify(pr) == 1) {
      printf("OK\n");
    } else {
      printf("KO\n");
    }
    // printf("decla = %s\tdecrypted = %s\n", pr->declaration_vote, buffer);
    free(buffer);

    cursor = cursor->next;
  }
  // delete_fake_signature(list_decla);
  printf("-----------------DELETE FAKE SIGNATURE STOP----------------\n");
  
  // free_list_keys(list_cand);
  // free_list_keys(list_keys);
  printf("3\n");
  free_cell_protected(list_decla);

  return 0;
}

