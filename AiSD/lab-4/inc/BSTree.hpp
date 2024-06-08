#pragma once

#include <stack>
#include <memory>
#include <iostream>

#include "ITree.hpp"

class BSTree : public ITree
{
    public:
        struct Node
        {
            int value;
            std::shared_ptr<Node> left, right, parent;
        };

        BSTree(int root_value)
            : root{std::make_shared<Node>()} { root->value = root_value; }

        auto insert(int value) -> void override;
        auto remove(int value) -> void override;

        auto height() const -> int override;
        auto size() const -> int override;

        auto print() const -> void override;

    private:
        std::shared_ptr<Node> root;
};

auto BSTree::insert(int value) -> void
{
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

auto BSTree::remove(int value) -> void
{
    auto node = root;

    // Find the node to remove
    while (node && node->value != value)
        if (value < node->value)
            node = node->left;
        else
            node = node->right;

    // Return if the node was not found
    if (!node)
        return;

    auto left = node->left;
    auto right = node->right;

    // Case 1: Node has no children
    if (!left && !right)
    {
        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
    }

    // Case 2: Node has one child
    else if (!left || !right)
    {
        if (node->parent->left == node)
            node->parent->left = left ? left : right;
        else
            node->parent->right = left ? left : right;
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

auto BSTree::height() const -> int
{
    std::stack<std::shared_ptr<Node>> stack;
    stack.push(root);

    int height = 0;
    int max_height = 0;

    while (!stack.empty())
    {
        auto node = stack.top();
        stack.pop();

        if (node->left)
            stack.push(node->left);

        if (node->right)
            stack.push(node->right);

        if (!node->left && !node->right)
        {
            height = 0;
            auto parent = node->parent;

            while (parent)
            {
                height++;
                parent = parent->parent;
            }

            if (height > max_height)
                max_height = height;
        }
    }

    return max_height + 1;
}

auto BSTree::size() const -> int
{
    std::stack<std::shared_ptr<Node>> stack;
    stack.push(root);

    int size = 0;

    while (!stack.empty())
    {
        auto node = stack.top();
        stack.pop();

        size++;

        if (node->left)
            stack.push(node->left);

        if (node->right)
            stack.push(node->right);
    }

    return size;
}

auto BSTreePrint(const std::shared_ptr<BSTree::Node> node, std::string indent, bool right) -> void
{
    if (!node)
        return;

    std::cout << indent;

    if (right)
    {
        std::cout << "└────";
        indent += "     ";
    }
    else
    {
        std::cout << "├────";
        indent += "│    ";
    }

    std::cout << node->value << std::endl;

    BSTreePrint(node->left, indent, node->right == nullptr);
    BSTreePrint(node->right, indent, true);
}

auto BSTree::print() const -> void
{
    BSTreePrint(root, "", true);
}