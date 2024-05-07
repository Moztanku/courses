#include <iostream>
#include <format>
#include <vector>

#include "key.hpp"
#include "binarysearch.hpp"

void printHelp(const int status)
{
    std::cout << "Usage: generate xxx | bsearch (k)\n";

    exit(status);
}

auto main(int argc, char* argv[]) -> int
{
    if (argc > 1)
    {
        std::string_view arg = argv[1];

        if (arg == "-h")
            printHelp(EXIT_SUCCESS);
    }

    if (argc != 2)
        printHelp(EXIT_FAILURE);

    const int k = std::stoi(argv[1]);

    size_t length;

    std::cin >> length;

    std::vector<Key> arr(length);

    for (auto &key : arr)
    {
        int value;
        std::cin >> value;

        key = Key(value);
    }

    Key::reset_stats();

    const Key searched = Key(k);
    const bool found = binary_search(arr, searched);

    auto stats = Key::get_stats();

    std::cout
        << std::format("[{}] Stats:\n", found ? "Found" : "Not Found")
        << std::format("  - Comparisons: {}\n", stats.comparison_count);

    return found ? EXIT_SUCCESS : EXIT_FAILURE;
}