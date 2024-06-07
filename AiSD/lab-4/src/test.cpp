#include <iostream>
#include <format>
#include <vector>
#include <memory>

#include "BSTree.hpp"

auto main() -> int
{
    std::unique_ptr<ITree> tree = std::make_unique<BSTree>();

    std::vector<int> keys = {50, 30, 70, 20, 40, 60, 65, 80};

    for (auto key : keys)
        tree->insert(key);

    tree->print();
    tree->remove(50);

    std::cout << "\n\n";
    tree->print();
}