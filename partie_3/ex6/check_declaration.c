#include <stdio.h>
#include <stdlib.h>

#include "../ex5/linked_keys.h"

void delete_fake_signature(CellProtected *c) {
  CellProtected *to_dell;
  Protected *pr;
  int nb_fake = 0;

  while(c != NULL) {
    pr = c->data;
    // printf("mess = %s\n", pr->sgn->mess);

    // si la signature est fausse --> suppression
    if(verify(pr) == 0) {
      nb_fake +=1;
      to_dell = c;
      c = c->next;
      // TODO DELETE WRONG DECLARATION
      // delete_cell_protected(to_dell);
    }else {
      c = c->next;
    }
  }

  printf("Nombre de fraude repérée: %d\n", nb_fake);

  return;
}