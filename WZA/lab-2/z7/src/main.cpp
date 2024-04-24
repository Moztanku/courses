#include <iostream>
#include <format>

#include "poly.hpp"

auto main() -> int
{
    // 1 + x^2 + x^4
    Polynomial f1{1.0, 0.0, 1.0, 0.0, 1.0};
    // -1 + -2x + -x^2 + x^4
    Polynomial f2{-1.0, -2.0, -1.0, 0.0, 1.0};
    // -1 + x^3
    Polynomial f3{-1.0, 0.0, 0.0, 1.0};

    Polynomial gcd_f12 = gcd(f1, f2);
    Polynomial gcd_f123 = gcd(gcd_f12, f3);

    std::cout << std::format(
        "gcd({}, {}, {}) = {}\n",
        to_string(f1), to_string(f2), to_string(f3),
        to_string(gcd_f123)
    );

    // -4 + -4x + x^2 + x^3
    Polynomial g1{-4.0, -4.0, 1.0, 1.0};

    // 4 + -4x + -x^2 + x^3
    Polynomial g2{4.0, -4.0, -1.0, 1.0};

    // 2 + -x + -2x^2 + x^3
    Polynomial g3{2.0, -1.0, -2.0, 1.0};

    Polynomial gcd_g12 = gcd(g1, g2);
    Polynomial gcd_g123 = gcd(gcd_g12, g3);

    std::cout << std::format(
        "gcd({}, {}, {}) = {}\n",
        to_string(g1), to_string(g2), to_string(g3),
        to_string(gcd_g123)
    );
    
    return 0;
}