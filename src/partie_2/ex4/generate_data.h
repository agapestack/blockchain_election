#ifndef __GENERATE_DATA__
#define __GENERATE_DATA__

#include "../../params.h"
#include "../ex3/keys_struct.h"

int is_in(int* tab, int val, int size);
void generate_random_data(int nv, int nc);

// meme fonction que generate_random_data mais avec des emplacements de fichiers differents, uniquement utilises pour l'ex 8...
void generate_random_data_test(int nv, int nc);

#endif