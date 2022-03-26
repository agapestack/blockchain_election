#include <stdlib.h>
#include <stdio.h>

#include "../ex5/linked_keys.h"
#include "../../params.h"
#include "./check_declaration.h"

int main(void) {

  // CellKey *list_keys = read_public_keys(FILE_KEYS);
  // print_list_keys(list_keys);

  // CellKey *list_cand = read_public_keys(FILE_CANDIDATES);
  // print_list_keys(list_cand);

  printf("1\n");
  CellProtected *list_decla = read_declarations(FILE_DECLARATIONS);
  printf("2\n");
  print_list_protected(list_decla);
  
  printf("-----------------DELETE FAKE SIGNATURE START----------------\n");
  delete_fake_signature(list_decla);
  printf("-----------------DELETE FAKE SIGNATURE STOP----------------\n");
  
  // free_list_keys(list_cand);
  // free_list_keys(list_keys);
  printf("3\n");
  free_cell_protected(list_decla);

  return 0;
}

