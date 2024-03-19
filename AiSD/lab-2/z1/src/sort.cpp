#include <iostream>
#include <format>

#include "insertionsort.hpp"
#include "quicksort.hpp"
#include "hybridsort.hpp"

void printHelp(const int status)
{
    std::cout << "Usage: generate xxx | sort (insertion|quick|hybrid) (simpleprint)\n";

    exit(status);
}

int main(int argc, char *argv[])
{
    SortFn sort = QuickSort;

    if (argc > 1)
    {
        std::string_view arg = argv[1];
        if (arg == "insertion")
            sort = InsertionSort;
        else if (arg == "quick")
            sort = QuickSort;
        else if (arg == "hybrid")
            sort = HybridSort;
        else if (arg == "-h")
            printHelp(0);
        else
            printHelp(1);
    }

    bool prettyprint = true;

    if (argc == 3)
    {
        std::string_view arg = argv[2];
        if (arg == "nopp")
            prettyprint = false;
        else
            printHelp(1);
    }

    size_t length;

    std::cin >> length;

    std::vector<Key> arr(length);
    std::vector<Key> copy(length);

    for (auto &key : arr)
    {
        int value;
        std::cin >> value;
        key = value;
    }

    std::copy(arr.begin(), arr.end(), copy.begin());

    Key::reset_stats();
    sort(
        copy,
        prettyprint
    );

    auto stats = Key::get_stats();
    const bool is_sorted = std::is_sorted(copy.begin(), copy.end());

    if (length < 40 && prettyprint)
    {
        std::cout << "Org. array: ";
        for (const auto &key : arr)
            std::cout << key << ' ';
        std::cout << '\n';

        std::cout << "Srt. array: ";
        for (const auto &key : arr)
            std::cout << key << ' ';
        std::cout << '\n';
    }

    if (prettyprint)
    std::cout
        << std::format("[{}] Stats:\n", is_sorted ? "Sorted" : ":c")
        << std::format("    - comparisons: {}\n", stats.comparison_count)
        << std::format("    - assignments: {}\n", stats.assignment_count);
    else
        std::cout << std::format("{} {}\n", stats.comparison_count, stats.assignment_count);
}