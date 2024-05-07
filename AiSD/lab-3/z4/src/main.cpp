#include <iostream>
#include <format>

#include <map>
#include <span>
#include <vector>
#include <ranges>

#include <random>
#include <chrono>

#include "gen.hpp"
#include "sort.hpp"
#include "binarysearch.hpp"

using GetIndexFn = std::function<Key(std::span<Key>)>;

const GetIndexFn GetBegin = [](std::span<Key> arr) -> Key
{
    static auto rng = std::mt19937(std::random_device()());

    idx l = 0;
    idx r = arr.size() / 10;

    idx i = std::uniform_int_distribution<idx>(l, r)(rng);
    return arr[i];
};

const GetIndexFn GetMid = [](std::span<Key> arr) -> Key
{
    static auto rng = std::mt19937(std::random_device()());

    idx l = (arr.size() / 10) * 4;
    idx r = (arr.size() / 10) * 6;

    idx i = std::uniform_int_distribution<idx>(l, r)(rng);
    return arr[i];
};

const GetIndexFn GetEnd = [](std::span<Key> arr) -> Key
{
    static auto rng = std::mt19937(std::random_device()());

    idx l = arr.size() - arr.size() / 10;
    idx r = arr.size() - 1;

    idx i = std::uniform_int_distribution<idx>(l, r)(rng);
    return arr[i];
};

const GetIndexFn GetRandom = [](std::span<Key> arr) -> Key
{
    static auto rng = std::mt19937(std::random_device()());

    idx l = 0;
    idx r = arr.size() - 1;

    idx i = std::uniform_int_distribution<idx>(l, r)(rng);
    return arr[i];
};

const GetIndexFn GetMissing = [](std::span<Key> arr) -> Key
{
    static auto rng = std::mt19937(std::random_device()());

    idx l = 0;
    idx r = arr.size() - 1;

    Key k = std::binomial_distribution<>(1, 0.5)(rng) == 1 ? arr[l] - 1 : arr[r] + 1;

    return k;
};

auto main() -> int
{
    constexpr uint M = 1000;

    constexpr uint N_MIN = 1000;
    constexpr uint N_MAX = 100000;
    constexpr uint N_STEP = 1000;

    const std::map<idx, const GetIndexFn> GetIndexFns = 
    {
        {0, GetBegin},
        {1, GetMid},
        {2, GetEnd},
        {3, GetRandom},
        {4, GetMissing}
    };

    const std::map<idx, std::string> GetIndexFnsNames = 
    {
        {0, "Begining"},
        {1, "Middle"},
        {2, "End"},
        {3, "Random"},
        {4, "Missing"}
    };

    struct Result
    {
        double comparison_cnt;
        double time_ns;
    };

    std::map<std::pair<idx, uint>, Result> results;

    const auto Ns = std::views::iota(N_MIN / N_STEP, (N_MAX + N_STEP) / N_STEP)
            | std::views::transform([N_STEP](auto i) { return N_STEP * i; });

    // Do preheat
    for (auto N : Ns)
    {
        std::vector<Key> keys(N);
        GenSorted(keys);
        for (auto _ = 0; _ < M; _++)
            for (idx i = 0; i < GetIndexFns.size(); i++)
                binary_search(keys, GetIndexFns.at(i)(keys));
    }

    for (auto N : Ns)
    {
        std::vector<Key> keys(N);
        GenSorted(keys);

        for (idx i = 0; i < GetIndexFns.size(); i++)
            results[{i, N}] = {0.0, 0.0};

        for (auto _ = 0; _ < M; _++)
        {
            for (idx i = 0; i < GetIndexFns.size(); i++)
            {
                const GetIndexFn& getIndex = GetIndexFns.at(i);

                Key searched = getIndex(keys);

                Key::reset_stats();

                auto start = std::chrono::high_resolution_clock::now();
                const bool result = binary_search(keys, searched);
                auto end = std::chrono::high_resolution_clock::now();

                auto duration = 
                    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

                if ((result == false && i != 4) || (result == true && i == 4))
                {
                    std::cerr << "Error: " << GetIndexFnsNames.at(i) << std::endl;
                    exit(EXIT_FAILURE);
                }

                auto stats = Key::get_stats();
                auto& res = results[{i, N}];

                res.comparison_cnt +=
                    stats.comparison_count / static_cast<double>(M);
                res.time_ns +=
                    duration.count() / static_cast<double>(M);
            }
        }
    }

    for (auto N : Ns)
        for (idx i = 0; i < GetIndexFns.size(); i++)
            std::cout << std::format(
                "{} {} {:.2f} {:.2f}\n",
                N,
                GetIndexFnsNames.at(i),
                results[{i, N}].comparison_cnt,
                results[{i, N}].time_ns
            );
}