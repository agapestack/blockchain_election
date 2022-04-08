#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "../../params.h"

int main(void)
{

  printf("----------START READ_PROTECTED----------\n");
  CellProtected **lp = read_protected(FILE_DECLARATIONS);
  printf("----------END READ_PROTECTED----------\n\n\n");

  printf("----------START PRINT_LIST_KEYS----------\n");
  print_list_protected(*lp);
  printf("----------END PRINT_LIST_KEYS----------\n\n\n");

  printf("----------START VERIFY_LIST_PROTECTED----------\n");
  verify_list_protected(lp);
  printf("----------END VERIFY_LIST_PROTECTED----------\n\n\n");

  // A present toutes les declarations sont bien verifier

  printf("----------START TEST HASH FUNCTIONS----------\n");


  
  delete_list_protected(lp);
  // free(list_decla);
  printf("----------END TEST HASH FUNCTIONS----------\n");

  return 0;
}