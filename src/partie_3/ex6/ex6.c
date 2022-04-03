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

  CellProtected *list_decla = read_declarations(FILE_DECLARATIONS);
  printf("Nombres de déclarations: %d\n", get_cp_size(list_decla));
  // print_list_protected(list_decla);
  
  printf("-----------------DELETE FAKE SIGNATURE START----------------\n");
  delete_fake_signature(list_decla);
  printf("Nombres de déclarations: %d\n", get_cp_size(list_decla));
  printf("-----------------DELETE FAKE SIGNATURE STOP----------------\n");
  
  // free_list_keys(list_cand);
  // free_list_keys(list_keys);
  free_cell_protected(list_decla);

  return 0;
}