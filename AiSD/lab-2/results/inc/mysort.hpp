#pragma once

#include "sort.hpp"
#include "mergesort.hpp"

auto chooseRun(std::vector<idx>& runs) -> std::tuple<idx,idx>
{
    idx minRun = 0;
    idx minRunSize = runs[0] - 0;

    for (idx i = 1; i < runs.size(); i++)
    {
        idx runSize = runs[i] - runs[i - 1];
        if (runSize < minRunSize)
        {
            minRun = i;
            minRunSize = runSize;
        }
    }

    idx secRun = minRun == 0                            ? 1
                 :  minRun == runs.size() - 1           ? runs.size() - 2
                 :  runs[minRun - 1] < runs[minRun + 1] ? minRun - 1
                                                        : minRun + 1;

    if (minRun > secRun)
        std::swap(minRun, secRun);

    return {minRun, secRun};
}

const SortFn MySort = [](std::span<Key> keys, const bool print = false)
{
    //
    // 1. Divide the array into runs
    //      - Walk through the array and mark end of a run when current element is less than previous
    //      - Runs are already sorted inside of them
    // 2. Merge runs
    //      - Merge runs in pairs
    //      - Choose smallest run to merge
    //      - Repeat until only one run is left
    //
    std::vector<idx> runs;

    idx i = 0;
    while (i < keys.size())
    {
        idx j = i + 1;
        while (j < keys.size() && keys[j] >= keys[j - 1])
            j++;

        runs.push_back(j);
        i = j;
    }

    while(runs.size() > 1)
    {
        auto [l, r] = chooseRun(runs);

        idx right = runs[r];
        idx left  = l == 0 ? 0 : runs[l - 1];
        idx mid   = runs[l];

        runs.erase(runs.begin() + l);
        std::vector<Key> leftRun(keys.begin() + left, keys.begin() + mid);
        std::vector<Key> rightRun(keys.begin() + mid, keys.begin() + right);

        std::span<Key> target(keys.begin() + left, keys.begin() + right);

        merge(leftRun, rightRun, target);
    }
};