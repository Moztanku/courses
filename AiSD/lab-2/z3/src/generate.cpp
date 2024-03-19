#include <iostream>
#include <string_view>

#include "gen.hpp"

void printHelp(const int status)
{
    std::cout << "Usage: generate (1 - 1000000) [random|sorted|reversed]\n";

    exit(status);
}

int main(int argc, char *argv[]) {
    GenFn generator = GenRandom;

    if (argc < 2)
        printHelp(1);

    if (std::string_view(argv[1]) == "-h")
        printHelp(0);

    size_t length{};

    try { length = std::stoul(argv[1]); }
    catch (...) { printHelp(1); }

    if (length > 1000000)
        printHelp(1);

    if (argc > 2) {
        std::string_view arg = argv[2];

        if (arg == "random")
            generator = GenRandom;
        else if (arg == "sorted")
            generator = GenSorted;
        else if (arg == "reversed")
            generator = GenReversed;
        else
            printHelp(1);
    }

    std::vector<Key> arr(length);
    generator(arr);

    std::cout << length << '\n';
    for (const auto &key : arr)
        std::cout << key << '\n';
}