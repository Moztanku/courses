#include <iostream>

#include <map>
#include <queue>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include <optional>
#include <algorithm>
#include <functional>

#define FAST_RANDOM true

constexpr double INF = std::numeric_limits<double>::infinity();

class Graph
{
    public:
        Graph(const size_t size, const std::optional<double> initial = std::nullopt) : m_size{size}
        {
            m_adjMat.resize(m_size);
            // m_adjMat.resize(m_size * (m_size - 1) / 2);

            // Resize the adjacency matrix to store only the upper triangular part, no need to store [i][j] and [j][i]
            for (size_t i = 0; i < m_size; i++)
            {
                m_adjMat[i].resize(
                    m_size - i - 1
                );
            }

        #if not FAST_RANDOM
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
        #endif

            // Fill the adjacency matrix with random values (or the initial value if provided)
            for (size_t i = 0; i < m_size; i++)
                for (size_t j = i + 1; j < m_size; j++)
                    if (initial.has_value())
                        m_adjMat[i][j - i - 1] = initial.value();
                        // m_adjMat[i * (m_size - i - 1) + j - i - 1] = initial.value();
                    else
                    #if not FAST_RANDOM
                        m_adjMat[i][j - i - 1] = dis(gen);
                        // m_adjMat[i * (m_size - i - 1) + j - i - 1] = dis(gen);
                    #else
                        m_adjMat[i][j - i - 1] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
                        // m_adjMat[i * (m_size - i - 1) + j - i - 1] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
                    #endif
                        // m_adjMat[i][j - i - 1] = dis(gen);
        }

        auto size() const -> size_t
        {
            return m_size;
        }

        auto get(size_t i, size_t j) const -> double
        {
            if (i == j)
                return 0.0;

            if (i > j)
                std::swap(i, j);

            return m_adjMat[i][j - i - 1];
            // return m_adjMat[i * (m_size - i - 1) + j - i - 1];
        }

        auto set(size_t i, size_t j, double val) -> void
        {
            if (i == j)
                return;

            if (i > j)
                std::swap(i, j);

            m_adjMat[i][j - i - 1] = val;
            // m_adjMat[i * (m_size - i - 1) + j - i - 1] = val;
        }

    private:
        const size_t m_size;
        std::vector<std::vector<double>> m_adjMat;
        // std::vector<double> m_adjMat;
};

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

auto main() -> int
{
    constexpr uint N_min  =  100;
    constexpr uint N_step =  100;
    constexpr uint N_max  = 10000;

    constexpr uint K = 10;

    std::map<uint, double> prim_times;
    std::map<uint, double> kruskal_times;

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    for (uint N = N_min; N <= N_max; N += N_step)
    {
        std::clog << "Running for N = " << N << std::endl;

        prim_times[N] = 0.0;
        kruskal_times[N] = 0.0;

        for (uint _ = 0; _ < K; _++)
        {
            Graph full_graph(N);

            start = std::chrono::high_resolution_clock::now();
            Graph mst_prim = prim(full_graph);
            end = std::chrono::high_resolution_clock::now();

            prim_times[N] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            Graph mst_kruskal = kruskal(full_graph);
            end = std::chrono::high_resolution_clock::now();

            kruskal_times[N] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        prim_times[N] /= K;
        kruskal_times[N] /= K;
    }

    std::cout << "#N\t\tPrim\t\tKruskal" << std::endl;
    for (uint N = N_min; N <= N_max; N += N_step)
    {
        std::cout << N << "\t\t" << prim_times[N] / 1000.0 << "\t\t" << kruskal_times[N] / 1000.0 << std::endl;
    }

}