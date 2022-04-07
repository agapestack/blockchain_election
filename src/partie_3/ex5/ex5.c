#include <stdio.h>
#include <stdlib.h>

#include "../../params.h"
#include "./linked_list.h"

int main(void) {

  printf("----------START READ_PUBLIC_KEYS----------\n");
  CellKey **lk = read_public_keys(FILE_KEYS);
  printf("----------END READ_PUBLIC_KEYS----------\n\n\n");
  
  printf("----------START PRINT_LIST_KEYS----------\n");
  print_list_keys(*lk);
  printf("----------END PRINT_LIST_KEYS----------\n\n\n");

  delete_list_keys(lk);

  printf("----------START READ_PROTECTED----------\n");
  CellProtected **lp = read_protected(FILE_DECLARATIONS);
  printf("----------END READ_PROTECTED----------\n\n\n");

  printf("----------START PRINT_LIST_KEYS----------\n");
  print_list_protected(*lp);
  printf("----------END PRINT_LIST_KEYS----------\n\n\n");

  delete_list_protected(lp);

  return 0;
}
