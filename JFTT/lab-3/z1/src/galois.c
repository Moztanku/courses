#include "galois.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// If the compiler is GCC or Clang, check if GF_P is a prime number
#if defined(__GNUC__) || defined(__clang__)
    static bool is_Prime(int n)
    {
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;
        if (n % 2 == 0 || n % 3 == 0)
            return false;

        for (int i = 5; i * i <= n; i += 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        
        return true;
    }

    static void __attribute__((constructor)) validate_GF_P()
    {
        if (!is_Prime(GF_P))
        {
            fprintf(stderr, "GF_P must be a prime number\n");

            exit(1);
        }
    }
#endif

GF gf_add(GF a, GF b){ return (a + b) % GF_P; }
GF gf_sub(GF a, GF b){ return (a + gf_inva(b)) % GF_P; }
GF gf_mul(GF a, GF b){ return (a * b) % GF_P; }
GF gf_div(GF a, GF b){ return gf_mul(a, gf_invm(b)); }

GF gf_pow(GF a, GF b)
{
    GF result = 1;

    while (b > 0)
    {
        if (b % 2 == 1)
            result = gf_mul(result, a);

        a = gf_mul(a, a);
        b /= 2;
    }

    return result;
}

GF gf_norm(int a)
{
    a %= GF_P;

    return a < 0 ?
        a + GF_P :
        a;
}

GF gf_invm(GF a)
{
    int b = GF_P;

    int x = 1;
    int y = 0;

    int x1 = 0;
    int y1 = 1;

    while (b != 0)
    {
        int q = a / b;

        int x2 = x - q * x1;
        x = x1;
        x1 = x2;

        int y2 = y - q * y1;
        y = y1;
        y1 = y2;

        int temp = a;
        a = b;
        b = temp - q * b;
    }

    if (x < 0)
        x += GF_P;

    return x % GF_P;
}

GF gf_inva(GF a)
{
    return (GF_P - a) % GF_P;
}
