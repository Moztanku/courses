#pragma once

#include <cstdint>

namespace impl
{
    consteval bool is_prime(int64_t n)
    {
        if (n <= 1)
            return false;

        for (int64_t i = 2; i * i <= n; i++)
            if (n % i == 0)
                return false;

        return true;
    }
};

template <int64_t N>
struct is_prime
{
    inline static constexpr bool value = impl::is_prime(N);
};

template <int64_t N>
constexpr bool is_prime_v = is_prime<N>::value;
