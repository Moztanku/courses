#pragma once

typedef unsigned long long GF; // Galois Field element

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
