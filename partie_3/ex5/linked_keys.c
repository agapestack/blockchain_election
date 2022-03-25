#include <stdio.h>
#include <stdlib.h>

#include "linked_keys.h"

CellKey *create_cell_key(Key *key)
{
  CellKey *c = (CellKey *)malloc(sizeof(CellKey));
  if(!c)
    exit(12);

  c->data = key;
  c->next = NULL;

  return c;
}

CellKey *inserer_cell_tete(Key *key, CellKey *next)
{
  CellKey *new = create_cell_key(key);

  new->next = next;

  return new;
}

CellKey *read_public_keys(char *nomfic)
{
  FILE *fic = fopen(nomfic, "r");
  Key *key_tmp;
  CellKey *res = NULL;
  char buffer[512], pKey[256];

  if(!fic)
    exit(12);

  while (fgets(buffer, 512, fic) != NULL)
  {
    if (sscanf(buffer, "%s ", pKey) == 1)
    {
      // printf("%s\n", pKey);
      key_tmp = str_to_key(pKey);
      res = inserer_cell_tete(str_to_key(pKey), res);
      free(key_tmp);
    }
  }

  fclose(fic);

  return res;
}

void print_list_keys(CellKey* c) {
  if(!c)
    return;

  char *tmp;

  while(c != NULL) {
    tmp = key_to_str(c->data);
    printf("%s\n", tmp);
    c = c->next;
    free(tmp);
  }
}

void delete_cell_key(CellKey* c) {
  free(c->data);
  free(c);

  return;
}
void free_list_key(CellKey *c) {
  CellKey *tmp;

  while(c != NULL) {
    tmp = c->next;
    delete_cell_key(c);
    c = tmp;
  }

  return;
}

CellProtected* create_cell_protected(Protected* pr) {
  CellProtected *res = (CellProtected*)malloc(sizeof(CellProtected));
  if(!res)
    exit(12);

  res->data = pr;
  res->next;

  return res;
}

CellProtected* inserer_list_protected(Protected *pr, CellProtected *next) {
  CellProtected *nouv = create_cell_protected(pr);
  nouv->next = next;

  return nouv;
}

CellProtected* read_declarations(char* nomfic) {
  
  FILE *fic = fopen(nomfic, "r");
  CellProtected *res = NULL;
  Protected *pr_tmp;
  Signature *sgn_tmp;
  Key *k_tmp;
  char buffer[512];
  char pKey[128], declaration[128], sgn[256];
  int i=0;

  if(!fic)
    exit(12);

  while(fgets(buffer, 512, fic) != NULL) {
    if(sscanf(buffer, "%s %s %s", pKey, declaration, sgn) == 3) {
      printf("%d\n", i++);
      printf("%s %s %s\n", pKey, declaration, sgn);
      sgn_tmp = str_to_signature(sgn);
      k_tmp = str_to_key(pKey);
      pr_tmp = init_protected(k_tmp, declaration, sgn_tmp);
      res = inserer_list_protected(pr_tmp, res);
    }
  }

  fclose(fic);
  return res;
}

void print_list_protected(CellProtected *pr) {
  CellProtected *tmp;
  char *str_sgn, *str_key, *str_declaration;

  while(pr != NULL) {
    tmp = pr->next;
    str_sgn = signature_to_str(pr->data->sgn);
    str_key = key_to_str(pr->data->pKey);
    str_declaration = pr->data->declaration_vote;

    printf("%s %s %s\n", str_key, str_declaration, str_sgn);

    free(str_sgn);
    free(str_key);

    pr = tmp;
  } 
}

void delete_cell_protected(CellProtected *pr) {
  free_protected(pr->data);
  free(pr);

  return;
}

void free_cell_protected(CellProtected *pr) {
  CellProtected *tmp;

  while(pr != NULL) {
    tmp = pr->next;
    free(pr->data->pKey);
    // free(pr->data->declaration_vote);
    free(pr->data->sgn->content);
    // free(pr->data->sgn->mess);
    free(pr->data->sgn);
    free(pr->data);
    free(pr);
    pr = tmp;
  }

  return;
}
