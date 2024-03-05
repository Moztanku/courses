#pragma once

struct Pair {
    int x;
    int y;
};

int factorial_iter(const int n);
int factorial_recu(const int n);

int gcd_iter(int a, int b);
int gcd_recu(int a, int b);

struct Pair solve_iter(int a, int b, int c);
struct Pair solve_recu(int a, int b, int c);