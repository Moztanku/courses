#pragma once

#include "quicksort.hpp"
#include "dpquicksort.hpp"

#include "randomselect.hpp"

const SortFn myquicksort = [](std::span<Key> arr, const bool print = false) -> void
{
    if (arr.size() <= 1)
        return;

    idx p = arr.size() / 2;
    RandomizedSelect(arr, p + 1);

    std::span<Key> A(arr.begin(), arr.begin() + p);
    std::span<Key> B(arr.begin() + p + 1, arr.end());

    myquicksort(A, print);
    myquicksort(B, print);
};

const SortFn mydpquicksort = [](std::span<Key> arr, const bool print = false)
{
    if (arr.size() < 2)
        return;
    
    idx l = (arr.size() * 1) / 3;
    idx r = (arr.size() * 2) / 3;

    RandomizedSelect(arr, l + 1);

    // subspan from l to end of array
    std::span<Key> subspan(arr.begin() + l, arr.end());
    RandomizedSelect(subspan, r - l + 1);

    std::span<Key> A(arr.begin(), arr.begin() + l);
    std::span<Key> B(arr.begin() + l, arr.begin() + r);
    std::span<Key> C(arr.begin() + r, arr.end());

    mydpquicksort(A, print);
    mydpquicksort(B, print);
    mydpquicksort(C, print);
};