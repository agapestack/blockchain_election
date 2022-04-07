#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "../ex5/linked_list.h"
#include "../../partie_2/ex3/keys_struct.h"

void verify_list_protected(CellProtected **cp)
{
  CellProtected *cursor;
  CellProtected *prev, *nouv_tete;
  int nb_erreur = 0;
  int nb_test = 0;
  float pourcentage_erreur;

  cursor = *cp;
  while (cursor)
  {
    CellProtected *to_del;

    if (verify(cursor->data) == 1)
    { // signature valide
      prev = cursor;
      cursor = cursor->next;
    }
    else
    { // signature invalide
      nb_erreur += 1;

      if (prev)
      { // Si on a un element precedent
        prev->next = cursor->next;
        delete_cell_protected(cursor);
        cursor = prev->next;
      }
      else
      { // pas d'element precedent --> tete de liste
        nouv_tete = cursor->next;
        delete_cell_protected(cursor);
        *cp = nouv_tete;
        cursor = nouv_tete;
      }
    }

    nb_test++;
  }

  pourcentage_erreur = (nb_erreur * 100.0) / (nb_test);
  printf("Nombre de signatures test: %d\nNombre de signatures invalides supprimées: %d\nPourcentage d'erreur: %.02f%%\n", nb_test, nb_erreur, pourcentage_erreur);
  return;
}

HashCell* create_hashcell(Key* key) {
  HashCell *nouv = (HashCell*)malloc(sizeof(HashCell));
  if(!nouv)
    exit(12);

  nouv->key = key;
  nouv->val = 0;

  return nouv;
}

int hash_function(Key *key, int size) {
  int s = 0;
  char *chaine = key_to_str(key);
  while(*chaine) {
    s += (int)(*chaine);
    chaine++;
  }
  return s % size;
}

int find_position(HashTable *t, Key* key) {
  
}
