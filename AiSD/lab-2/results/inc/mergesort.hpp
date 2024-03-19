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
