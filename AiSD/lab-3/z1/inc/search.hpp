#pragma once

#include <span>
#include <functional>

#include "key.hpp"

typedef int idx;

using SearchFn = std::function<Key(std::span<Key>,idx)>;