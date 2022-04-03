#include <stdio.h>
#include <stdlib.h>

#include "../ex5/linked_keys.h"


// pour faire des tests sur delete_fake_signature --> on change une/des signature(s) pour qu'elle soit fausse et on voit si la taille de c diminu bien
int get_cp_size(CellProtected *c) {
  CellProtected *cursor;
  cursor = c;
  int compteur = 0;

  while(cursor != NULL) {
    compteur += 1;
    cursor = cursor->next;
  }

  return compteur;
}

void delete_fake_signature(CellProtected *c) {
  CellProtected *to_del;
  Protected *pr;
  int nb_fake = 0;

  while(c != NULL) {
    pr = c->data;
    // printf("mess = %s\n", pr->sgn->mess);

    // si la signature est fausse --> suppression
    if(verify(pr) == 0) {
      nb_fake +=1;
      to_del = c;
      c = c->next;
      // TODO DELETE WRONG DECLARATION
      // printf("test delete_cell_protected\n");
      // delete_cell_protected(to_del);
    }else {
      c = c->next;
    }
  }

  printf("Nombre de fraude repérée: %d\n", nb_fake);

  return;
}