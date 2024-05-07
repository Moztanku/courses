#pragma once

#include "sort.hpp"

const SortFn InsertionSort = [](std::span<Key> arr, const bool print = false)
{
    for (idx j = 1; j < arr.size(); j++)
    {
        Key key = arr[j];
        idx i{};
        for (i = j - 1; i >= 0 && arr[i] > key; i--)
            // arr[i + 1].swap(arr[i]);
            arr[i + 1] = arr[i];

        // arr[i + 1].swap(key);
        arr[i + 1] = key;
    }
};