#include <iostream>
#include <ranges>
#include <cmath>
#include <unordered_map>

#include "Galois.hpp"
#include "DHSetup.hpp"
#include "User.hpp"

auto main() -> int
{
    using GF = Galois<1234567891>;

    DHSetup<GF> dh_setup;
    User user(dh_setup);

    user.set_key(1001);

    GF message = 42;
    std::cout << "Message: " << message << "\n";
    std::cout << "Encrypted message: " << user.encrypt(message) << "\n";
    std::cout << "Decrypted message: " << user.decrypt(user.encrypt(message)) << "\n";
    
    return 0;
}