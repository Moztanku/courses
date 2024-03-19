#pragma once

#include <tuple>

#include "sort.hpp"
#include "insertionsort.hpp"

void merge(std::span<Key> left, std::span<Key> right, std::span<Key> result)
{
    idx i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
            result[k++] = left[i++];
        else
            result[k++] = right[j++];
    }

    while (i < left.size())
        result[k++] = left[i++];

    while (j < right.size())
        result[k++] = right[j++];
}

const SortFn MergeSort = [](std::span<Key> keys, const bool print = false)
{
    if (keys.size() < 2)
        return;

    idx mid = keys.size() / 2;

    std::vector<Key> left(keys.begin(), keys.begin() + mid);
    std::vector<Key> right(keys.begin() + mid, keys.end());

    MergeSort(left, print);
    MergeSort(right, print);

    merge(left, right, keys);    
};

const SortFn MergeSort2 = [](std::span<Key> keys, const bool print = false)
{
    if (keys.size() < 2)
        return;

    idx mid = keys.size() / 2;

    std::vector<Key> left(keys.begin(), keys.begin() + mid);
    std::vector<Key> right(keys.begin() + mid, keys.end());

    if (left.size() <= 1)
        InsertionSort(left, print);
    else
        MergeSort2(left, print);

    if (right.size() <= 11)
        InsertionSort(right, print);
    else
        MergeSort2(right, print);

    merge(left, right, keys);    
};

auto printSpan(std::span<Key> keys) -> void
{
    for (const auto& key : keys)
        std::cout << key << " ";
    std::cout << std::endl;
}

auto printVector(const std::vector<int>& keys) -> void
{
    for (const auto& key : keys)
        std::cout << key << " ";
    std::cout << std::endl;
}

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

    // std::cout << "Input: ";
    // printSpan(keys);

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

    // std::cout << "Output: ";
    // printSpan(keys);

    // std::cout << "Runs: ";
    // printVector(runs);

    // std::span<Key> firstRun(keys.begin(), runs[0]);
    // std::cout << "[0] ";
    // printSpan(firstRun);

    // for (idx run = 1; run < runs.size(); run++)
    // {
    //     std::span<Key> r(keys.begin() + runs[run - 1], runs[run] - runs[run - 1]);
    //     std::cout << "[" << run << "] ";
    //     printSpan(r);
    // }
};
