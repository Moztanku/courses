#include <iostream>
#include<format>
#include <string_view>

#include "Graph.hpp"
#include "Kruskal.hpp"
#include "Prim.hpp"
#include "Tree.hpp"

auto print_help(const std::string_view exec, int status) -> void
{
    std::cout << std::format("Usage: {} <Kruskal/Prim> <N>\n", exec);

    std::exit(status);
}

auto main(int argc, char** argv) -> int
{
    if (argc == 2 && (argv[1] == std::string_view("-h") || argv[1] == std::string_view("--help")))
        print_help(argv[0], 0);

    if (argc != 3)
        print_help(argv[0], 1);

    std::string_view alg_name = argv[1];

    auto algorithm = 
        alg_name == "Kruskal" ? kruskal :
        alg_name == "Prim"    ? prim    :
        nullptr;

    if (algorithm == nullptr)
        print_help(argv[0], 1);

    auto N = std::stoi(argv[2]);

    if (!(N > 0))
        print_help(argv[0], 1);

    Graph full_graph(N);

    Graph mst = algorithm(full_graph);

    Tree tree(mst);

    tree.print();

    return 0;
}
