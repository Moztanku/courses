#pragma once

#include "search.hpp"

#include "quicksort.hpp"

auto rand_partition(std::span<Key> arr) -> idx
{
    idx i = std::rand() % arr.size();

    arr[i].swap(arr[arr.size() - 1]);

    return partition(arr);
}

const SearchFn RandomizedSelect = [](std::span<Key> arr, idx nth) -> Key
{
    if (arr.size() == 1)
        return arr[0];

    idx r = rand_partition(arr);

    idx k = r + 1;

    if (nth == k)
        return arr[r];
    else if (nth < k)
        return RandomizedSelect(
            arr.subspan(0, r),
            nth
        );
    else /*(nth > k)*/
        return RandomizedSelect(
            arr.subspan(r + 1),
            nth - k
        );
};