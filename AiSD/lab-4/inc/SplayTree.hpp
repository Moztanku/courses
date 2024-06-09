#pragma once

#include <stack>
#include <memory>
#include <iostream>

#include "ITree.hpp"

#include "NodePtr.hpp"

class SplayTree : public ITree
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

        auto rotate_left(NodePtr<Node> node) -> void;
        auto rotate_right(NodePtr<Node> node) -> void;

        auto splay(NodePtr<Node> node) -> void;
};

auto SplayTree::rotate_left(NodePtr<Node> y) -> void
{
    auto x = y->right;

    if (y->parent)
    {
        if (y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    x->parent = y->parent;

    y->right = x->left;
    if (y->right)
        y->right->parent = y;

    x->left = y;
    y->parent = x;

    if (y == root)
        root = x;
}

auto SplayTree::rotate_right(NodePtr<Node> y) -> void
{
    auto x = y->left;

    if (y->parent)
    {
        if (y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    x->parent = y->parent;
    
    y->left = x->right;
    if (y->left)
        y->left->parent = y;
    
    x->right = y;
    y->parent = x;

    if (y == root)
        root = x;
}

auto SplayTree::splay(NodePtr<Node> x) -> void
{
    if (!x || x == root)
        return;

    auto& y = x->parent;

    // Case 1: x is child of root
    if (y == root)
    {
        if (y->left == x)
            rotate_right(y);
        else
            rotate_left(y);
        return;
    }

    auto& z = y->parent;

    // Case 2: straight
    if (y->left == x && z->left == y)
    {
        rotate_right(z);
        rotate_right(x->parent);
    }
    else if (y->right == x && z->right == y)
    {
        rotate_left(z);
        rotate_left(x->parent);
    }

    // Case 3: zig-zag// Case 3: zig-zag
    else if (
        (y->left == x  && z->right == y) ||
        (y->right == x && z->left  == y)
    ){
        if (y->left == x)
        {
            rotate_right(x->parent);
            rotate_left(x->parent);
        }
        else
        {
            rotate_left(x->parent);
            rotate_right(x->parent);
        }
    }

    if (x != root)
        splay(x);
}

auto SplayTree::insert(Key value) -> void
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
                node->left->parent = node;

                node = node->left;
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
                node->right->parent = node;

                node = node->right;
                break;
            }
        }
    }

    node->value = value;

    splay(node);
}

auto SplayTree::remove(Key value) -> void
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

    splay(node->parent);
}

auto SplayTree::height() const -> int
{
    std::stack<NodePtr<Node>> stack;
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

auto SplayTree::size() const -> int
{
    std::stack<NodePtr<Node>> stack;
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

auto SplayTreePrint(const NodePtr<SplayTree::Node> node, std::string indent, bool right) -> void
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

    SplayTreePrint(node->left, indent, node->right == nullptr);
    SplayTreePrint(node->right, indent, true);
}

auto SplayTree::print() const -> void
{
    SplayTreePrint(root, "", true);
}