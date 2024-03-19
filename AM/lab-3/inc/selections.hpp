#pragma once

#include "misc.hpp"


const Select randomSelect = [](const std::span<const Cycle>& population, const std::span<const uint>& costs, std::span<std::pair<size_t,size_t>> parrents)
{
    const uint parrentPairs = (population.size() / 4);
    const uint parrentsCount = parrentPairs * 2;

    static std::vector<size_t> arr(population.size());

    std::iota(arr.begin(), arr.end(), 0u);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(arr.begin(), arr.end(), gen);

    for (size_t i = 0; i < parrentPairs; i++)
        parrents[i] = std::make_pair(arr[i * 2], arr[i * 2 + 1]);
};

const Select tourneySelect = [](const std::span<const Cycle>& population, const std::span<const uint>& costs, std::span<std::pair<size_t,size_t>> parrents)
{
    const uint parrentPairs = (population.size() / 4);
    const uint parrentsCount = parrentPairs * 2;

    const uint tourneySize = 20;

    size_t arr[population.size()];
    std::iota(arr, arr + population.size(), 0u);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(arr, arr + population.size(), gen);

    for (uint tourney = 0; tourney < population.size(); tourney += tourneySize)
    {
        auto parrentsSpan = std::span(parrents.begin() + tourney / 4, parrents.begin() + tourney / 4 + tourneySize / 4);
        auto arrSpan = std::span(arr + tourney, arr + tourney + tourneySize);

        std::sort(arrSpan.begin(), arrSpan.end(), [&costs](const size_t i1, const size_t i2)
        {
            return costs[i1] < costs[i2];
        });

        for (size_t i = 0; i < tourneySize / 4; i++)
        {
            parrentsSpan[i] = std::make_pair(arrSpan[i * 2], arrSpan[i * 2 + 1]);
        }
    }

    return parrents;
};

const Select islandTourneySelect = [](const std::span<const Cycle>& population, const std::span<const uint>& costs, std::span<std::pair<size_t,size_t>> parrents)
{
    static uint iteration = 0;
    iteration++;

    if (iteration % 20 == 0){
        tourneySelect(population, costs, parrents);
        return;
    }

    const uint numOfIslands = 10;

    const uint parrentPairs = (population.size() / 4);
    const uint parrentsCount = parrentPairs * 2;

    const uint islandSize = population.size() / numOfIslands;
    const uint islandParrentPairs = parrentPairs / numOfIslands;

    for (uint island = 0; island < numOfIslands; island++)
    {
        const size_t islandStart = island * islandSize;
        const size_t islandEnd = islandStart + islandSize;

        std::span<const Cycle> islandSpan(population.begin() + islandStart, population.begin() + islandEnd);
        std::span<const uint> costsSpan(costs.begin() + islandStart, costs.begin() + islandEnd);
        std::span<std::pair<size_t, size_t>> parrentsSpan(parrents.begin() + island * islandParrentPairs, parrents.begin() + (island + 1) * islandParrentPairs);

        tourneySelect(islandSpan, costsSpan, parrentsSpan);
    }
};