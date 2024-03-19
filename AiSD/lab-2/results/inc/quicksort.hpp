#pragma once

#include "sort.hpp"

idx partition (std::span<Key> arr)
{
    idx lo = 0;
    idx hi = arr.size() - 1;

    Key pivot = arr[hi];

    idx i = lo;
    for (idx j = lo; j < hi; j++)
    {
        if (arr[j] <= pivot)
        {
            arr[i].swap(arr[j]);
            i++;
        }
    }

    arr[i].swap(arr[hi]);
    return i;
}

const SortFn QuickSort = [](std::span<Key> arr, const bool print = false)
{
    if (arr.size() <= 1)
        return;

    idx p = partition(arr);

    std::span<Key> A(arr.begin(), arr.begin() + p);
    std::span<Key> B(arr.begin() + p + 1, arr.end());

    QuickSort(A, print);
    QuickSort(B, print);
};