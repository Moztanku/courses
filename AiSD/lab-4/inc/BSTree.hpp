#pragma once

#include <memory>

#include "ITree.hpp"

class BSTree : public ITree 
{
    public:
        BSTree() = default;

        auto insert(int key) -> void override;
        auto remove(int key) -> void override;

        auto height() const -> int override;
        auto print() const -> void override;
    private:
        struct Node;
        using NodePtr = std::shared_ptr<Node>;

        struct Node {
            int key;
            NodePtr l;
            NodePtr r;
            NodePtr p;
        };

        NodePtr m_root{nullptr};

        auto insert(NodePtr& parr, int key) -> void;
        auto remove(NodePtr& parr, int key) -> void;

        auto height(const NodePtr parr) const -> int;
        auto print(const NodePtr parr, int depth) const -> void;
};

auto BSTree::insert(NodePtr& parr, int key) -> void
{
    if (key <= parr->key) {
        if (parr->l == nullptr) {
            parr->l = std::make_shared<Node>(Node{.key = key, .p = parr});
            return;
        } else {
            insert(parr->l, key);
        }
    } else {
        if (parr->r == nullptr) {
            parr->r = std::make_shared<Node>(Node{.key = key, .p = parr});
            return;
        } else {
            insert(parr->r, key);
        }
    }
}

auto BSTree::insert(int key) -> void
{
    if (m_root == nullptr)
    {
        m_root = std::make_shared<Node>(Node{.key = key});
        return;
    }

    insert(m_root, key);
}

auto BSTree::remove(int key) -> void
{
    remove(m_root, key);
}

auto BSTree::remove(NodePtr& parr, int key) -> void
{
    if (parr == nullptr)
        return;

    if (key < parr->key)
        return remove(parr->l, key);

    if (key > parr->key)
        return remove(parr->r, key);

    // Case 1: No child
    if (parr->l == nullptr && parr->r == nullptr)
    {
        parr = nullptr;
        return;
    }

    // Case 2: One child
    if (parr->l == nullptr)
    {
        parr = parr->r;
        return;
    }

    if (parr->r == nullptr)
    {
        parr = parr->l;
        return;
    }

    // Case 3: Two children
    NodePtr min = parr->r;

    while (min->l != nullptr)
        min = min->l;

    parr->key = min->key;

    if (parr->r == min)
        parr->r = min->r;
    else
        min->p->l = min->r;
}

auto BSTree::height() const -> int
{
    return height(m_root);
}

auto BSTree::height(const NodePtr parr) const -> int
{
    if (parr == nullptr)
        return 0;

    return 1 + std::max(height(parr->l), height(parr->r));
}

auto BSTree::print() const -> void
{
    print(m_root, 0);
}

auto BSTree::print(const NodePtr parr, int depth) const -> void
{
    if (parr == nullptr)
        return;

    print(parr->r, depth + 1);

    constexpr std::string_view space = "  ";

    for (int i = 0; i < depth; ++i)
        std::cout << space;
    std::cout << "-[" << parr->key << "]\n";

    print(parr->l, depth + 1);
}