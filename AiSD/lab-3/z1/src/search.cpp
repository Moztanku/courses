#include <format>
#include <vector>
#include <string>
#include <iostream>

#include "key.hpp"
#include "gen.hpp"
#include "select.hpp"
#include "randomselect.hpp"
#include "quicksort.hpp"

auto operator<<(std::ostream& os, std::vector<Key> arr) -> std::ostream&
{
    for (size_t i = 0; i < arr.size(); i++)
        os << arr[i] << (i == arr.size() - 1 ? "" : " ");

    return os;
}

void printHelp(const int status)
{
    std::cout << "Usage: generate xxx | search (random|select) (k)\n";

    exit(status);
}

auto main(int argc, char* argv[]) -> int
{
    SearchFn search = Select;

    if (argc > 1)
    {
        std::string_view arg = argv[1];

        if (arg == "random")
            search = RandomizedSelect;
        else if (arg == "select")
            search = Select;
        else if (arg == "-h")
            printHelp(EXIT_SUCCESS);
        else
            printHelp(EXIT_FAILURE);
    }

    if (argc != 3)
        printHelp(EXIT_FAILURE);

    int k = std::stoi(argv[2]);

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
    Key found = search(arr, k);

    auto stats = Key::get_stats();

    if (length <= 50)
    {
        std::cout << "Before: " << copy << "\n";
        std::cout << "After: " << arr << "\n";
    }

    QuickSort(copy, false);
    if (length <= 50)
    {
        std::cout << "Sorted: " << copy << "\n";
    }

    std::cout
        << std::format("[{}] Stats:\n", found == copy[k - 1] ? "Found" : ":c")
        << std::format("    - comparisons: {}\n", stats.comparison_count)
        << std::format("    - assignments: {}\n", stats.assignment_count)
        << "    - found: " << found << "\n";

    return EXIT_SUCCESS;
}