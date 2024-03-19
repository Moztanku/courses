#pragma once

#include "sort.hpp"
#include "quicksort.hpp"
#include "insertionsort.hpp"

const SortFn HybridSort = [](std::span<Key> arr, const bool print = false)
{
    if (arr.size() <= 1)
        return;

    constexpr size_t threshold = 29;

    idx p = partition(arr);

    std::span<Key> A(arr.begin(), arr.begin() + p);
    std::span<Key> B(arr.begin() + p + 1, arr.end());

    if (A.size() <= threshold)
    {
        InsertionSort(A, print);
    }
    else
    {
        HybridSort(A, print);
    }

    if (B.size() <= threshold)
    {
        InsertionSort(B, print);
    }
    else
    {
        HybridSort(B, print);
    }
};