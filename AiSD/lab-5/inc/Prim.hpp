#pragma once

#include "Graph.hpp"

#include <queue>
#include <functional>

// auto prim(const Graph& graph) -> Graph
// {
//     // Lambda function to find the closest node to the visited nodes
//     constexpr auto find_closest = [](const Graph& graph, const std::vector<bool>& visited)
//     {
//         struct Closest
//         {
//             size_t i{0};
//             size_t j{0};
//             double val{INF};
//         } min;

//         for (size_t i = 0; i < graph.size(); i++)
//         {
//             if (!visited[i])
//                 continue;

//             for (size_t j = 0; j < graph.size(); j++)
//             {
//                 if (visited[j])
//                     continue;

//                 if (graph.get(i, j) < min.val)
//                 {
//                     min.val = graph.get(i, j);
//                     min.i = i;
//                     min.j = j;
//                 }
//             }
//         }

//         return min;
//     };

//     // Create a new graph to store the minimum spanning tree, initially filled with INF to represent no edge
//     Graph mst(graph.size(), INF);

//     std::vector<bool> visited(graph.size(), false);
//     int visited_count = 0;

//     visited[0] = true;
//     visited_count++;

//     // Find the closest node to the current mst until all nodes are visited
//     while (visited_count < graph.size())
//     {
//         auto min = find_closest(graph, visited);

//         mst.set(min.i, min.j, graph.get(min.i, min.j));

//         visited[min.j] = true;
//         visited_count++;
//     }

//     return mst;
// }

struct EdgeComparator {
    bool operator()(const std::pair<double, std::pair<size_t, size_t>>& a,
                    const std::pair<double, std::pair<size_t, size_t>>& b) const {
        return a.first > b.first;
    }
};

auto prim(const Graph& graph) -> Graph {
    // Min-heap to store the edges
    std::priority_queue<
        std::pair<double, std::pair<size_t, size_t>>,
        std::vector<std::pair<double, std::pair<size_t, size_t>>>,
        EdgeComparator> heap;

    // New graph to store the minimum spanning tree
    Graph mst(graph.size(), INF);

    std::vector<bool> visited(graph.size(), false);

    // Best weights to each vertex
    std::vector<double> best_weights(graph.size(), INF);

    // Add the first vertex to the MST
    size_t current_vertex = 0;
    visited[current_vertex] = true;
    best_weights[current_vertex] = 0;

    // Add all edges from the first vertex to the heap
    for (size_t j = 0; j < graph.size(); j++) {
        if (graph.get(current_vertex, j) != INF) {
            heap.push({graph.get(current_vertex, j), {current_vertex, j}});
            best_weights[j] = graph.get(current_vertex, j);
        }
    }

    while (!heap.empty()) {
        auto [weight, vertices] = heap.top();
        heap.pop();

        auto [i, j] = vertices;

        if (!visited[j]) {
            mst.set(i, j, weight);
            visited[j] = true;

            for (size_t k = 0; k < graph.size(); k++) {
                double edge_weight = graph.get(j, k);
                if (!visited[k] && edge_weight < best_weights[k]) {
                    // Decrease key by removing and re-inserting with updated weight
                    heap.push({edge_weight, {j, k}});
                    best_weights[k] = edge_weight;
                }
            }
        }
    }

    return mst;
}
