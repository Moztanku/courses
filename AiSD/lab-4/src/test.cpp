#include <iostream>
#include <format>
#include <memory>

#include <span>
#include <vector>
#include <algorithm>
#include <random>
#include <ranges>

#include "ITree.hpp"
#include "BSTree.hpp"
#include "RBTree.hpp"
#include "SplayTree.hpp"

auto generate_sorted_values(std::span<int> arr) -> void
{
    std::iota(arr.begin(), arr.end(), 1);
}

auto generate_random_values(std::span<int> arr) -> void
{
    generate_sorted_values(arr);

    static std::random_device rd;
    static std::mt19937 g(rd());
    
    std::shuffle(arr.begin(), arr.end(), g);
}

auto test_tree(std::unique_ptr<ITree>& tree, std::span<int> values) -> void
{
    for (auto value : values)
    {
        tree->insert(value);

        std::cout << std::format(
            "Inserting {}, height: {}, size: {}\n",
            value, tree->height(), tree->size()
        );

        tree->print();
    }

    generate_random_values(values);
    for (auto value : values)
    {
        std::cout << std::format(
            "Removing {}, height: {}, size: {}\n",
            value, tree->height() - 1, tree->size() - 1
        );
        
        tree->remove(value);
        tree->print();
    }
}

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <BS | RB | Splay>\n";
        return 1;
    }
    std::string type = argv[1];

    std::unique_ptr<ITree> tree{};
    if (type == "BS")
        tree = std::make_unique<BSTree>();
    else if (type == "RB")
        tree = std::make_unique<RBTree>();
    else if (type == "Splay")
        tree = std::make_unique<SplayTree>();
    else 
    {
        std::cerr << "Usage: " << argv[0] << " <BS | RB | Splay>\n";
        return 1;
    }

    constexpr int N = 20;
    std::vector<int> values(N);

    generate_sorted_values(values);
    test_tree(tree, values);

    if (type == "BS")
        tree = std::make_unique<BSTree>();
    else if (type == "RB")
        tree = std::make_unique<RBTree>();
    else
        tree = std::make_unique<SplayTree>();

    generate_random_values(values);
    test_tree(tree, values);

    return 0;
}
