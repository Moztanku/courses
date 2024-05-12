#include <iostream>
#include <format>

#include "poly.hpp"

auto main() -> int
{
    // 1 + x^2 + x^4
    Polynomial f{1.0, 0.0, 1.0, 0.0, 1.0};
    // -1 + -2x + -x^2 + x^4
    Polynomial g{-1.0, -2.0, -1.0, 0.0, 1.0};

    const auto GCD = gcd(f, g);
    const auto [A, B] = egcd(f, g);

    std::cout << std::format(
        "GCD(f, g)\n\t= {}\n\t= A x f + B x g\n\t= {} x {} + {} x {}\n\t= {}\n",
        to_string(GCD),
        to_string(A), to_string(f),
        to_string(B), to_string(g),
        to_string((A * f) + (B * g))
    );
    
    return 0;
}