#pragma once

#include <stack>
#include <memory>
#include <iostream>

#include "ITree.hpp"

#include "NodePtr.hpp"

class RBTree : public ITree
{
    public:
        struct Node
        {
            Key value;
            bool is_black;

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

using Node = RBTree::Node;
const NodePtr<Node> nil = 
    std::make_shared<Node>(Node
        {
            0,
            true,
            std::shared_ptr<Node>(nullptr),
            std::shared_ptr<Node>(nullptr),
            std::shared_ptr<Node>(nullptr)
        });

auto rotateLeft(NodePtr<Node>& root, NodePtr<Node> &x) -> void
{
    NodePtr<Node> y = x->right;

    x->right = y->left;

    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

auto rotateRight(NodePtr<Node> &root, NodePtr<Node> &x) -> void
{
    NodePtr<Node> y = x->left;

    x->left = y->right;

    if (y->right != nil)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

auto fixInsert(NodePtr<Node>& root, NodePtr<Node>& x) -> void
{    
    NodePtr<Node> p{nullptr};
    NodePtr<Node> gp{nullptr};

    while ((x != root) && (!x->is_black) && (!x->parent->is_black))
    {
        p = x->parent;
        gp = x->parent->parent;

        if (p == gp->left) {
            NodePtr<Node> uncle = gp->right;

            if (uncle != nil && !uncle->is_black) {
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
            NodePtr<Node> uncle = gp->left;

            if ((uncle != nil) && (!uncle->is_black)) {
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

auto RBTree::insert(Key value) -> void
{
    if (!root)
    {
        root = std::make_shared<Node>();
        root->value = value;
        root->is_black = true;
        root->left = nil;
        root->right = nil;
        root->parent = nil;
        return;
    }

    auto node = root;
    while (node)
    {
        if (value < node->value)
        {
            if (node->left != nil)
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
            if (node->right != nil)
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
    node->left = nil;
    node->right = nil;

    fixInsert(root, node);
}

auto find(const NodePtr<Node> root, Key value) -> NodePtr<Node>
{
    auto node = root;

    while (node != nil)
    {
        if (value == node->value)
            return node;

        if (value < node->value)
            node = node->left;
        else
            node = node->right;
    }

    // return nullptr;
    return nil;
}

auto treeSuccessor(NodePtr<Node> x) -> NodePtr<Node>
{
    if (x->right != nil)
    {
        x = x->right;

        while (x->left != nil)
            x = x->left;

        return x;
    }

    auto y = x->parent;

    while (y != nil && x == y->right)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

auto fixRemove(NodePtr<Node>& root, NodePtr<Node>& x) -> void
{
    while (x != root && x->is_black == true)
    {
        if (x == x->parent->left)
        {
            NodePtr<Node> w = x->parent->right;

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
            NodePtr<Node> w = x->parent->left;

            if (w->is_black == false)
            {
                w->is_black = true;
                x->parent->is_black = false;
                rotateRight(root, x->parent);
                w = x->parent->left;
            }

            if (w->right->is_black == true && w->left->is_black == true)
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

auto RBTree::remove(Key value) -> void
{
    auto z = find(root, value);

    NodePtr<Node> x, y;

    if (z == nil)
        return;

    if (z->left == nil || z->right == nil){
        y = z;
    }
    else{
        y = treeSuccessor(z);
    }

    if (y->left != nil){
        x = y->left;}
    else{
        x = y->right;}  // x = nil

    x->parent = y->parent;

    if (y->parent == nil){
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
    std::stack<NodePtr<Node>> stack;
    stack.push(root);

    int height = 0;
    int max_height = 0;

    while (!stack.empty())
    {
        auto node = stack.top();
        stack.pop();

        if (node->left != nil)
            stack.push(node->left);

        if (node->right != nil)
            stack.push(node->right);

        if (node->left == nil && node->right == nil)
        {
            height = 0;
            auto parent = node->parent;

            while (parent != nil)
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
    std::stack<NodePtr<Node>> stack;
    stack.push(root);

    int size = 0;

    while (!stack.empty())
    {
        auto node = stack.top();
        stack.pop();

        size++;

        if (node->left != nil)
            stack.push(node->left);

        if (node->right != nil)
            stack.push(node->right);
    }

    return size;
}

auto RBTreePrint(const NodePtr<Node> node, std::string indent, bool right) -> void
{
    if (node == nil || !node)
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

    RBTreePrint(node->left, indent, node->right == nil);
    RBTreePrint(node->right, indent, true);
}

auto RBTree::print() const -> void
{
    RBTreePrint(root, "", true);
}