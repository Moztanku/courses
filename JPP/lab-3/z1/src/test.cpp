#include <iostream>
#include <ranges>
#include <cmath>

#include "Galois.hpp"
#include "DiffieHellman.hpp"

auto main() -> int
{
    DHSetup<Galois<103>> dh_setup;

    std::cout << dh_setup.get_generator() << std::endl;
    
    return 0;
}