#pragma once

#include "search.hpp"

#include "select.hpp"
#include "insertionsort.hpp"

template <uint K>
const SearchFn KSelect = [](std::span<Key> arr, idx nth) -> Key
{
    if (arr.size() <= K)
    {
        InsertionSort(arr, false);
        return arr[nth - 1];
    }

    std::vector<std::span<Key>> subs(
        static_cast<size_t>(std::ceil(arr.size() / static_cast<double>(K)))
    );

    for (idx i = 0; i < subs.size(); i++)
    {
        idx offset = i * K;
        idx size = std::min(
            static_cast<idx>(K),
            static_cast<idx>(arr.size() - offset)
        );

        subs[i] = arr.subspan(offset, size);
    }

    std::vector<Key> medians(subs.size());

    for (idx i = 0; i < subs.size(); i++)
    {
        InsertionSort(subs[i], false);

        idx median_idx = subs[i].size() / 2;

        medians[i] = subs[i][median_idx];
    }

    Key pivot = KSelect<K>(medians, medians.size() / 2);

    idx r = partition(arr, pivot);
    idx k = r + 1;

    if (nth == k)
        return arr[r];
    else if (nth < k)
        return KSelect<K>(
            arr.subspan(0, r),
            nth
        );
    else /*(nth > k)*/
        return KSelect<K>(
            arr.subspan(r + 1),
            nth - k
        );
};
