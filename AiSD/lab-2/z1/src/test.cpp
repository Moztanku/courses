#include <iostream>
#include <format>
#include <array>
#include <string_view>
#include <optional>

#include "gen.hpp"
#include "quicksort.hpp"
#include "insertionsort.hpp"
#include "hybridsort.hpp"

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

int main()
{
    std::array<Key, 1000> arr{};
    GenRandom(arr);
    
    std::array<Key, 1000> copy{};

    std::copy(arr.begin(), arr.end(), copy.begin());
    TestSort(copy, InsertionSort, "InsertionSort");

    std::copy(arr.begin(), arr.end(), copy.begin());
    TestSort(copy, QuickSort, "QuickSort");

    std::copy(arr.begin(), arr.end(), copy.begin());
    TestSort(copy, HybridSort, "HybridSort");

    return 0;
}