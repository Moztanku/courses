#include "lib.h"

// PRIVATE

void swap(int* a, int* b)
{
    const int temp = *a;
    *a = *b;
    *b = temp;
}

int gcdr(int a, int b)
{
    return b == 0 ? a : gcdr(b, a % b);
}

Pair egcd(int a, int b)
{
    Pair result = {1,0};
    
    if (b != 0)
    {
        result = egcd(b, a % b);
        const int temp = result.x;

        result.x = result.y;
        result.y = temp - (a / b) * result.y;
    }

    return result;
}

// PUBLIC

int factorial(const int n)
{
    return n < 2 ? 1 : factorial(n - 1) * n;
}

int gcd(int a, int b)
{
    if (a < b)
        swap(&a, &b);

    return gcdr(a, b);
}

Pair solve(int a, int b, int c)
{
    // ax + by = c, gcd(a,b) | c
    // egcd(a,b) -> s,t
    // as + bt = gcd(a,b)
    // gcd(a,b) * k = c = ask + btk
    // x = sk, y = tk
    Pair result = {0,0};

    const int d = gcd(a, b);

    if (c % d == 0)
    {
        const Pair st = egcd(a,b);

        const int s = st.x;
        const int t = st.y;
        const int k = c / d;

        result.x = s*k;
        result.y = t*k;
    }

    return result;
}