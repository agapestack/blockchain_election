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

  CellProtected *list_decla = read_declarations(FILE_DECLARATIONS);
  // print_list_protected(list_decla);
  delete_fake_signature(list_decla);

  
  // free_list_keys(list_cand);
  // free_list_keys(list_keys);
  free_cell_protected(list_decla);

  return 0;
}

