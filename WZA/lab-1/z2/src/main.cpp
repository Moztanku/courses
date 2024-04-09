#include <iostream>
#include <vector>
#include <algorithm>
#include <format>
#include <cmath>

auto is_equal(const double a, const double b) -> bool
{
    constexpr double epsilon = 1e-7;
    return std::abs(a - b) < epsilon;
}

using Polynomial = std::vector<double>;

auto to_string(const Polynomial& p) -> std::string
{
    if (p.empty())
        return "0";

    std::string result = "";

    for (size_t i = 0; i < p.size(); i++)
    {
        double a = p[i];

        if (is_equal(a, 0.0))
            continue;


        result += 
            i == 0 ? std::format("{}", a) : std::format("{}x^{}", a, i);

        if (i < p.size() - 1)
            result += " + ";
    }

    return result;
}

auto LT(const Polynomial& p) -> double
{
    return p.empty() ? 0.0 : p.back();
}

/*

PDR(f,g) {
    p = f; q = 0; r = 0;

    while p != 0 do
    {
        if LT(g) | LT(p)
        {
            q = q + LT(p) / LT(g);
            p = p - (LT(p) / LT(g)) * g;
        }
        else
        {
            r = p;
            p = 0;
        }
    }

    return (q, r);
}


*/

auto div(const Polynomial& f, const Polynomial& g) -> std::pair<Polynomial, Polynomial>
{
    Polynomial p = f;
    Polynomial q(p.size() - g.size() + 1);
    Polynomial r(0);

    while (LT(p) != 0)
    {
        if (p.size() >= g.size() || (p.size() == g.size() && LT(p) >= LT(g)))
        {
            // q = q + LT(p) / LT(g);
            // LT(p) / LT(g) : ax^m / bx^n = (a / b) * x^(m - n)
            double a = std::floor(LT(p) / LT(g));
            size_t n = p.size() - g.size();
            q[n] += a;

            // p = p - (LT(p) / LT(g)) * g;
            for (size_t i = 0; i < g.size(); ++i)
            {
                p[n + i] -= a * g[i];
            }

            std::cout << to_string(p) << std::endl;
            std::cout << to_string(q) << std::endl;

            // Remove leading zeros
            while (!p.empty() && is_equal(p.back(), 0.0))
            {
                p.pop_back();
            }
        }
        else
        {
            r = p;
            p.clear();
        }
    }

    // Remove leading zeros
    while (!q.empty() && is_equal(q.back(), 0.0))
    {
        q.pop_back();
    }

    return {q, r};
}

auto gcd(const Polynomial& f, const Polynomial& g) -> Polynomial
{
    if (g.empty())
        return f;

    Polynomial r = div(f, g).second;

    // Polynomial r = f;

    // for (size_t i = 0; i < r.size(); i++)
    // {
    //     r[i] -= g[i];
    // }

    // while (!r.empty() && is_equal(r.back(), 0.0))
    // {
    //     r.pop_back();
    // }

    std::cout << to_string(f) << " / " << to_string(g) << " = " << to_string(r) << std::endl;

    return 
        g.size() > r.size() ? gcd(g, r) :
        r.size() > g.size() ? gcd(r, g) :
              LT(g) > LT(r) ? gcd(g, r) :
                              gcd(r, g);
}

int main()
{
    Polynomial f{1.0,0.0,0.0,1.0,1.0};
    Polynomial g{0.0,0.0,1.0};

    auto [q, r] = div(f, g);

    std::cout <<
        std::format
        (
            "{} / {} = {} + {}",
            to_string(f),
            to_string(g),
            to_string(q),
            to_string(r)
        ) << std::endl;

    f = {1.0,0.0,1.0};
    g = {1.0,2.0,1.0};

    auto gcd_result = gcd(f, g);

    std::cout <<
        std::format
        (
            "NWD({} / {}) = {}",
            to_string(f),
            to_string(g),
            to_string(gcd_result)
        ) << std::endl;
}