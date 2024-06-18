#include <iostream>

#include <map>
#include <chrono>

#include "Kruskal.hpp"
#include "Graph.hpp"
#include "Prim.hpp"

auto main() -> int
{
    constexpr uint N_min  =   100;
    constexpr uint N_step =   100;
    constexpr uint N_max  = 10000;

    constexpr uint K = 10;

    std::map<uint, double> prim_times;
    std::map<uint, double> kruskal_times;

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    for (uint N = N_min; N <= N_max; N += N_step)
    {
        std::clog << "Running for N = " << N << std::endl;

        prim_times[N] = 0.0;
        kruskal_times[N] = 0.0;

        for (uint _ = 0; _ < K; _++)
        {
            Graph full_graph(N);

            start = std::chrono::high_resolution_clock::now();
            Graph mst_prim = prim(full_graph);
            end = std::chrono::high_resolution_clock::now();

            prim_times[N] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            Graph mst_kruskal = kruskal(full_graph);
            end = std::chrono::high_resolution_clock::now();

            kruskal_times[N] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        prim_times[N] /= K;
        kruskal_times[N] /= K;
    }

    std::cout << "#N\t\tPrim\t\tKruskal" << std::endl;
    for (uint N = N_min; N <= N_max; N += N_step)
    {
        std::cout << N << "\t\t" << prim_times[N] / 1000.0 << "\t\t" << kruskal_times[N] / 1000.0 << std::endl;
    }

    return 0;
}