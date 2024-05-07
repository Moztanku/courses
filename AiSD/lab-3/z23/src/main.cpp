#include <map>
#include <format>
#include <vector>
#include <string>
#include <ranges>
#include <iostream>

#include "key.hpp"
#include "gen.hpp"
#include "select.hpp"
#include "kselect.hpp"
#include "randomselect.hpp"
#include "quicksort.hpp"

auto main() -> int
{
    constexpr uint m = 50;

    constexpr uint n_min = 100;
    constexpr uint n_max = 50000;
    constexpr uint n_step = 100;

    const std::map<idx, const SearchFn> SearchAlgorithms = 
    {
        {0, RandomizedSelect},
        {1, KSelect<3>},
        {2, KSelect<5>},
        {3, KSelect<7>},
        {4, KSelect<9>}
    };

    const std::map<idx, std::string> SearchAlgorithmsNames = 
    {
        {0, "RandomizedSelect"},
        {1, "Select<3>"},
        {2, "Select<5>"},
        {3, "Select<7>"},
        {4, "Select<9>"}
    };

    struct Result
    {
        double comparison_cnt;
        double assignment_cnt;
    };

    std::map<std::pair<idx, uint>, Result> results;

    auto Ns = std::views::iota(n_min / n_step, (n_max + n_step) / n_step)
            | std::views::transform([n_step](auto i) { return n_step * i; });
    GenFn gen = GenRandom;

    for (auto N : Ns)
    {
        std::vector<Key> keys(N);
        std::vector<Key> keys_copy(N);

        for (idx i = 0; i < SearchAlgorithms.size(); i++)
            results[{i, N}] = {0.0, 0.0};

        for (auto _ = 0; _ < m; _++)
        {
            gen(keys);
            idx searched = rand() % N + 1;

            for (idx i = 0; i < SearchAlgorithms.size(); i++)
            {
                const SearchFn& search = SearchAlgorithms.at(i);
                keys_copy = keys;

                Key::reset_stats();
                Key found = search(keys_copy, searched);

                if (static_cast<uint>(found) != searched - 1)
                {
                    std::cerr << "Error: Search algorithm " << SearchAlgorithmsNames.at(i) << " failed to find the element\n";
                    exit(EXIT_FAILURE);
                }

                auto stats = Key::get_stats();
                auto& res = results[{i, N}];

                res.assignment_cnt +=
                    stats.assignment_count / static_cast<double>(m);
                res.comparison_cnt +=
                    stats.comparison_count / static_cast<double>(m);
            }
        }
    }

    for (auto N : Ns)
        for (idx i = 0; i < SearchAlgorithms.size(); i++)
            std::cout << std::format(
                "{} {} {:.2f} {:.2f}\n",
                N,
                SearchAlgorithmsNames.at(i),
                results[{i, N}].comparison_cnt,
                results[{i, N}].assignment_cnt
            );

    return EXIT_SUCCESS;
}