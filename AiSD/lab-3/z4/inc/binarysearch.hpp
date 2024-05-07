#pragma once

#include <span>

#include "key.hpp"

#include <iostream>

auto binary_search(std::span<Key> keys, Key searched) -> bool
{
    if (keys.size() == 0)
        return false;

    if (keys.size() == 1)
        return keys[0] == searched;

    const Key mid = keys[keys.size() / 2];

    if (mid < searched)
        return keys.size() == 1 ? false : binary_search(
            keys.subspan(keys.size() / 2 + 1),
            searched
        );

    else if (mid > searched)
        return keys.size() == 1 ? false : binary_search(
            keys.subspan(0, keys.size() / 2), 
            searched
        );

    else if (mid == searched)
        return true;
    
    return false;
}