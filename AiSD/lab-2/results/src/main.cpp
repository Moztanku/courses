#include <iostream>
#include <format>
#include <string>

#include <map>
#include <vector>
#include <ranges>

#include "gen.hpp"
#include "key.hpp"

#include "insertionsort.hpp"
#include "quicksort.hpp"
#include "hybridsort.hpp"
#include "mergesort.hpp"
#include "mysort.hpp"
#include "dpquicksort.hpp"

struct Arguments
{
    size_t K{};
};

void printHelp(uint status, const char* programName)
{
    std::cout << std::format("Usage: {} <K>\n", programName);

    exit(status);
}

auto getArguments(int argc, char* argv[]) -> Arguments
{
    Arguments args;

    if (argc != 2)
        printHelp(1, argv[0]);
    
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help")
        printHelp(0, argv[0]);

    args.K = std::stoul(arg);

    return args;
}

int main(int argc, char* argv[])
{
    auto args = getArguments(argc, argv);

    const std::map<idx, const SortFn> SortingAlgorithms =
    {
        // {0, InsertionSort},
        {0, QuickSort},
        {1, HybridSort},
        {2, MergeSort},
        {3, MySort},
        {4, DPQuickSort}
    };

    const std::map<idx, std::string> SortingAlgorithmsNames =
    {
        // {0, "Insert"},
        {0, "Quick"},
        {1, "Hybrid"},
        {2, "Merge"},
        {3, "MySort"},
        {4, "DPQuick"}
    };

    struct Result
    {
        uint comparision_cnt;
        uint assignment_cnt;
    };

    std::map<std::pair<idx, size_t>, Result> results;

    auto Ns = std::views::iota(1, 50 + 1) | std::views::transform([](auto i) { return 1000 * i; });
    GenFn gen = GenRandom;

    for (auto N : Ns)
    {
        std::vector<Key> keys(N);
        std::vector<Key> keys_copy(N);

        for (idx i = 0; i < SortingAlgorithms.size(); i++)
        {
            results[{i, N}] = {0, 0};
        }

        for (auto _ = 0; _ < args.K; _++)
        {
            gen(keys);
            
            for (idx i = 0; i < SortingAlgorithms.size(); i++)
            {
                const SortFn& sort = SortingAlgorithms.at(i);
                keys_copy = keys;

                Key::reset_stats();
                sort(keys_copy, false);

                auto stats = Key::get_stats();
                auto& res = results[{i, N}];

                res.assignment_cnt += stats.assignment_count;
                res.comparision_cnt += stats.comparison_count;

                if (!std::is_sorted(keys_copy.begin(), keys_copy.end()))
                {
                    std::cerr << "Error: Sorting algorithm " << SortingAlgorithmsNames.at(i) << " failed to sort the array\n";
                    exit(1);
                }
            }
        }
    }

    for (auto N : Ns)
        for (idx i = 0; i < SortingAlgorithms.size(); i++)
        {
            std::cout << std::format(
                "{} {} {} {}\n",
                N, 
                SortingAlgorithmsNames.at(i),
                results[{i, N}].comparision_cnt / static_cast<double>(args.K),
                results[{i, N}].assignment_cnt / static_cast<double>(args.K)
            );
        }
}