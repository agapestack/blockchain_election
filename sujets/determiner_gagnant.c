#include <stdio.h>
#include <stdlib.h>

#include "../../partie_2/ex3/keys_struct.h"
#include "determiner_gagnant.h"
#include "../../params.h"

HashCell *create_hashCell(Key *key)
{
    HashCell *res = (HashCell *)malloc(sizeof(HashCell));
    if (!res)
    {
        exit(12);
    }
    res->key = key;
    res->val = 0;
    return res;
}

int hash_function(Key *key, int size)
{
    int s = 0;
    char *chaine = key_to_str(key);
    while (*chaine)
    {
        s += (int)(*chaine);
        chaine++;
    }
    return s % size;
}

int find_position(HashTable *t, Key *key)
{
    HashCell **tab = t->tab;
    for (int i = 0; i < t->size; i++)
    {
        HashCell *cell = tab[i];
        if (cell->key == key)
        {
            return i;
        }
        else
        {
            while (cell != NULL)
            {
                continue;
            }
            return i;
        }
    }
    return -1;
}

HashTable *create_hashTable(CellKey *keys, int size)
{
    HashTable *res = (HashTable *)malloc(sizeof(HashTable));
    if (!res)
    {
        exit(12);
    }

    // Allouer un tableu de pointeur vers un HashCell afin de mettre a jour des donnees dedans
    res->tab = (HashCell **)malloc(sizeof(HashCell *) * size);
    res->size = size;
    int i = 0;

    while (keys)
    {
        HashCell *hashCell = res->tab[i];
        hashCell->key = keys->data;
        keys = keys->next;
        i++;
    }
    return res;
}

void delete_hashTable(HashTable *t)
{
    for (int i = 0; i < t->size; i++)
    {
        free(t->tab[i]);
    }
    free(t);
}

Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{
    HashTable *Hc = create_hashTable(candidates, sizeC);
    HashTable *Hv = create_hashTable(voters, sizeV);

    CellProtected *list_decla = read_declarations(FILE_DECLARATIONS);
    print_list_protected(list_decla);

    CellProtected *cur = list_decla;
    while (cur)
    {
        Protected *decla = cur->data;
        Key *pKey_V = decla->pKey;
        Key *pKey_C = str_to_key(decla->declaration_vote);

        int pos_V = find_position(Hv, pKey_V);
        int pos_C = find_position(Hc, pKey_C);

        int nbVote_V = Hv->tab[pos_V]->val;
        int nbVote_C = Hc->tab[pos_C]->val;

        // La personne a le droit de voter et la personne sur qui porte le vote est un candidat de l'election
        if ((pos_V != -1) && (pos_C != -1))
        {
            // La personne n'a pas deja vote
            if (nbVote_V == 0)
            {
                nbVote_V++;
                nbVote_C++;
            }
            else
            {
                printf("Le vote n'est pas pris en compte\n");
                continue;
            }
        }
        else
        {
            printf("Le vote n'est pas pris en compte\n");
            continue;
        }
    }

    // Je comprends pas l'enonce ici, si on a un vote invalid, on arrete la fonction ou pas
    // Apres avoir compte les votes

    int nbVote_mx = Hc->tab[0]->val;
    Key *pKey_win = Hc->tab[0]->key;
    for (int i = 1; i < Hc->size; i++)
    {
        HashCell *cell = Hc->tab[i];
        if (cell != NULL)
        {
            if (cell->val > nbVote_mx)
            {
                nbVote_mx = cell->val;
                pKey_win = cell->key;
                continue;
            }
            else
            {
                continue;
            }
        }
        else
        {
            printf("Case Null\n");
            continue;
        }
    }

    return pKey_win;
}