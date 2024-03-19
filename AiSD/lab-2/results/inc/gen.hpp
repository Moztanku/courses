#pragma once

#include <span>
#include <random>
#include <algorithm>
#include <functional>

#include "key.hpp"

using GenFn = std::function<void(std::span<Key>)>;

const GenFn GenSorted = [](std::span<Key> arr)
{
    std::iota(arr.begin(), arr.end(), 0);
};

const GenFn GenReversed = [](std::span<Key> arr)
{
    std::iota(arr.rbegin(), arr.rend(), 0);
};

const GenFn GenRandom = [](std::span<Key> arr)
{
    static auto rng = std::mt19937(std::random_device()());
    std::iota(arr.begin(), arr.end(), 0);
    std::shuffle(
        arr.begin(), arr.end(), rng
    );
};