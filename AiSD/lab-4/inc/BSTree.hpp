#pragma once

#include <stack>
#include <memory>
#include <iostream>

#include "ITree.hpp"

#include "NodePtr.hpp"

class BSTree : public ITree
{
    public:
        struct Node
        {
            Key value;
            NodePtr<Node> left, right, parent;
        };

        auto insert(Key value) -> void override;
        auto remove(Key value) -> void override;

        auto height() const -> int override;
        auto size() const -> int override;

        auto print() const -> void override;

    private:
        NodePtr<Node> root{nullptr};
};

auto BSTree::insert(Key value) -> void
{
    if (!root)
    {
        root = std::make_shared<Node>();
        root->value = value;
        return;
    }

    auto node = root;
    while (node)
    {
        if (value < node->value)
        {
            if (node->left)
            {
                node = node->left;
            }
            else
            {
                node->left = std::make_shared<Node>();
                node->left->value = value;
                node->left->parent = node;
                break;
            }
        }
        else
        {
            if (node->right)
            {
                node = node->right;
            }
            else
            {
                node->right = std::make_shared<Node>();
                node->right->value = value;
                node->right->parent = node;
                break;
            }
        }
    }
}

auto BSTree::remove(Key value) -> void
{
    auto node = root;

    // Find the node to remove
    while (node && node->value != value)
    {
        if (value < node->value)
            node = node->left;
        else
            node = node->right;
    }

    // Return if the node was not found
    if (!node)
        return;

    auto left = node->left;
    auto right = node->right;

    // Case 1: Node has no children
    if (!left && !right)
    {
        if (node == root)
        {
            root = nullptr;
            return;
        }

        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
    }

    // Case 2: Node has one child
    else if ((!left && right) || (left && !right))
    {
        auto child = left ? left : right;
        if (node == root)
        {
            root = child;
            child->parent = nullptr; // Add this line
            return;
        }

        if (node->parent->left == node){
            node->parent->left = child;}
        else{
            node->parent->right = child;}
        child->parent = node->parent; // Add this line
    }

    // Case 3: Node has two children
    else
    {
        auto next = right;

        // We find the successor of the node
        while (next->left)
            next = next->left;

        // We replace the node with the successor
        node->value = next->value;

        // We remove the successor
        if (next->parent->left == next)
            next->parent->left = nullptr;
        else
            next->parent->right = nullptr;
    }
}

auto BSTHeight(const NodePtr<BSTree::Node> node) -> int
{
    if (!node)
        return 0;

    return 1 + std::max(BSTHeight(node->left), BSTHeight(node->right));
}

auto BSTree::height() const -> int
{
    return BSTHeight(root);
}

auto BSTSize(const NodePtr<BSTree::Node> node) -> int
{
    if (!node)
        return 0;

    return 1 + BSTSize(node->left) + BSTSize(node->right);
}

auto BSTree::size() const -> int
{
    return BSTSize(root);
}

auto BSTreePrint(const NodePtr<BSTree::Node> node, std::string indent, bool right) -> void
{
    if (!node)
        return;

    std::cout << indent;

    if (right)
    {
        std::cout << "└──";
        indent += "   ";
    }
    else
    {
        std::cout << "├──";
        indent += "│  ";
    }

    std::cout << node->value << std::endl;

    BSTreePrint(node->left, indent, node->right == nullptr);
    BSTreePrint(node->right, indent, true);
}

auto BSTree::print() const -> void
{
    BSTreePrint(root, "", true);
}