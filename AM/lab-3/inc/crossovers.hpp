#pragma once

#include "misc.hpp"

const CrossOver PMXCrossOver = [](const Cycle& p1, const Cycle& p2, Cycle& child)
{
    const size_t size = p1.size();

    uint cut1{}, cut2{};

    while(cut1 == cut2)
    {
        std::tie(cut1,cut2) = std::minmax(
            myRand() % size, myRand() % size
        );
    }

    cut1 = 3;
    cut2 = 6;

    for (size_t i = cut1; i < cut2; i++)
        child[i] = p1[i];

    std::vector<size_t> invalid{};

    for (size_t i = 0; i < cut1; i++)
        if (std::find(child.begin() + cut1, child.begin() + cut2, p2[i]) == child.begin() + cut2)
            child[i] = p2[i];
        else
            invalid.push_back(i);

    for (size_t i = cut2; i < size; i++)
        if (std::find(child.begin() + cut1, child.begin() + cut2, p2[i]) == child.begin() + cut2)
            child[i] = p2[i];
        else {
            invalid.push_back(i);
        }

    auto pit = 0;
    for (const auto i : invalid)
    {
        while (std::find(child.begin() + cut1, child.begin() + cut2, *(p2.begin() + pit)) != child.begin() + cut2 || child[pit] == p2[pit])
        {
            pit++;
        }

        child[i] = *(p2.begin() + pit);
        pit++;
    }
};

const CrossOver OXCrossOver = [](const Cycle& p1, const Cycle& p2, Cycle& child)
{
    const size_t size = p1.size();

    uint cut1{}, cut2{};

    while(cut1 == cut2)
    {
        std::tie(cut1,cut2) = std::minmax(
            myRand() % size, myRand() % size
        );
    }

    for (size_t i = cut1; i < cut2; i++)
        child[i] = p1[i];

    auto it = child.begin() + cut2;
    auto pit = p2.begin() + cut2;

    uint ctr = 0;
    while(it != child.begin() + cut1)
    {
        if (it == child.end())
            it = child.begin();

        if (pit == p2.end())
            pit = p2.begin();

        if (std::find(child.begin() + cut1, child.begin() + cut2, *pit) == child.begin() + cut2)
        {
            *it = *pit;
            it++;
        }

        pit++;
    }

    return child;
};