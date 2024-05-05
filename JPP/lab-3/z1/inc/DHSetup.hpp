#pragma once

#include <random>
#include <ranges>
#include <type_traits>
#include <format>
#include <algorithm>
#include <vector>

#include "Galois.hpp"

namespace impl
{
    template <typename T>
    struct is_galois : std::false_type{};

    template <int64_t P>
    struct is_galois<Galois<P>> : std::true_type{};

    template <typename T>
    concept is_galois_v = is_galois<T>::value;
};

template <class GF>
class DHSetup
{
    static_assert(impl::is_galois_v<GF>, "GF must be a Galois Field");
    static_assert(is_prime_v<GF::order>, "GF::order must be a prime number");

    public:
        DHSetup() : generator(get_random_generator()) {}

        auto get_generator() const noexcept -> GF
        {
            return generator;
        }

        static auto power(GF base, const GF& exp) noexcept -> GF
        {
            return power(base, exp.get_value());
        }

        static auto power(GF base, uint64_t exp) noexcept -> GF
        {
            GF result{1};

            while (exp > 0)
            {
                if (exp % 2 == 1)
                    result *= base;

                base *= base;
                exp /= 2;
            }

            return result;
        }

    private:
        const GF generator;

        static auto get_random_generator() -> GF
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int64_t> dis(2, GF::order - 1);

            GF generator{};

            do generator = dis(gen);
            while (!is_generator(generator));

            return generator;
        }

        static auto is_generator(const GF& generator) -> bool
        {
            constexpr auto phi = GF::order - 1;
            static std::vector<int64_t> prime_factors = get_prime_factors(phi);

            for (const auto factor : prime_factors)
                if (power(generator, phi / factor) == 1)
                    return false;

            return true;
        }

        static auto get_prime_factors(int64_t phi) -> std::vector<int64_t>
        {
            std::vector<int64_t> prime_factors{};

            for (int64_t i = 2; i * i <= phi; i++)
            {
                while (phi % i == 0)
                {
                    if (std::binary_search(prime_factors.begin(), prime_factors.end(), i) == false)
                        prime_factors.push_back(i);

                    phi /= i;
                }
            }

            if (phi > 1)
                prime_factors.push_back(phi);

            return prime_factors;
        }
};