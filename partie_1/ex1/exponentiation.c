#include <stdio.h>
#include <stdlib.h>
#include "exponentiation.h"

int is_prime_naive(long p)
{
    if (p <= 1) {
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
    if(m < 0) {
        printf("modpow_naive: invalid parameter(negative exponent)\n");
        exit(14);
    }
    if(m == 0) {
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
    
    if (m % 2 == 0)     // cas pair
    {
        return (b * b) % n;
    }
    else                // cas impair
    {
        return (a * b * b) % n;
    }
}