#pragma once

#include <set>

#include "misc.hpp"

const Mutate mutateSwap = [](Cycle& cycle)
{
    const float randomned = randomFloat();

    const uint noOfPairsToSwap = 
        randomned <= 0.5f ? 0u :
        randomned <= 0.7f ? 1u :
        randomned <= 0.9f ? 2u :
        3u;

    std::set<std::pair<size_t, size_t>> pairsToSwap;

    while (pairsToSwap.size() < noOfPairsToSwap)
    {
        const auto [i,j] = std::minmax(myRand() % cycle.size(), myRand() % cycle.size());

        if (i == j)
            continue;

        pairsToSwap.emplace(std::make_pair(i,j));
    }

    for (const auto [i,j] : pairsToSwap)
    {
        std::swap(cycle[i],cycle[j]);
    }
};

const Mutate emptyMutate = [](Cycle& cycle)
{
    return;
};