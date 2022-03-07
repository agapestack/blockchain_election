#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "miller_rabin.h"
#include "exponentiation.h"
#include "../ex2/keys.h"

#define NB_TOUR_EXPONENTIATION 100
#define ECART_TOUR_EXPONENTIATION 100000

int main(int argc, char **argv)
{

    srand(time(NULL));

    // -------------------------------Q1 Jeux de test-------------------------------
    // assert(is_prime_naive(7) == 1);
    // print_is_prime(7);
    // print_is_prime(21);
    // print_is_prime(5);
    // print_is_prime(13);
    // print_is_prime(97);
    // print_is_prime(57);
    // print_is_prime(59);

    // -------------------------------Q2-------------------------------

    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu, tps_1, tps_2;

    long i = 2;
    long last_prime = 2;

    temps_cpu = 0;
    // while(temps_cpu <= 0.002) {
    //     temps_initial = clock();
    //     if(is_prime_naive(i) == 1)
    //         last_prime = i;
    //     temps_final = clock();
    //     temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    //     i++;
    // }
    // printf("%fs\t%ld\n", temps_cpu, last_prime);
    print_is_prime(last_prime);

    // -------------------------------Q3-------------------------------
    // Complexité thêta(m)
    // printf("%ld\n", modpow_naive(2, 10, 255));

    // -------------------------------Q4-------------------------------
    // Complexité O(log(m))
    // printf("%d\n", modpow(2, 0, 255));

    // -------------------------------Q5-------------------------------
    FILE *fic = fopen("./comparaison_exponentiation.txt", "w");
    if (!fic)
    {
        printf("Erreur ouverture du fichier\n");
        exit(12);
    }

    int nb_alea = rand() % RAND_MAX;
    int mod_alea = rand() % 1024;
    
    // uncomment bellow to test and write time comparaison between modpow_naive and modpow
    // for (int i = 2; i < NB_TOUR_EXPONENTIATION; i++)
    // {
    //     temps_initial = clock();
    //     for (int j = 0; j < ECART_TOUR_EXPONENTIATION; j++)
    //     {
    //         modpow_naive(nb_alea, i, mod_alea);
    //     }
    //     temps_final = clock();
    //     tps_1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    //     printf("%f\n", tps_1);

    //     temps_initial = clock();
    //     for (int j = 0; j < ECART_TOUR_EXPONENTIATION; j++)
    //     {
    //         modpow(nb_alea, i, mod_alea);
    //     }
    //     temps_final = clock();
    //     tps_2 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    //     printf("%f\n", tps_2);

    //     fprintf(fic, "%d %f %f\n", i, tps_1, tps_2);
    // }


    // MILLER RABIN
    // On évite les assert ici car c'est un test de primalité probabiliste  
    printf("%ld\n", random_prime_number(12, 24, 5));

    return 0;
}
