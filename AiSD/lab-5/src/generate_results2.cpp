#include <iostream>
#include <format>
#include <map>

#include "Graph.hpp"
#include "Kruskal.hpp"
#include "Prim.hpp"
#include "Tree.hpp"

auto main() -> int
{
    constexpr uint N_min  =  100;
    constexpr uint N_step =  100;
    constexpr uint N_max  = 1000;

    constexpr uint K = 10;

    struct Result
    {
        double unsorted_rounds{};
        double sorted_rounds{};

        auto operator+=(const Result& other)
        {
            this->unsorted_rounds += other.unsorted_rounds;
            this->sorted_rounds += other.sorted_rounds;

            return *this;
        }

        auto operator/=(const double divisor)
        {
            this->unsorted_rounds /= divisor;
            this->sorted_rounds /= divisor;

            return *this;
        }
    };

    std::map<uint, Result> prim_results{};
    std::map<uint, Result> kruskal_results{};

    for (uint N = N_min; N <= N_max; N += N_step)
    {
        std::clog << std::format("Running for N = {}.\n", N);

        prim_results[N] = {};
        kruskal_results[N] = {};

        for (uint _ = 0; _ < K; _++)
        {
            Graph full_graph(N);

            Graph mst_prim = prim(full_graph);
            Graph mst_kruskal = kruskal(full_graph);

            Tree tree_prim(mst_prim);
            Tree tree_kruskal(mst_kruskal);

            tree_prim.calc_size();
            tree_kruskal.calc_size();

            int unsorted_result_prim = tree_prim.transmit();
            int unosrted_result_kruskal = tree_kruskal.transmit();

            // tree_prim.calc_size();
            // tree_kruskal.calc_size();

            tree_prim.calc_size2();
            tree_kruskal.calc_size2();

            int sorted_result_prim = tree_prim.transmit();
            int sorted_result_kruskal = tree_kruskal.transmit();

            prim_results[N] += Result{
                .unsorted_rounds = static_cast<double>(unsorted_result_prim),
                .sorted_rounds = static_cast<double>(sorted_result_prim)
            };

            kruskal_results[N] += Result{
                .unsorted_rounds = static_cast<double>(unosrted_result_kruskal),
                .sorted_rounds = static_cast<double>(sorted_result_kruskal)
            };
        }

        prim_results[N] /= K;
        kruskal_results[N] /= K;
    }

    std::cout << std::format(
        "#N\t\tPrimUnsorted\t\tPrimSorted\t\tKruskalUnsorted\t\tKruskalSorted\n"
    );
    for (uint N = N_min; N <= N_max; N += N_step)
    {
        const Result prim = prim_results[N];
        const Result kruskal = kruskal_results[N];

        std::cout << std::format(
            "{}\t\t{}\t\t{}\t\t{}\t\t{}\n",
            N,
            prim.unsorted_rounds, prim.sorted_rounds,
            kruskal.unsorted_rounds, kruskal.sorted_rounds
        );
    }
}