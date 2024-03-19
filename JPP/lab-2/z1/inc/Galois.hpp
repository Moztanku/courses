#pragma once

#include <cstdint>

#include "is_prime.hpp"

template <int64_t P>
class Galois
{
    static_assert(is_prime_v<P>, "P must be a prime number");
    public:
        constexpr Galois() = default;
        constexpr Galois(int64_t m_value) : m_value(m_value % order) {}

        constexpr auto operator=(const Galois& other) -> Galois&
        {
            m_value = other.m_value;
            return *this;
        }

        constexpr auto operator+=(const Galois& other) -> Galois&
        {
            m_value = (m_value + other.m_value) % order;
            return *this;
        }

        constexpr auto operator-=(const Galois& other) -> Galois&
        {
            const auto inverse = -other;
            *this += inverse;
            return *this;
        }

        constexpr auto operator*=(const Galois& other) -> Galois&
        {
            m_value = (m_value * other.m_value) % order;
            return *this;
        }

        constexpr auto operator/=(const Galois& other) -> Galois&
        {
            const auto inverse = ~other;
            *this *= inverse;
            return *this;
        }

        constexpr friend auto operator<=>(const Galois& l, const Galois& r) = default;

        constexpr friend auto operator+(const Galois& l, const Galois& r) -> Galois
        {
            return Galois((l.m_value + r.m_value) % order);
        }

        constexpr friend auto operator-(const Galois& l, const Galois& r) -> Galois
        {
            const auto inverse = -r;
            return l + inverse;
        }

        constexpr friend auto operator*(const Galois& l, const Galois& r) -> Galois
        {
            return Galois((l.m_value * r.m_value) % order);
        }

        constexpr friend auto operator/(const Galois& l, const Galois& r) -> Galois
        {
            const auto inverse = ~r;
            return l * inverse;
        }

        constexpr friend auto operator-(const Galois& l) -> Galois
        {
            return Galois(order - l.m_value);
        }

        constexpr friend auto operator~(const Galois& l) -> Galois
        {
            return Galois(egcd(l.m_value));
        }

        constexpr friend auto operator<<(std::ostream& os, const Galois& l) -> std::ostream&
        {
            return os << l.m_value;
        }

        constexpr static int64_t order = order;
    private:
        int64_t m_value{};

        static constexpr auto egcd(int64_t a) -> int64_t
        {
            int64_t b = order;

            int64_t x = 1;
            int64_t y = 0;

            int64_t x1 = 0;
            int64_t y1 = 1;

            while (b != 0) {
                const int64_t q = a / b;

                const int64_t x2 = x - q * x1;
                x = x1;
                x1 = x2;

                const int64_t y2 = y - q * y1;
                y = y1;
                y1 = y2;

                const int64_t temp = a;
                a = b;
                b = temp - q * b;
            }

            if (x < 0)
                x += order;

            return x;
        }
};
