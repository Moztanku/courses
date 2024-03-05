#include "lib.h"

#include <limits.h>

int factorial(const int n)
{
    int val = 1;
    
    for (int i = 1; i <= n; i++)
        val *= i;

    return val;
}

int factorial_recursive(const int n)
{
    return n < 2 ? 1 : factorial(n - 1) * n;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int gcd(int a, int b)
{
    if (a < b)
        swap(&a,&b);

    while (b != 0) {
        a %= b;
        swap(&a, &b);
    }

    return a;
}

int gcd_recursive(int a, int b)
{
    if (a < b)
        swap(&a, &b);

    return gcdr(a,b);
}

int gcdr(int a, int b)
{
    return b == 0 ? a : gcdr(b, a % b);
}

struct Pair egcd(int a, int b)
{
    struct Pair result = {0,0};

    while (b != 0) {

    }
}   //

struct Pair egcd_recursive(int a, int b)    // 17,5 | 5,2 | 2,1 | 1,0
{                                           // -2,7    1,-2  0,1   1,0
    struct Pair result = {0,0};
    if (b == 0)
    {
        result.x = 1;
    } else {
        struct Pair temp = egcd_recursive(b, a % b);

        result.x = temp.y;
        result.y = temp.x - (a / b) * temp.y;
    }

    return result;
}

struct Pair solve(int a, int b, int c)
{
    struct Pair result = {0,0};

    return result;
}

struct Pair solve_recursive(int a, int b, int c)
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
        struct Pair st = egcd_recursive(a,b);
        
        int s = st.x;
        int t = st.y;
        int k = c / d;

        result.x = s*k;
        result.y = t*k;
    }

    return result;
}