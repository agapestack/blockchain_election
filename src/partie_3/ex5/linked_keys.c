#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_keys.h"

CellKey *create_cell_key(Key *key)
{
  CellKey *c = (CellKey *)malloc(sizeof(CellKey));
  if (!c)
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
  CellKey *res = NULL;
  char buffer[512], pKey[256];

  if (!fic)
    exit(12);

  while (fgets(buffer, 512, fic) != NULL)
  {
    if (sscanf(buffer, "%s ", pKey) == 1)
    {
      // printf("%s\n", pKey);
      res = inserer_cell_tete(str_to_key(pKey), res);
    }
  }

  fclose(fic);

  return res;
}

void print_list_keys(CellKey *c)
{
  if (!c)
    return;

  printf("-----PRINT LIST KEYS START-----\n");

  char *tmp;

  while (c != NULL)
  {
    tmp = key_to_str(c->data);
    printf("%s\n", tmp);
    c = c->next;
    free(tmp);
  }

  printf("-----PRINT LIST KEYS STOP-----\n\n\n");
}

void delete_cell_key(CellKey *c)
{
  if (c)
  {
    free(c->data);
    free(c);
  }

  return;
}
void free_list_keys(CellKey *c)
{
  CellKey *tmp;

  while (c != NULL)
  {
    tmp = c->next;
    delete_cell_key(c);
    c = tmp;
  }

  return;
}

CellProtected *create_cell_protected(Protected *pr)
{
  CellProtected *res = (CellProtected *)malloc(sizeof(CellProtected));
  if (!res)
    exit(12);

  res->data = pr;
  res->next;

  return res;
}

CellProtected *inserer_list_protected(Protected *pr, CellProtected *next)
{
  CellProtected *nouv = create_cell_protected(pr);
  nouv->next = next;

  return nouv;
}

CellProtected *read_declarations(char *nomfic)
{

  FILE *fic = fopen(nomfic, "r");
  CellProtected *res = NULL;
  Protected *pr_tmp;
  Signature *sgn_tmp;
  Key *k_tmp;
  char buffer[512], *decla_alloc;
  char pKey[128], declaration[128], sgn[256];

  if (!fic)
    exit(12);

  while (fgets(buffer, 512, fic) != NULL)
  {
    if (sscanf(buffer, "%s %s %s", pKey, declaration, sgn) == 3)
    {
      // printf("%s %s %s\n", pKey, declaration, sgn);
      sgn_tmp = str_to_signature(sgn);
      k_tmp = str_to_key(pKey);
      decla_alloc = strdup(declaration);
      pr_tmp = init_protected(k_tmp, decla_alloc, sgn_tmp);
      res = inserer_list_protected(pr_tmp, res);
    }
  }

  fclose(fic);
  return res;
}

void print_list_protected(CellProtected *pr)
{
  CellProtected *tmp;
  char *str_sgn, *str_key, *str_declaration;

  printf("-----PRINT LIST PROTECTED START-----\n");

  while (pr != NULL)
  {
    tmp = pr->next;
    str_sgn = signature_to_str(pr->data->sgn);
    str_key = key_to_str(pr->data->pKey);
    str_declaration = pr->data->declaration_vote;

    printf("%s %s %s\n", str_key, str_declaration, str_sgn);

    free(str_sgn);
    free(str_key);

    pr = tmp;
  }

  printf("-----PRINT LIST PROTECTED STOP-----\n");
}

void delete_cell_protected(CellProtected *pr)
{
  free_protected(pr->data);
  free(pr);

  return;
}

void free_cell_protected(CellProtected *pr)
{
  CellProtected *tmp;

  while (pr != NULL)
  {
    tmp = pr->next;
    delete_cell_protected(pr);
    pr = tmp;
  }

  return;
}