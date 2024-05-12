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

    User Alice(dh_setup);
    User Bob(dh_setup);

    Alice.set_key(Bob.get_public_key());
    Bob.set_key(Alice.get_public_key());

    GF message = 42;

    GF encrypted_message = Alice.encrypt(message);
    GF decrypted_message = Bob.decrypt(encrypted_message);

    std::cout << "Message: " << message << "\n";
    std::cout << "Encrypted message: " << encrypted_message << "\n";
    std::cout << "Decrypted message: " << decrypted_message << "\n";
    
    return 0;
}