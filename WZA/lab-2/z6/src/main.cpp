#include <iostream>
#include <vector>

using Natural = std::vector<uint>;

using Subset = std::vector<Natural>;

auto operator<=(const Natural& lhs, const Natural& rhs) -> bool
{
    if (lhs.size() != rhs.size())
        throw std::runtime_error("Natural numbers must have the same size");

    for (size_t i = 0; i < lhs.size(); i++)
        if (lhs[i] > rhs[i])
            return false;

    return true;
}

auto find_minimum_points(const Subset& subset) -> Subset
{
    //  A = {a1, a2, ..., an}  ∀i ai ∈ N^k
    //  M = ∅
    //
    //  outer_loop:
    //  for a ∈ A:
    //      for m ∈ M:
    //          if m ≤ a:
    //              A.remove(a)
    //              continue outer_loop
    //          if a ≤ m:
    //              M.remove(m)
    //      M.add(a)
    //
    //  return M
    Subset A = subset;
    Subset M = {};

    auto it_a = A.begin();
    auto it_m = M.begin();

    outer:
    while (it_a != A.end())
    {
        it_m = M.begin();
        while (it_m != M.end())
        {
            if ((*it_m) <= (*it_a))
            {
                it_a = A.erase(it_a);

                goto outer;
            }

            if ((*it_a) <= (*it_m))
            {
                it_m = M.erase(it_m);
                it_m--;
            }

            it_m++;
        }

        M.push_back(*it_a);
        it_a++;
    }

    return M;
}

auto operator<<(std::ostream& os, const Natural& nat) -> std::ostream&
{
    os << "{";
    for (size_t i = 0; i < nat.size(); i++)
    {
        os << nat[i];
        if (i < nat.size() - 1)
            os << ", ";
    }
    os << "}";
    return os;
}

auto main() -> int
{
    Subset subset =
    {
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 1},
        {2, 2},
        {2, 3},
        {2, 4},
        {3, 1},
        {3, 2},
        {3, 3},
        {3, 4},
        {4, 1},
        {4, 2},
        {4, 3},
        {4, 4}
    };

    Subset minimum_points = find_minimum_points(subset);

    for (const auto& point : minimum_points)
        std::cout << point << ' ';
    std::cout << std::endl;

    Subset s1 = {};

    // {(n, k) : n, k ∈ N, n*k >= 11}
    for (uint n = 1; n <= 13; n++)
        for (uint k = 1; k <= 13; k++)
            if (n*k >= 11)
                s1.push_back({n, k});

    Subset mp_s1 = find_minimum_points(s1);

    for (const auto& point : mp_s1)
        std::cout << point << ' ';
    std::cout << std::endl;

    Subset s2 = {};

    // {(n, k) : n, k ∈ N, (n-10)^2 + (k-10)^2 <= 25}
    for (int n = 1; n <= 100; n++)
        for (int k = 1; k <= 100; k++)
            if ((n - 10)*(n - 10) + (k-10)*(k-10) <= 25)
            if (n >= 0 && k >= 0)
                s2.push_back({
                    static_cast<uint>(n),
                    static_cast<uint>(k)
                });

    Subset mp_s2 = find_minimum_points(s2);

    for (const auto& point : mp_s2)
        std::cout << point << ' ';
    std::cout << std::endl;

    return 0;
};