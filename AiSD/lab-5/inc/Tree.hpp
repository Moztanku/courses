#pragma once

#include <vector>
#include <memory>
#include <semaphore>
#include <algorithm>

#include "Graph.hpp"

class Tree
{
    struct Node;

    public:
        Tree(const Graph& mst);

        auto calc_size2() -> size_t;
        auto calc_size() -> size_t;
        auto transmit() -> int;
        auto print() -> void;
    private:
        auto add_nodes(const Graph& mst, size_t curr, size_t parent, Node& curr_node) -> void;
        std::unique_ptr<Node> m_root{};
};

struct Tree::Node 
{
    Node() = default;

    auto add_node() -> void
    {
        m_children.push_back(std::make_pair(
            0u, std::make_unique<Node>()
        ));
    }

    auto calc_size() -> size_t
    {
        size_t sum{};

        for (auto& [size, child] : m_children)
        {
            size = child->calc_size();
            sum += size;
        }

        std::sort(
            m_children.begin(), m_children.end(),
            [](const auto& lhs, const auto& rhs){ return lhs.first < rhs.first; }
        );

        return 1u + sum;
    }

    auto calc_size2() -> size_t
    {
        if (m_children.empty())
            return 1;

        size_t sum{};

        for (auto& [size, child] : m_children)
            size = child->calc_size2();

        std::sort(
            m_children.begin(), m_children.end(),
            [](const auto& lhs, const auto& rhs){ return lhs.first > rhs.first; }
        );

        size_t max = 0;

        for (size_t i = 0; i < m_children.size(); i++)
            max = std::max(max, m_children[i].first + i);

        return 1u + max;
    }

    auto transmit(int curr_round = 0) -> int
    {
        if (m_children.empty())
            return curr_round + 1;

        size_t max = {};

        for (size_t i{}; i < m_children.size(); i++)
        {
           const size_t child_round = m_children[i].second->transmit(curr_round + i + 1);
           max = std::max(max, child_round);
        }

        return max;
    }

    auto print(std::string prefix = "", bool isLast = true) -> void
    {
        std::cout << prefix << (isLast ? "└──" : "├──") << "[]\n";

        for (size_t i = 0; i < m_children.size(); i++)
        {
            std::string newPrefix =
                prefix + (isLast ? "    " : "│   ");

            m_children[i].second->print(
                newPrefix, 
                i == (m_children.size() - 1)
            );
        }
    }

    std::vector<
        std::pair<size_t, std::unique_ptr<Node>>
    > m_children{};
};

#include <iostream>

auto Tree::add_nodes(const Graph& mst, size_t curr, size_t parent, Node& curr_node) -> void
{
    // std::cout << "Adding node " << curr << " with parent " << parent << std::endl;

    for (size_t i = 0; i < mst.size(); i++)
        if (mst.get(curr, i) != INF && curr != i && i != parent)
        {
            curr_node.add_node();
            add_nodes(mst, i, curr, *(curr_node.m_children.back().second));
        }

    return;
}


Tree::Tree(const Graph& mst)
{
    m_root = std::make_unique<Node>();

    add_nodes(mst, 0, 0, *m_root);
}

auto Tree::calc_size2() -> size_t
{
    return m_root->calc_size2();
}

auto Tree::calc_size() -> size_t
{
    return m_root->calc_size();
}

auto Tree::transmit() -> int
{
    return m_root->transmit();
}

auto Tree::print() -> void
{
    m_root->print();
}
