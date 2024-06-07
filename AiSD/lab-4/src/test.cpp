#include <iostream>
#include <memory>

#include <span>
#include <vector>
#include <algorithm>
#include <random>

#include "ITree.hpp"
#include "BSTree.hpp"
#include "RBTree.hpp"
// #include "SplayTree.hpp"

auto generate_random_values(std::span<int> arr) -> void
{
    std::generate(arr.begin(), arr.end(), []() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 100);

        return dist(gen); 
    });
}

auto main() -> int
{
    std::unique_ptr<ITree> tree = std::make_unique<RBTree>(500000);

    std::vector<int> values(40);
    generate_random_values(values);

    for (auto value : values)
        tree->insert(value);

    for (auto i = 0; i < values.size(); i += 2)
        tree->remove(values[i]);

    std::cout << "Height: " << tree->height() << std::endl;
    std::cout << "Size: " << tree->size() << std::endl;

    tree->print();

    return 0;
}