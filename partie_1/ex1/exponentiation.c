#include <stdio.h>
#include <stdlib.h>
#include "exponentiation.h"

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

long modpow(long a, long m, long n)
{
    long res = 1;
    long b;

    if (m == 0)
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