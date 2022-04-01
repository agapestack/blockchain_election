#ifndef __PARAMS__
#define __PARAMS__

#define NB_VALIDATION_MILLER 256    // probabilite d'erreur = (1/4)^NB_VALIDATION_MILLER
#define LOW_SIZE 3                  // Nombre premier minimum = 2^LOW_SIZE
#define UP_SIZE 7                   // Nombre premier maximum = 2^UP_SIZE
#define NB_KEYS 20                  // Nombre de personnes enregistre aux elections / declaration de vote
#define NB_CANDIDATS 1              // Nombre de candidats parmis les personnes enregistre

#define FILE_KEYS "../../data/keys.txt"                
#define FILE_CANDIDATES "../../data/candidates.txt"
#define FILE_DECLARATIONS "../../data/declarations.txt"

#endif