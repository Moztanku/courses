#include <iostream>
#include <format>
#include <array>
#include <string_view>
#include <optional>
#include <map>

#include "gen.hpp"
#include "mergesort.hpp"
#include "insertionsort.hpp"
#include "quicksort.hpp"
#include "mysort.hpp"


void TestSort(
    std::span<Key> arr,
    const SortFn sortFn,
    std::optional<std::string_view> name = std::nullopt)
{
    Key::reset_stats();

    sortFn(arr,false);

    auto stats = Key::get_stats();
    bool isSorted = std::is_sorted(arr.begin(), arr.end());

    std::cout 
        << std::format("[{}] {} Stats:\n", isSorted ? "PASS" : "FAIL", name.value_or("Sort"))
        << std::format(" Comparisions: {}\n", stats.comparison_count)
        << std::format(" Assignments: {}\n", stats.assignment_count);
        // << std::format(" Swaps: {}\n", stats.swap_count);
}

#include <memory>

#define STR(x) #x

int main()
{

    // std::array<Key, 50> arr{};
    // GenRandom(arr);

    // std::array<Key, 500> copy{};
    // std::copy(arr.begin(), arr.end(), copy.begin());

    // MergeSort(copy, false);

    // std::cout << mergecount << std::endl;
    // mergecount = 0;

    // MySort(arr, false);

    // std::cout << mergecount << std::endl;


    constexpr size_t n = 1000;
    constexpr size_t k = 100;
    std::array<Key, n> arr{};
    std::array<Key, n> copy{};

    struct Stats
    {
        uint comparison_count;
        uint assignment_count;
    };

    Stats mergeStats = {0, 0};
    Stats merge2Stats = {0, 0};
    Stats mySortStats = {0, 0};

    for (size_t _ = 0; _ < k; _++)
    {
        GenRandom(arr);

        std::copy(arr.begin(), arr.end(), copy.begin());
        Key::reset_stats();
        MergeSort(copy, false);
        mergeStats.comparison_count += Key::get_stats().comparison_count;
        mergeStats.assignment_count += Key::get_stats().assignment_count;

        std::copy(arr.begin(), arr.end(), copy.begin());
        Key::reset_stats();
        MergeSort2(copy, false);
        merge2Stats.comparison_count += Key::get_stats().comparison_count;
        merge2Stats.assignment_count += Key::get_stats().assignment_count;

        std::copy(arr.begin(), arr.end(), copy.begin());
        Key::reset_stats();
        MySort(copy, false);
        mySortStats.comparison_count += Key::get_stats().comparison_count;
        mySortStats.assignment_count += Key::get_stats().assignment_count;
    }

    std::cout << "Results:\n";

    std::cout
        << std::format(
            "MergeSort: Comparisions: {}, Assignments: {}\n",
            mergeStats.comparison_count / (double)k,
            mergeStats.assignment_count / (double)k);

    std::cout
        << std::format(
            "MergeSort2: Comparisions: {}, Assignments: {}\n",
            merge2Stats.comparison_count / (double)k,
            merge2Stats.assignment_count / (double)k);

    std::cout
        << std::format(
            "MySort: Comparisions: {}, Assignments: {}\n",
            mySortStats.comparison_count / (double)k,
            mySortStats.assignment_count / (double)k);

    // constexpr uint k = 1000;
    // constexpr size_t minN = 1;
    // constexpr size_t maxN = 50;

    // // std::array<SortFn, 3> sortFns = {MergeSort, InsertionSort, QuickSort};
    // std::array<SortFn, 2> sortFns = {
    //     MergeSort,
    //     MergeSort2
    // };
    
    // std::map<idx, std::string> sortNames = {
    //     {0, STR(Merge)},
    //     {1, STR(Merge2)}
    // };

    // std::map<std::pair<size_t, size_t>, Stats> stats;

    // for (size_t n = minN; n <= maxN; n++)
    // {
    //     std::vector<Key> arr(n);
    //     std::vector<Key> copy(n);

    //     for (size_t _ = 0; _ < k; _++)
    //     {
    //         GenRandom(arr);
    //         for (idx sortFn = 0; sortFn < sortFns.size(); sortFn++)
    //         {
    //             Key::reset_stats();
                
    //             std::copy(arr.begin(), arr.end(), copy.begin());
    //             sortFns[sortFn](copy, false);

    //             auto s = Key::get_stats();
    //             if (!std::is_sorted(copy.begin(), copy.end()))
    //                 exit(1);

    //             auto pair = std::make_pair(sortFn, n);

    //             if (stats.find(pair) == stats.end())
    //                 stats[pair] = {0, 0};

    //             auto& st = stats[pair];

    //             st.comparison_count += s.comparison_count;
    //             st.assignment_count += s.assignment_count;
    //         }
    //     }
    // }

    // std::cout << "Comparisions/n:\nN";
    // for (idx i = 0; i < sortFns.size(); i++)
    //     std::cout << "\t\t" << sortNames[i];
    // std::cout << std::endl;

    // for (size_t n = minN; n <= maxN; n++)
    // {
    //     std::cout << n;
    //     for (idx i = 0; i < sortFns.size(); i++)
    //     {
    //         auto pair = std::make_pair(i, n);
    //         auto s = stats[pair];
    //         double c = s.comparison_count / (double)k;
    //         std::cout << "\t\t" << c;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "Assignments/n:\nN";
    // for (idx i = 0; i < sortFns.size(); i++)
    //     std::cout << "\t\t" << sortNames[i];
    // std::cout << std::endl;

    // for (size_t n = minN; n <= maxN; n++)
    // {
    //     std::cout << n;
    //     for (idx i = 0; i < sortFns.size(); i++)
    //     {
    //         auto pair = std::make_pair(i, n);
    //         auto s = stats[pair];
    //         double a = s.assignment_count / (double)k;
    //         std::cout << "\t\t" << a;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout
    //     << "Mergesort Stats:\n"
    //     << std::format("N\t\tC\tA\tC/n\tA/n\n");

    // for (size_t n = minN; n <= maxN; n++)
    // {
    //     double c = stats[std::make_pair(0, n)].comparison_count / (double)k;
    //     double a = stats[std::make_pair(0, n)].assignment_count / (double)k;

    //     std::cout 
    //         << std::format("{}\t\t{:.2f}\t{:.2f}\t{:.2f}\t{:.2f}\n", n, c, a, c / n, a / n);
    // }

    // std::cout
    //     << "Comparisions/n:\n"
    //     << std::format(
    //         "N\t\t{}\t\t{}\t\t{}\n",
    //         STR(Merge),
    //         STR(Insert),
    //         STR(Quick)
    //     );
    // for (size_t n = minN; n <= maxN; n++)
    // {
    //     double ms = stats[std::make_pair(0, n)].comparison_count / (double)k;
    //     double is = stats[std::make_pair(1, n)].comparison_count / (double)k;
    //     double qs = stats[std::make_pair(2, n)].comparison_count / (double)k;

    //     std::cout
    //         << std::format(
    //             "{}\t\t{:.2f}\t\t{:.2f}\t\t{:.2f}\n",
    //             n, ms, is, qs
    //         );
    // }

    // std::cout
    //     << "Assignments/n:\n"
    //     << std::format(
    //         "N\t\t{}\t\t{}\t\t{}\n",
    //         STR(Merge),
    //         STR(Insert),
    //         STR(Quick)
    //     );
    // for (size_t n = minN; n <= maxN; n++)
    // {
    //     double ms = stats[std::make_pair(0, n)].assignment_count / (double)k;
    //     double is = stats[std::make_pair(1, n)].assignment_count / (double)k;
    //     double qs = stats[std::make_pair(2, n)].assignment_count / (double)k;

    //     std::cout
    //         << std::format(
    //             "{}\t\t{:.2f}\t\t{:.2f}\t\t{:.2f}\n",
    //             n, ms, is, qs
    //         );
    // }
    // std::array<Key, 1000> arr{};
    // GenRandom(arr);
    
    // std::array<Key, 1000> copy{};

    // std::copy(arr.begin(), arr.end(), copy.begin());
    // TestSort(copy, MergeSort, "Mergesort");

    // std::copy(arr.begin(), arr.end(), copy.begin());
    // TestSort(copy, MySort, "MySort");

    // std::copy(arr.begin(), arr.end(), copy.begin());
    // TestSort(copy, HybridSort, "HybridSort");

    return 0;
}