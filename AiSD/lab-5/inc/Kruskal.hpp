#pragma once

#include "Graph.hpp"

#include <queue>
#include <algorithm>
#include <functional>

auto kruskal(const Graph& graph) -> Graph
{
    struct Edge
    {
        size_t src, dest;
        double weight;
    };

    // Create a vector to store the edges
    std::vector<Edge> edges;

    // Fill the vector with all the edges in the graph
    for (size_t i = 0; i < graph.size(); i++)
    {
        for (size_t j = i + 1; j < graph.size(); j++)
        {
            if (graph.get(i, j) != INF)
            {
                edges.push_back({i, j, graph.get(i, j)});
            }
        }
    }

    // Sort the edges by weight
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b)
    {
        return a.weight < b.weight;
    });

    // Create a vector to store the parent of each node
    std::vector<size_t> parent(graph.size());
    std::iota(parent.begin(), parent.end(), 0);

    // Function to find the parent of a node
    const std::function<size_t(size_t)> find = [&parent, &find](size_t i)
    {
        if (parent[i] == i)
        {
            return i;
        }
        return parent[i] = find(parent[i]);
    };

    // Function to union two nodes
    auto union_nodes = [&parent, &find](size_t i, size_t j)
    {
        parent[find(i)] = find(j);
    };

    // Create a new graph to store the minimum spanning tree
    Graph mst(graph.size(), INF);

    // Add the edges to the minimum spanning tree
    for (const auto& edge : edges)
    {
        if (find(edge.src) != find(edge.dest))
        {
            mst.set(edge.src, edge.dest, edge.weight);
            union_nodes(edge.src, edge.dest);
        }
    }

    return mst;
}
