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
        if (p.size() >= g.size())
        {
            // q = q + LT(p) / LT(g);
            // LT(p) / LT(g) : ax^m / bx^n = (a / b) * x^(m - n)
            double a = LT(p) / LT(g);
            size_t n = p.size() - g.size();
            q[n] += a;

            // p = p - (LT(p) / LT(g)) * g;
            for (size_t i = 0; i < g.size(); ++i)
            {
                p[n + i] -= a * g[i];
            }

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

    return 
        g.size() > r.size() ? gcd(g, r) :
        r.size() > g.size() ? gcd(r, g) :
              LT(g) > LT(r) ? gcd(g, r) :
                              gcd(r, g);
}

auto lcm(const Polynomial& f, const Polynomial& g) -> Polynomial
{
    Polynomial mul((f.size() - 1) + (g.size() - 1) + 1, 0.0);

    for (size_t i = 0; i < f.size(); i++)
        for (size_t j = 0; j < g.size(); j++)
            if (!is_equal(f[i], 0.0) && !is_equal(g[j], 0.0))
                mul[i + j] += f[i] * g[j];

    return div(mul, gcd(f, g)).first;
}