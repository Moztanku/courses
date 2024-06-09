#pragma once

#include <Key.hpp>

struct ITree
{
    virtual ~ITree() = default;

    virtual auto insert(Key value) -> void = 0;
    virtual auto remove(Key value) -> void = 0;

    virtual auto height() const -> int = 0;
    virtual auto size() const -> int = 0;

    virtual auto print() const -> void = 0;
};