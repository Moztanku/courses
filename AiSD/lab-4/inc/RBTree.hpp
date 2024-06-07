#pragma once

#include <stack>
#include <memory>
#include <iostream>

#include "ITree.hpp"

class RBTree : public ITree
{
    public:
        struct Node
        {
            int value;
            bool is_black;

            std::shared_ptr<Node> left, right, parent;
        };

        RBTree(int root_value)
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

using Node = RBTree::Node;
auto rotateLeft(std::shared_ptr<Node>& root, std::shared_ptr<Node> &x) -> void
{
    std::shared_ptr<Node> y = x->right;

    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

auto rotateRight(std::shared_ptr<Node> &root, std::shared_ptr<Node> &x) -> void
{
    std::shared_ptr<Node> y = x->left;

    x->left = y->right;

    if (y->right != nullptr)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

auto fixInsert(std::shared_ptr<Node>& root, std::shared_ptr<Node>& x) -> void
{    
    std::shared_ptr<Node> p = nullptr;
    std::shared_ptr<Node> gp = nullptr;

    while ((x != root) && (!x->is_black) && (!x->parent->is_black))
    {
        p = x->parent;
        gp = x->parent->parent;

        if (p == gp->left) {
            std::shared_ptr<Node> uncle = gp->right;

            if (uncle != nullptr && !uncle->is_black) {
                gp->is_black = false;
                p->is_black = true;
                uncle->is_black = true;
                x = gp;
            } else {
                if (x == p->right)
                {
                    rotateLeft(root, p);
                    x = p;
                    p = x->parent;
                }

                rotateRight(root, gp);
                std::swap(p->is_black, gp->is_black);
                x = p;
            }
        } else {
            std::shared_ptr<Node> uncle = gp->left;

            if ((uncle != nullptr) && (!uncle->is_black)) {
                gp->is_black = false;
                p->is_black = true;
                uncle->is_black = true;
                x = gp;
            } else {
                if (x == p->left) {
                    rotateRight(root, p);
                    x = p;
                    p = x->parent;
                }

                rotateLeft(root, gp);
                std::swap(p->is_black, gp->is_black);
                x = p;
            }
        }
    }

    root->is_black = true;
} 

auto RBTree::insert(int value) -> void
{
    auto node = root;
    while (node)
    {
        if (value <= node->value)
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
    node->is_black = false;

    fixInsert(root, node);
}

auto find(const std::shared_ptr<Node> root, int value) -> std::shared_ptr<Node>
{
    auto node = root;

    while (node)
    {
        if (value == node->value)
            return node;

        if (value < node->value)
            node = node->left;
        else
            node = node->right;
    }

    return nullptr;
}

auto treeSuccessor(std::shared_ptr<Node> x) -> std::shared_ptr<Node>
{
    if (x->right)
    {
        x = x->right;

        while (x->left)
            x = x->left;

        return x;
    }

    auto y = x->parent;

    while (y && x == y->right)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

auto fixRemove(std::shared_ptr<Node>& root, std::shared_ptr<Node>& x) -> void
{
    if (x == nullptr)
        return;


    while (x != root && x->is_black == true)
    {
        if (x == x->parent->left)
        {
            std::shared_ptr<Node> w = x->parent->right;

            if (w->is_black == false)
            {
                w->is_black = true;
                x->parent->is_black = false;
                rotateLeft(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->is_black == true && w->right->is_black == true)
            {
                w->is_black = false;
                x = x->parent;
            }

            else
            {
                if (w->right->is_black == true)
                {
                    w->left->is_black = true;
                    w->is_black = false;
                    rotateRight(root, w);
                    w = x->parent->right;
                }

                w->is_black = x->parent->is_black;
                x->parent->is_black = true;
                w->right->is_black = true;
                rotateLeft(root, x->parent);
                x = root;
            }
        } else {
            std::shared_ptr<Node> w = x->parent->left;

            if (w->is_black == false)
            {
                w->is_black = true;
                x->parent->is_black = false;
                rotateRight(root, x->parent);
                w = x->parent->left;
            }

            if (w->right && w->right->is_black == true && w->left && w->left->is_black == true)
            {
                w->is_black = false;
                x = x->parent;
            }

            else
            {
                if (w->left->is_black == true)
                {
                    w->right->is_black = true;
                    w->is_black = false;
                    rotateLeft(root, w);
                    w = x->parent->left;
                }

                w->is_black = x->parent->is_black;
                x->parent->is_black = true;
                w->left->is_black = true;
                rotateRight(root, x->parent);
                x = root;
            }
        }
    }

    x->is_black = true;
}


auto RBTree::remove(int value) -> void
{
    auto z = find(root, value);

    std::shared_ptr<Node> x, y;

    if (!z)
        return;

    if (z->left == nullptr || z->right == nullptr){
        y = z;
    }
    else{
        y = treeSuccessor(z);}

    if (y->left != nullptr){
        x = y->left;}
    else{
        x = y->right;}

    if (x){
        x->parent = y->parent;}

    if (y->parent == nullptr){
        root = x;}
    else if (y == y->parent->left){
        y->parent->left = x;}
    else{
        y->parent->right = x;}

    if (y != z){
        z->value = y->value;
    }

    if (y->is_black){
        fixRemove(root, x);}
}

auto RBTree::height() const -> int
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

auto RBTree::size() const -> int
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

auto RBTreePrint(const std::shared_ptr<Node> node, std::string indent, bool right) -> void
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

    const auto color = node->is_black ? "\033[1;30m" : "\033[1;31m";
    const auto reset = "\033[0m";

    std::cout << color << node->value << reset << std::endl;

    RBTreePrint(node->left, indent, node->right == nullptr);
    RBTreePrint(node->right, indent, true);
}

auto RBTree::print() const -> void
{
    RBTreePrint(root, "", true);
}