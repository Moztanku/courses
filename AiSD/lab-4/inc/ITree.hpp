#pragma once

#include <memory>

struct ITree {
    virtual ~ITree() = default;

    virtual auto insert(int key) -> void = 0;
    virtual auto remove(int key) -> void = 0;
    
    virtual auto height() const -> int = 0;
    virtual auto print() const -> void = 0;
};


