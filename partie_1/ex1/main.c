#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define NB_TOUR_EXPONENTIATION 100
#define ECART_TOUR_EXPONENTIATION 100000

int witness(long a, long b, long d, long p)
{
    long x = modpow(a, d, p);
    if (x == 1)
    {
        return 0;
    }
    for (long i = 0; i < b; i++)
    {
        if (x == p - 1)
        {
            return 0;
        }
        x = modpow(x, 2, p);
    }
    return 1;
}

long rand_long(long low, long up)
{
    return rand() % (up - low + 1) + low;
}

int is_prime_miller(long p, int k)
{
    if (p == 2)
    {
        return 1;
    }
    if (!(p & 1) || p <= 1)
    { // on verifie que p est impair et different de 1
        return 0;
    }
    // on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!(d & 1))
    { 
        // tant que d n’est pas impair
        d = d / 2;
        b = b + 1;
    } 
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;
    for (i = 0; i < k; i++)
    {
        a = randlong(2, p - 1);
        if (witness(a, b, d, p))
        {
            return 0;
        }
    }
    return 1;
}

int is_prime_naive(long p)
{
    for (int i = 3; i < p; i++)
    {
        if (p % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

void print_is_prime(long p)
{
    if (is_prime_naive(p) == 1)
    {
        printf("%ld est premier\n", p);
    }
    else
    {
        printf("%ld n'est pas premier\n", p);
    }
}

long modpow_naive(long a, long m, long n)
{
    int res = 1;

    for (int i = 0; i < m; i++)
    {
        res = res * a;
        res = res % n;
    }

    return res;
}

int modpow(long a, long m, long n)
{
    int res = 1;
    int b;

    if (m == 1)
    {
        return a % n;
    }

    b = modpow(a, m / 2, n);
    if (m % 2 == 0)
    {
        return (b * b) % n;
    }
    else
    {
        return (a * b * b) % n;
    }
}

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

    // temps_cpu = 0;
    // while(temps_cpu <= 0.002) {
    //     temps_initial = clock();
    //     if(is_prime_naive(i) == 1)
    //         last_prime = i;
    //     temps_final = clock();
    //     temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    //     i++;
    // }
    // printf("%fs\t%ld\n", temps_cpu, last_prime);
    // print_is_prime(last_prime);

    // -------------------------------Q3-------------------------------
    // Complexité thêta(m)
    printf("%ld\n", modpow_naive(2, 10, 255));

    // -------------------------------Q4-------------------------------
    // Complexité O(log(m))
    printf("%d\n", modpow(2, 10, 255));

    // -------------------------------Q5-------------------------------
    FILE *fic = fopen("./comparaison_exponentiation.txt", "w");
    if (!fic)
    {
        printf("Erreur ouverture du fichier\n");
        exit(12);
    }

    int nb_alea = rand() % RAND_MAX;
    int mod_alea = rand() % 1024;

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

    return 0;
}
