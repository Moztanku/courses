#include <iostream>
#include <format>
#include <vector>
#include <memory>

#include "BSTree.hpp"

auto main() -> int
{
    std::unique_ptr<ITree> tree = std::make_unique<BSTree>();

    std::vector<int> keys = {5, 4, 3, 5, 7, 10, 11};

    for (auto key : keys) {
        tree->insert(key);
        std::cout << std::format("Inserted key: {}, Tree height: {}\n", key, tree->height());
    }
}