#include <random>
#include <ranges>
#include <type_traits>
#include <format>
#include <array>

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

        static auto power(const GF& base, uint64_t exp) noexcept -> GF
        {
            // TODO: Implement a more efficient algorithm
            GF result{1};

            for (uint64_t i = 0; i < exp; ++i)
                result *= base;

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
            constexpr auto prime_factors = get_prime_factors<phi>();

            for (const auto factor : prime_factors)
                if (power(generator, phi / factor) == 1)
                    return false;

            return true;
        }

        template <int64_t phi>
        consteval static auto get_num_of_prime_factors() -> int64_t
        {
            int64_t num_of_prime_factors = 0;

            constexpr auto is_prime = [](int64_t n) -> bool
            {
                if (n <= 1)
                    return false;
                if (n <= 3)
                    return true;
                if (n % 2 == 0 || n % 3 == 0)
                    return false;

                for (int64_t i = 5; i * i <= n; i += 6)
                    if (n % i == 0 || n % (i + 2) == 0)
                        return false;

                return true;
            };

            for (int64_t i = 2; i <= phi / 2; ++i)
                if (is_prime(i) && phi % i == 0)
                    ++num_of_prime_factors;

            return num_of_prime_factors;
        }

        template <int64_t phi>
        consteval static auto get_prime_factors() -> std::array<int64_t, get_num_of_prime_factors<phi>()>
        {
            std::array<int64_t, get_num_of_prime_factors<phi>()> prime_factors{};

            constexpr auto is_prime = [](int64_t n) -> bool
            {
                if (n <= 1)
                    return false;
                if (n <= 3)
                    return true;
                if (n % 2 == 0 || n % 3 == 0)
                    return false;

                for (int64_t i = 5; i * i <= n; i += 6)
                    if (n % i == 0 || n % (i + 2) == 0)
                        return false;

                return true;
            };

            int64_t index = 0;

            for (int64_t i = 2; i <= phi / 2; ++i)
                if (is_prime(i) && phi % i == 0)
                    prime_factors[index++] = i;

            return prime_factors;
        }
};

template <class GF>
class User
{
    static_assert(impl::is_galois_v<GF>, "GF must be a Galois Field");
    static_assert(is_prime_v<GF::order>, "GF::order must be a prime number");

    public:
        User(const DHSetup<GF>& dh_setup) : dh_setup(dh_setup) {}

        auto get_public_key() const noexcept -> GF;
        void set_key(const GF& other_public_key);

        auto encrypt(const GF& m) const noexcept -> GF;
        auto decrypt(const GF& c) const noexcept -> GF;
    private:
        const DHSetup<GF>& dh_setup;
        const GF private_key;
};