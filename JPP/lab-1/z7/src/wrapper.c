#include "wrapper.h"

extern int  rust_factorial   (int);
extern int  rust_gcd         (int, int);
extern Pair rust_solve       (int, int, int);

int factorial(const int n)
{
    return rust_factorial(n);
}

int gcd(int a, int b)
{
    return rust_gcd(a, b);
}

Pair solve(int a, int b, int c)
{
    return rust_solve(a, b, c);
}