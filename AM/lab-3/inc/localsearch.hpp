#pragma once

#include "misc.hpp"

#include <set>

int getCostDifference(const Cycle& cycle, const std::vector<Vertex>& vertices, const size_t i, const size_t j)
{
    int cost_diff = 0;

    if (i == 0) {
        cost_diff -= d(
            vertices[cycle[i]], 
            vertices[cycle[cycle.size() - 1]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[j]],
            vertices[cycle[cycle.size() - 1]]) + 0.5f;
    } else {
        cost_diff -= d(
            vertices[cycle[i - 1]],
            vertices[cycle[i]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[i - 1]],
            vertices[cycle[j]]
            ) + 0.5f;
    }

    if (j + 1 == cycle.size()) {
        cost_diff -= d(
            vertices[cycle[0]],
            vertices[cycle[j]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[0]],
            vertices[cycle[i]]) + 0.5f;
    } else {
        cost_diff -= d(
            vertices[cycle[j + 1]],
            vertices[cycle[j]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[j + 1]],
            vertices[cycle[i]]) + 0.5f;
    }

    return cost_diff;
}

void reverse(Cycle& cycle, const size_t i, const size_t j)
{
    if(i == j)
        return;

    for (size_t k = 0; k < (j - i + 1) / 2; k++)
        std::swap(cycle[i + k], cycle[j - k]);
}
double timeD = 0.0;
void localSearch(Cycle& cycle, const Vertices& vertices, uint max_steps)
{
    if (max_steps == 0)
        return;

    bool maxima;

    const uint neighborhood_size = cycle.size();
    std::set<std::pair<size_t,size_t>> neighbours;

    do {
        while (neighbours.size() < neighborhood_size)
        {
            const size_t i = myRand() % cycle.size();
            const size_t j = myRand() % cycle.size();

            if (i == j)
                continue;

            neighbours.insert(std::make_pair(i, j));
        }

        maxima = true;
        int max_diff = 0;
        int min_i = 0;
        int min_j = 0;

        for (auto& [i,j] : neighbours)
        {
            const int cost_diff = getCostDifference(cycle, vertices, i, j);

            if (j - i + 2 >= cycle.size())
                continue;

            if (cost_diff < max_diff) {
                maxima = false;
                max_diff = cost_diff;
                min_i = i;
                min_j = j;
            }
        }

        reverse(cycle, min_i, min_j);

    } while (!maxima && max_steps-- > 0);
}