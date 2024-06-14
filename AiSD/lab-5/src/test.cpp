#include <iostream>

#include <vector>
#include <memory>
#include <random>

class Vertex
{
    public:
        Vertex() : m_id(s_id++) {}

        auto id() const -> int { return m_id; }
    private:
        const int m_id;
        static int s_id;
};

int Vertex::s_id = 0;

struct Edge
{
    Edge(const Vertex* u, const Vertex* v, double weight) : u(u), v(v), weight(weight) {}

    const Vertex* u;
    const Vertex* v;
    const double weight;
};

auto connect(const Vertex& u, const Vertex& v) -> Edge
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0, 1);

    return Edge(&u, &v, dis(gen));
}

auto prims(const std::vector<Vertex>& V, const std::vector<Edge>& E) -> std::vector<Edge>
{
    // constexpr auto find_closest = [](const std::vector<Vertex>& V, const std::vector<Edge>& E, const std::vector<Edge>& T) -> Edge
    // {

    // }

    std::vector<Edge> T;

    const Vertex* v = &V[0];
    Vertex* closest = nullptr;

    // while (T.size() < V.size() - 1)
    // {

    // }

    return T;
}

auto kruskals(const std::vector<Vertex>& V, const std::vector<Edge>& E) -> std::vector<Edge>
{
    std::vector<Edge> T;

    // while (T.size() < V.size() - 1)
    // {

    // }

    return T;
}

auto main() -> int
{
    constexpr size_t N = 100;

    // G = (V, E)
    std::vector<Vertex> V(100);
    std::vector<Edge> E;
    E.reserve((N * (N - 1)) / 2);

    for (size_t i = 0; i < N; i++)
        for (size_t j = i + 1; j < N; j++)
            E.push_back(connect(V[i], V[j]));
}