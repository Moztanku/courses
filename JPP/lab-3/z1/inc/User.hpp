#pragma once

#include "DHSetup.hpp"

template <class GF>
class User
{
    static_assert(impl::is_galois_v<GF>, "GF must be a Galois Field");
    static_assert(is_prime_v<GF::order>, "GF::order must be a prime number");

    public:
        User(const DHSetup<GF>& dh_setup) :
            dh_setup(dh_setup),
            private_key{get_random_private_key()}
        {}

        auto get_public_key() const noexcept -> GF 
        {
            return dh_setup.power(dh_setup.get_generator(), private_key);
        }

        void set_key(const GF& a)
        {
            cipher_key = dh_setup.power(a, private_key);
        }

        auto encrypt(const GF& m) const -> GF
        {
            if (cipher_key == 0)
                throw std::runtime_error("Cipher key is not set");

            return m * cipher_key;
        }

        auto decrypt(const GF& c) const -> GF
        {
            if (cipher_key == 0)
                throw std::runtime_error("Cipher key is not set");

            return c / cipher_key;
        }
    private:
        const DHSetup<GF>& dh_setup;
        const GF private_key;
        GF cipher_key{};

        constexpr auto get_random_private_key() -> GF
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int64_t> dis(2, GF::order - 1);

            return dis(gen);
        }
};