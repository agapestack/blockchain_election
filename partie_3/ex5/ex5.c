#include <stdio.h>
#include <stdlib.h>

#include "linked_keys.h"
#include "../../params.h"

int main(void) {

  CellKey *list_cand = read_public_keys(FILE_KEYS);
  // print_list_keys(list_cand);

  CellProtected *list_decla = read_declarations(FILE_DECLARATIONS);
  printf("FIN READ DECLARATION\n");
  // print_list_protected(list_decla);

  free_cell_protected(list_decla);
  free_list_key(list_cand);

  return 0;
}
