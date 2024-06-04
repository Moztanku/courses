#pragma once

#include <memory>

#include "ITree.hpp"

class BSTree : public ITree 
{
    public:
        BSTree(NodePtr root = nullptr) {
            m_root = root;
        }

        auto insert(int key) -> void override;
        auto remove(int key) -> void override;
        auto height() const -> int override;
};

auto BSTree::insert(int key) -> void
{
    auto node = std::make_shared<Node>(
        Node{.key = key}
    );

    if (m_root == nullptr) {
        m_root = node;
        return;
    }

    auto current = m_root;

    while (true) {
        if (key < current->key) {
            if (current->l == nullptr) {
                current->l = node;
                node->p = current;
                return;
            }
            current = current->l;
        } else {
            if (current->r == nullptr) {
                current->r = node;
                node->p = current;
                return;
            }
            current = current->r;
        }
    }
}

auto BSTree::height() const -> int
{
    if (m_root == nullptr) 
        return 0;

    int lheight = BSTree{m_root->l}.height();
    int rheight = BSTree{m_root->r}.height();

    return std::max(lheight, rheight) + 1;
}

auto BSTree::remove(int key) -> void
{

}