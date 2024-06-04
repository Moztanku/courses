#pragma once

#include "ITree.hpp"

class RBTree : public ITree 
{
    public:
        auto insert(int key) -> void override;
        auto remove(int key) -> void override;
        auto height() const -> int override;
    private:
};