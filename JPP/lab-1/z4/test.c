#include <stdio.h>

#include "wrapper.h"

void TestFactorial(void)
{
    const int n = 5;
    int result = factorial(n);
    printf("Factorial of %d is %d\n", n, result);
}

void TestGCD(void)
{
    const int a = 74;
    const int b = 28;
    int result = gcd(a, b);
    printf("GCD of %d and %d is %d\n", a, b, result);
}

void print(int n,void * r)
{
    for (int i = 0; i < n; i++)
        printf("%d ", *((int*)r+i));
    printf("\n");
}

void TestSolve(void)
{
    const int a = 23;
    const int b = 5;
    const int c = 17;
    Pair result = solve(a, b, c);

    printf("Solutions of %d*x + %d*y = %d are x = %d and y = %d\n", a, b, c, result.x, result.y);
}

int main (int argc, char *argv[])
{
    wrapperInit();
        TestFactorial();
        TestGCD();
        TestSolve();
    wrapperClose();
}
