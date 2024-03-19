#include <iostream>
#include <format>
#include <array>
#include <string_view>
#include <optional>

#include "gen.hpp"
#include "dpquicksort.hpp"

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
    std::array<Key, 50> arr{};
    GenRandom(arr);

    std::cout << "Before Sort:\n";
    for (const auto& key : arr)
        std::cout << key << " ";
    std::cout << std::endl;

    DPQuickSort(arr, false);

    std::cout << "After Sort:\n";
    for (const auto& key : arr)
        std::cout << key << " ";
    std::cout << std::endl;
    
    // std::array<Key, 1000> copy{};

    // std::copy(arr.begin(), arr.end(), copy.begin());
    // TestSort(copy, InsertionSort, "InsertionSort");

    // std::copy(arr.begin(), arr.end(), copy.begin());
    // TestSort(copy, QuickSort, "QuickSort");

    // std::copy(arr.begin(), arr.end(), copy.begin());
    // TestSort(copy, HybridSort, "HybridSort");

    return 0;
}