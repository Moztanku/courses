#include "lib.h"

// PRIVATE

void swap(int* a, int* b)
{
    const int temp = *a;
    *a = *b;
    *b = temp;
}

Pair egcd(int a, int b)
{
    Pair result = {1,0};
    Pair prev = {0,1};

    while (b != 0) {
        const int q = a / b;

        const int x = result.x - q * prev.x;
        result.x = prev.x;
        prev.x = x;

        const int y = result.y - q * prev.y;
        result.y = prev.y;
        prev.y = y;

        const int temp = a;
        a = b;
        b = temp - q * b;
    }

    return result;
}

// PUBLIC

int factorial(const int n)
{
    int val = 1;
    
    for (int i = 1; i <= n; i++)
        val *= i;

    return val;
}

int gcd(int a, int b)
{
    if (a < b)
        swap(&a, &b);

    while (b != 0)
    {
        int temp = a;
        a = b;
        b = temp % b;
    }

    return a;
}

Pair solve(int a, int b, int c)
{
    Pair result = {0,0};

    const int d = gcd(a,b);

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