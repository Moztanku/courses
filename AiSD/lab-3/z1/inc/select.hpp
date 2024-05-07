#pragma once

#include "search.hpp"

#include "insertionsort.hpp"

idx partition(std::span<Key> arr, Key pivotValue)
{
    idx i = 0;
    for (idx j = 0; j < arr.size(); j++)
    {
        if (arr[j] < pivotValue)
        {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    for (idx j = i; j < arr.size(); j++)
    {
        if (arr[j] == pivotValue)
        {
            std::swap(arr[i], arr[j]);
            break;
        }
    }
    return i;
}

const SearchFn Select = [](std::span<Key> arr, idx nth) -> Key
{
    if (arr.size() <= 5)
    {
        InsertionSort(arr, false);
        return arr[nth - 1];
    }

    std::vector<std::span<Key>> subs(
        static_cast<size_t>(std::ceil(arr.size() / 5.0))
    );

    for (idx i = 0; i < subs.size(); i++)
    {
        idx offset = i * 5;
        idx size = std::min(5, static_cast<idx>(arr.size() - offset));

        subs[i] = arr.subspan(offset, size);
    }

    std::vector<Key> medians(subs.size());

    for (idx i = 0; i < subs.size(); i++)
    {
        InsertionSort(subs[i], false);

        idx median_idx = subs[i].size() / 2;

        medians[i] = subs[i][median_idx];
    }

    Key pivot = Select(medians, medians.size() / 2);

    idx r = partition(arr, pivot);
    idx k = r + 1;

    if (nth == k)
        return arr[r];
    else if (nth < k)
        return Select(
            arr.subspan(0, r),
            nth
        );
    else /*(nth > k)*/
        return Select(
            arr.subspan(r + 1),
            nth - k
        );
};