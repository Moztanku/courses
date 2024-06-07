#pragma once

#include <stack>
#include <memory>
#include <iostream>

#include "ITree.hpp"

class SplayTree : public ITree
{
    public:
        struct Node
        {
            int value;
            bool is_black;

            std::shared_ptr<Node> left, right, parent;
        };

        SplayTree(int root_value)
            : root{std::make_shared<Node>()} {
                root->value = root_value;
                root->is_black = true;
            }

        auto insert(int value) -> void override;
        auto remove(int value) -> void override;

        auto height() const -> int override;
        auto size() const -> int override;

        auto print() const -> void override;

    private:
        std::shared_ptr<Node> root;
};

using Node = SplayTree::Node;