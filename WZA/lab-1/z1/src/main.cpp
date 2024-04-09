#include <iostream>
#include <utility>
#include <cmath>
#include <format>

template <typename T>
struct ComplexBase
{
    T real;
    T imag;
};

template <typename T>
auto operator-(const ComplexBase<T> &x, const ComplexBase<T> &y) -> ComplexBase<T>
{
    return {x.real - y.real, x.imag - y.imag};
}

template <typename T>
auto operator*(const ComplexBase<T> &x, const ComplexBase<T> &y) -> ComplexBase<T>
{
    return {
        (x.real * y.real) - (x.imag * y.imag),
        (x.real * y.imag) + (x.imag * y.real) 
    };
}

template <typename T>
auto norm(const ComplexBase<T> &x) -> T
{
    return x.real * x.real + x.imag * x.imag;
}

template <typename T>
auto conj(const ComplexBase<T> &x) -> ComplexBase<T>
{
    return {x.real, -x.imag};
}

using Galois = ComplexBase<int>;
using Complex = ComplexBase<double>;

struct Result
{
    Galois quotient;
    Galois remainder;
};

auto div(const Galois &x, const Galois &y) -> Result
{
    Galois a1 = x * conj(y);
    Complex s = {
        static_cast<double>(a1.real),
        static_cast<double>(a1.imag)};
    s.real /= norm(y);
    s.imag /= norm(y);

    Galois q = {
        static_cast<int>(std::round(s.real)),
        static_cast<int>(std::round(s.imag))
    };

    return {q, x - (y * q)};
}

auto gcd(const Galois &x, const Galois &y) -> Galois
{
    if (y.real == 0 && y.imag == 0)
    {
        return x;
    }

    auto [_, remainder] = div(x, y);

    return gcd(y, remainder);
}

auto lcm(const Galois &x, const Galois &y) -> Galois
{
    return div(x * y, gcd(x, y)).quotient;
}

int main()
{
    Galois x = {5, 1};
    Galois y = {1, 2};

    auto result = div(x, y);

    std::cout <<
        std::format
        (
            "({} + {}i) / ({} + {}i) = ({} + {}i) + ({} + {}i)",
            x.real, x.imag,
            y.real, y.imag,
            result.quotient.real, result.quotient.imag,
            result.remainder.real, result.remainder.imag
        ) << std::endl;

    x = {22, 0};
    y = {6, 0};
    auto gcd_result = gcd(x, y);

    std::cout <<
        std::format
        (
            "GCD({} + {}i, {} + {}i) = {} + {}i",
            x.real, x.imag,
            y.real, y.imag,
            gcd_result.real, gcd_result.imag
        ) << std::endl;

    x = {24,0};
    y = {44,0};

    auto lcm_result = lcm(x, y);

    std::cout <<
        std::format
        (
            "LCM({} + {}i, {} + {}i) = {} + {}i",
            x.real, x.imag,
            y.real, y.imag,
            lcm_result.real, lcm_result.imag
        ) << std::endl;

    x = {3, 4};
    y = {1, 3};

    Galois c = gcd(x, y);
    Galois d = lcm(x, y);

    std::cout <<
        std::format
        (
            "<{} + {}i, {} + {}i> = <{} + {}i>",
            x.real, x.imag,
            y.real, y.imag,
            c.real, c.imag
        ) << std::endl;

    std::cout <<
        std::format
        (
            "<{} + {}i>∩<{} + {}i> = <{} + {}i>",
            x.real, x.imag,
            y.real, y.imag,
            d.real, d.imag
        ) << std::endl;
}