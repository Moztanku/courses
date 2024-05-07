#pragma once

#include <span>
#include <functional>

#include "key.hpp"

typedef int idx;

using SortFn = std::function<void(std::span<Key>, const bool)>;
