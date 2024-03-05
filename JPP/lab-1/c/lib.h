#pragma once

struct Pair {
    int x;
    int y;
};

int factorial(const int n);
int factorial_recursive(const int n);

int gcd(int a, int b);
int gcd_recursive(int a, int b);

struct Pair solve(int a, int b, int c);
struct Pair solve_recursive(int a, int b, int c);