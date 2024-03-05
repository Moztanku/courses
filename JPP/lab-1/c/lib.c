#include "lib.h"

#include <limits.h>

// PRIVATE

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int gcdr(int a, int b)
{
    return b == 0 ? a : gcdr(b, a % b);
}

struct Pair egcd_iter(int a, int b) {
    struct Pair result = {1,0};
    struct Pair prev = {0,1};

    while (b != 0) {
        int q = a / b;

        int x = result.x - q * prev.x;
        result.x = prev.x;
        prev.x = x;

        int y = result.y - q * prev.y;
        result.y = prev.y;
        prev.y = y;

        int temp = a;
        a = b;
        b = temp - q * b;
    }
    
    return result;
}

struct Pair egcd_recu(int a, int b)    // 17,5 | 5,2 | 2,1 | 1,0
{                                           // -2,7    1,-2  0,1   1,0
    struct Pair result = {0,0};
    if (b == 0)
    {
        result.x = 1;
    } else {
        struct Pair temp = egcd_recu(b, a % b);

        result.x = temp.y;
        result.y = temp.x - (a / b) * temp.y;
    }

    return result;
}

// ITERATIVE

int factorial_iter(const int n)
{
    int val = 1;
    
    for (int i = 1; i <= n; i++)
        val *= i;

    return val;
}

int gcd_iter(int a, int b)
{
    if (a < b)
        swap(&a,&b);

    while (b != 0) {
        a %= b;
        swap(&a, &b);
    }

    return a;
}

struct Pair solve_iter(int a, int b, int c)
{
    struct Pair result = {0,0};

    int d = gcd(a, b);

    if (c % d == 0)
    {
        struct Pair st = egcd_iter(a,b);
        
        int s = st.x;
        int t = st.y;
        int k = c / d;

        result.x = s*k;
        result.y = t*k;
    }

    return result;
}

// RECURSIVE

int factorial_recu(const int n)
{
    return n < 2 ? 1 : factorial(n - 1) * n;
}


int gcd_recu(int a, int b)
{
    if (a < b)
        swap(&a, &b);

    return gcdr(a,b);
}

struct Pair solve_recu(int a, int b, int c)
{
    // ax + by = c, gcd(a,b) | c
    // egcd(a,b) -> s,t
    // as + bt = gcd(a,b)
    // gcd(a,b) * k = c = ask + btk
    // x = sk, y = tk
    struct Pair result = {0,0};

    int d = gcd(a, b);

    if (c % d == 0)
    {
        struct Pair st = egcd_recu(a,b);
        
        int s = st.x;
        int t = st.y;
        int k = c / d;

        result.x = s*k;
        result.y = t*k;
    }

    return result;
}