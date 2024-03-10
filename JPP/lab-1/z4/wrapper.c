/* wrapper.c */
#include "wrapper.h"

#include <stdlib.h>

extern void adainit     (void);
extern void adafinal    (void);

extern int   ada_factorial  (int);
extern int   ada_gcd        (int, int);
extern Pair* ada_solve      (int, int, int);

int factorial(int n)
{
    return ada_factorial(n);
}

int gcd(int a, int b)
{
    return ada_gcd(a, b);
}

Pair solve(int a, int b, int c)
{
    Pair* result = ada_solve(a, b, c);
    Pair p = {result->x, result->y};

    free(result);

    return p;
}

void wrapperInit(void)
{
    adainit();
}

void wrapperClose(void)
{
    adafinal();
}