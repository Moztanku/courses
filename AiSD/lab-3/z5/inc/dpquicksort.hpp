#pragma once

#include "sort.hpp"

auto parition(std::span<Key> keys) -> std::tuple<idx, idx>
{
    idx lo = 0;
    idx hi = keys.size() - 1;

    if (keys[lo] > keys[hi])
        keys[lo].swap(keys[hi]);

    idx l = lo + 1;
    idx r = hi - 1;

    idx it = lo + 1;

    while(it <= r)
    {
        if (keys[it] < keys[lo])
            keys[it++].swap(keys[l++]);
        else if (keys[it] > keys[hi])
            keys[it].swap(keys[r--]);
        else
            it++;
    }

    keys[lo].swap(keys[--l]);
    keys[hi].swap(keys[++r]);

    return {l, r};
}

const SortFn DPQuickSort = [](std::span<Key> keys, const bool print = false)
{
    if (keys.size() < 2)
        return;

    auto [l , r] = parition(keys);

    std::span<Key> A(keys.begin(), keys.begin() + l);
    std::span<Key> B(keys.begin() + l + 1, keys.begin() + r);
    std::span<Key> C(keys.begin() + r + 1, keys.end());

    DPQuickSort(A, print);
    DPQuickSort(B, print);
    DPQuickSort(C, print);

};
