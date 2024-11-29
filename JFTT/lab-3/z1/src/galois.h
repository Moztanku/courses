#pragma once

typedef unsigned long long GF; // Galois Field element

// Define the characteristic of the Galois Field
//  can be changed to any prime number by adding '-DGF_P=<number>' to the compiler flags
//  using '#define GF_P <number>' in the code will not work because galois.c is compiled separately
#ifndef GF_P
#   define GF_P 1234577 // Prime number used as the characteristic of the Galois Field
#endif

GF gf_add(GF a, GF b);  // a + b
GF gf_sub(GF a, GF b);  // a - b
GF gf_mul(GF a, GF b);  // a * b
GF gf_div(GF a, GF b);  // a / b
GF gf_pow(GF a, GF b);  // a ^ b

GF gf_norm(int a);      // turn a into a number in the range [0, GF_P)
GF gf_invm(GF a);       // multiplicative inverse of a
GF gf_inva(GF a);       // additive inverse of a
