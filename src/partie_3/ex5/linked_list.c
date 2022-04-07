#include <stdio.h>
#include <stdlib.h>

#include "./linked_list.h"
#include "../../partie_1/ex2/keys.h"

// creation d'une cellule contenant une cle
CellKey *create_cell_key(Key *key)
{
  CellKey *nouv = (CellKey *)malloc(sizeof(CellKey));
  if (!nouv)
    exit(12);

  nouv->data = key;
  nouv->next = NULL;
  return nouv;
}

// insertion d'une cle dans une liste chaine de cles
void inserer_key(CellKey **list_keys, Key *key)
{
  CellKey *nouv = create_cell_key(key);
  nouv->next = *list_keys;
  *list_keys = nouv;

  return;
}

// retourne une liste de cellule contenant des cles a partir d'un fichier
CellKey **read_public_keys(char *file_name)
{
  FILE *fic = fopen(file_name, "r");
  CellKey **res = (CellKey **)malloc(sizeof(CellKey *));
  Key *key;
  char buffer[256], pKey_str[256];

  if (!fic)
    exit(12);

  *res = NULL;

  while (fgets(buffer, 256, fic))
  {
    sscanf(buffer, "%s", pKey_str);
    // printf("%s\n", pKey_str);
    key = str_to_key(pKey_str);
    inserer_key(res, key);
  }

  fclose(fic);
  return res;
}

void print_list_keys(CellKey *LCK)
{
  CellKey *cursor = LCK;

  while (cursor)
  {
    char *buffer;
    buffer = key_to_str(cursor->data);
    printf("%s\n", buffer);
    free(buffer);
    cursor = cursor->next;
  }

  return;
}

// supprime une cellule contenant une cle
void delete_cell_key(CellKey *ck)
{
  free(ck->data);
  free(ck);

  return;
}

// supprime liste de cellule contant des cles
void delete_list_keys(CellKey **lk)
{
  CellKey *next;

  while (*lk)
  {
    next = (*lk)->next;
    delete_cell_key(*lk);
    *lk = next;
  }
  free(lk);

  return;
}

CellProtected *create_cell_protected(Protected *pr)
{
  CellProtected *nouv = (CellProtected*)malloc(sizeof(CellProtected));
  if (!nouv)
    exit(12);

  nouv->data = pr;
  nouv->next = NULL;
  return nouv;
}

void inserer_protected(CellProtected **list_protected, Protected *pr)
{
  CellProtected *to_add = create_cell_protected(pr);
  to_add->next = *list_protected;
  *list_protected = to_add;
}

CellProtected **read_protected(char *file_name)
{
  FILE *fic = fopen(file_name, "r");
  CellProtected **res = (CellProtected **)malloc(sizeof(CellProtected *));
  *res = NULL;
  Protected *pr;
  char buffer[512], protected_str[512], pKey_str[128], decla_str[128], sgn_str[256];

  if (!fic)
    exit(12);

  while (fgets(buffer, 512, fic))
  {
    sscanf(buffer, "%s %s %s", pKey_str, decla_str, sgn_str);
    sprintf(buffer, "%s %s %s", pKey_str, decla_str, sgn_str);
    pr = str_to_protected(buffer);
    inserer_protected(res, pr);
  }

  fclose(fic);
  return res;
}

void print_list_protected(CellProtected *lp)
{

  while (lp)
  {
    char *pr;
    pr = protected_to_str(lp->data);
    printf("%s\n", pr);
    free(pr);
    lp = lp->next;
  }

  return;
}

void delete_cell_protected(CellProtected* c) {
  free_protected(c->data);
  free(c);

  return;
}

void delete_list_protected(CellProtected **cp) {
  CellProtected *next;

  while(*cp) {
    next = (*cp)->next;
    delete_cell_protected(*cp);
    *cp = next;
  }
  free(cp);

  return;
}
