#pragma once

struct ITree
{
    virtual ~ITree() = default;

    virtual auto insert(int value) -> void = 0;
    virtual auto remove(int value) -> void = 0;

    virtual auto height() const -> int = 0;
    virtual auto size() const -> int = 0;

    virtual auto print() const -> void = 0;
};