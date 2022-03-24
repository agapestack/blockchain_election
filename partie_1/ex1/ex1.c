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

    // -------------------------------Q1 --------------------------------
    assert(is_prime_naive(7) == 1);
    assert(is_prime_naive(5) == 1);
    assert(is_prime_naive(1) == 0);
    assert(is_prime_naive(42) == 0);
    assert(is_prime_naive(1667) == 1);
    assert(is_prime_naive(1229) == 1);
    assert(is_prime_naive(953) == 1);
    assert(is_prime_naive(81) == 0);
    assert(is_prime_naive(2) == 1);

    // -------------------------------Q2-------------------------------

    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu, tps_1, tps_2;

    long i = 2;
    long last_prime = 2;
    double temps_cpu_last_prime;
    int save_time = 0;

    temps_cpu = 0;
    // Trouver le plus grand nombre premier en 2ms
    // on test tous les nombres qui ont un temps d'exécution inferieur à 2ms et si il est premier on le sauvegarde dans last_prime
    while(temps_cpu <= 0.002) {
        temps_initial = clock();
        if(is_prime_naive(i) == 1)
            last_prime = i;
            save_time = 1;
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        // on sauvegarde le temps associer au dernier nombre premier trouver
        if(save_time == 1) {
            temps_cpu_last_prime = temps_cpu;
            save_time = 0;
        }
        i++;
    }
    printf("Dernier nombre premier trouver en 2ms par is_prime_naive: %ld\ttemps=%fs\n", last_prime, temps_cpu_last_prime);
    print_is_prime(last_prime);

    // -------------------------------Q3-------------------------------
    // Complexité Θ(m) car on a 2 opérations élémentaires (modulo et multiplication) m fois (la puissance)

    // printf("%lx\n", modpow_naive(2, 10, 255));
    assert(modpow_naive(2, 10, 255) == 4);
    assert(modpow_naive(5, 10, 56) == 9);
    assert(modpow_naive(7, 11, 33) == 7);
    assert(modpow_naive(3, 24, 22) == 15);
    assert(modpow_naive(53534, 0, 232) == 1);
    assert(modpow_naive(6, 4, 1296) == 0);
    assert(modpow_naive(8, 5, 7) == 1);
    assert(modpow_naive(12, 5, 2) == 0);

    // -------------------------------Q4-------------------------------
    // Complexité Ο(log(m)) car on divise par deux la puissance à chaque appel récursif
    // printf("%d\n", modpow(2, 0, 255));
    assert(modpow(2, 10, 255) == 4);
    assert(modpow(5, 10, 56) == 9);
    assert(modpow(7, 11, 33) == 7);
    assert(modpow(3, 24, 22) == 15);
    assert(modpow(53534, 0, 232) == 1);
    assert(modpow(6, 4, 1296) == 0);
    assert(modpow(8, 5, 7) == 1);
    assert(modpow(12, 5, 2) == 0);

    // -------------------------------Q5-------------------------------
    FILE *fic = fopen("./comparaison_exponentiation.txt", "w");
    if (!fic)
    {
        printf("Erreur ouverture du fichier\n");
        exit(12);
    }

    int nb_alea = rand() % RAND_MAX;
    int mod_alea = rand() % 1024;

    // comparaison de modpow et modpow_naive
    for (int i = 2; i < NB_TOUR_EXPONENTIATION; i++)
    {
        temps_initial = clock();
        for (int j = 0; j < ECART_TOUR_EXPONENTIATION; j++)
        {
            modpow_naive(nb_alea, i, mod_alea);
        }
        temps_final = clock();
        tps_1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        printf("%f\n", tps_1);

        temps_initial = clock();
        for (int j = 0; j < ECART_TOUR_EXPONENTIATION; j++)
        {
            modpow(nb_alea, i, mod_alea);
        }
        temps_final = clock();
        tps_2 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        printf("%f\n", tps_2);

        fprintf(fic, "%d %f %f\n", i, tps_1, tps_2);
    }

    // MILLER RABIN
    // On evite les assert ici car c'est un test de primalite probabiliste, on va donc tirer des nombres supposes pas trop grand pour pouvoir verifier avec is_prime_naive
    long random_prime;

    for (int i = 0; i < 10; i++)
    {
        random_prime = random_prime_number(rand() % 12 + 3, rand() % 6 + 20, 5);
        if(is_prime_naive(random_prime) == 1) {
            printf("random_prime_number trouve: %ld\tprime: true\n", random_prime);
        } else {
            printf("random_prime_number trouve: %ld\tprime: false\n", random_prime);
        }
        
    }

    fclose(fic);

    return 0;
}
