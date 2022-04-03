#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "miller_rabin.h"

int is_prime_naive(long p)
{
    if (p <= 1)
    {
        return 0;
    }

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
    if (m < 0)
    {
        printf("modpow_naive: invalid parameter(negative exponent)\n");
        exit(14);
    }
    if (m == 0)
    {
        return 1 % n;
    }

    long res = 1;

    for (int i = 0; i < m; i++)
    {
        res = res * a;
        res = res % n;
    }

    return res;
}

// retourn a^m modulo n
long modpow(long a, long m, long n)
{
    long res = 1;
    long b;

    // a = a % n;

    if (m == 0)
    {
        return 1;
    }

    b = modpow(a, m / 2, n);

    if (m % 2 == 0) // cas pair
    {
        return (b * b) % n;
    }
    else // cas impair
    {
        return (a * b * b) % n;
    }
}

// return 1 if miller witness else 0
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

// 0 not prime   1 prime
int is_prime_miller(long p, int k)
{
    if (p == 2)
    {
        return 1;
    }
    if (!(p & 1) && p != 1)
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
        a = rand_long(2, p - 1);
        if (witness(a, b, d, p))
        {
            return 0;
        }
    }
    return 1;
}

long random_prime_number(int low_size, int up_size, int k) {
  // au cas ou on veut dépasser la capacité d'un long sur 32bits on quitte avant
  if(up_size > 32) {
    printf("Entiers sur plus de 32 bits non implémenté dans ce projet\n");
    exit(14);
  }

  long min = modpow(2, low_size - 1, LONG_MAX);
  long max = modpow(2, up_size, LONG_MAX) -1 ;

  // printf("%ld\t%ld\n", min, max);
  long to_test = rand_long(min, max);

  // si to_test est premier on le renvoie sinon on retire un autre élément
  while(1) {
    if(is_prime_miller(to_test, k) == 1)
      return to_test;
    to_test = rand_long(min, max);
  }
}
