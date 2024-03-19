#include <iostream>
#include <vector>
#include <fstream>
#include <format>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Vertex{
    int x,y;

    friend auto operator==(const Vertex& v1, const Vertex& v2)
    {
        return (v1.x == v2.x) && (v1.y == v2.y);
    }
};

struct Edge{
    Vertex v1, v2;
    int weight;
};

#define repeat(n) for(int i = 0; i < n; i++)

std::vector<Vertex> getVerticesFromFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::in);
    if(!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return std::vector<Vertex>();
    }

    std::string buffer;
    buffer.reserve(100);

    repeat(5)
    {
        std::getline(file, buffer);
    }

    std::getline(file, buffer);
    int vertex_count = std::stoi(buffer.substr(buffer.find(':') + 1, buffer.size()));

    repeat(2)
    {
        std::getline(file, buffer);
    }

    std::vector<Vertex> vertices;
    vertices.reserve(vertex_count);

    repeat(vertex_count)
    {
        std::getline(file, buffer);

        size_t pos_1 = buffer.find(' ') + 1;
        size_t pos_2 = buffer.find(' ', pos_1);
        int x = std::stoi(buffer.substr(pos_1, pos_2 - pos_1));

        pos_1 = pos_2 + 1;
        int y = std::stoi(buffer.substr(pos_1, buffer.size()));

        vertices.push_back({x, y});
    }

    return vertices;
}

std::vector<Vertex> getRandomVertices(size_t count, int min_x, int max_x, int min_y, int max_y)
{
    std::vector<Vertex> vertices;
    vertices.reserve(count);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(min_x, max_x);
    std::uniform_int_distribution<> dis_y(min_y, max_y);

    repeat(count)
    {
        vertices.push_back({dis_x(gen), dis_y(gen)});
    }

    return vertices;
}

float getDistance(const Vertex& v1, const Vertex& v2)
{
    return std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2));
}

auto getDistanceAndVertex(const std::vector<Vertex>& vertices, const std::set<size_t>& visited, const Vertex& v)
{
    float min_distance = std::numeric_limits<float>::max();
    size_t min_index = 0;
    for(const auto& i : visited)
    {
        float distance = getDistance(vertices[i], v);
        if(distance < min_distance){
            min_distance = distance;
            min_index = i;
        }
    }

    if(min_distance == std::numeric_limits<float>::max())
        throw std::runtime_error("Error: could not find a vertex");

    return std::make_pair(min_distance, min_index);
}

auto getClosestVertex(const std::vector<Vertex>& vertices, const std::set<size_t>& visited)
{
    float min_distance = std::numeric_limits<float>::max();
    size_t min_index_v = 0;
    size_t min_index_w = 0;

    for(size_t i = 0; i < vertices.size(); i++)
    {
        if(visited.find(i) != visited.end())
            continue;

        auto [distance, index] = getDistanceAndVertex(vertices, visited, vertices[i]);
        if(distance < min_distance){
            min_distance = distance;
            min_index_v = index;
            min_index_w = i;
        }
    }

    if(min_distance == std::numeric_limits<float>::max())
        throw std::runtime_error("Error: could not find a vertex");

    return std::make_tuple(min_distance, min_index_v, min_index_w);
}

std::vector<Edge> getMinimalSpanningTree(const std::vector<Vertex>& vertices)
{
    std::vector<Edge> edges;
    std::set<size_t> visited;

    visited.insert(
        rand() % vertices.size()
    );

    while(visited.size() < vertices.size())
    {
        auto [distance, index_v, index_w] = getClosestVertex(vertices, visited);
        edges.push_back({vertices[index_v], vertices[index_w], static_cast<int>(distance)});
        visited.insert(index_w);
    }

    return edges;
}

void printSpanningTree(const std::vector<Edge>& edges)
{
    const int edges_weight = std::accumulate(edges.begin(), edges.end(), 0, [](int sum, const Edge& e){
        return sum + e.weight;
    });
    std::cout << "Spanning tree weight: " << edges_weight << std::endl;

    // const float edges_distance = std::accumulate(edges.begin(), edges.end(), 0.f, [](float sum, const Edge& e){
    //     return sum + getDistance(e.v1, e.v2);
    // });
    // std::cout << "Spanning tree distance: " << edges_distance << std::endl;

    // const int edges_weight_rounding_up = std::accumulate(edges.begin(), edges.end(), 0, [](int sum, const Edge& e){
    //     return sum + std::ceil(getDistance(e.v1, e.v2));
    // });
    // std::cout << "Spanning tree weight (rounding up): " << edges_weight_rounding_up << std::endl;

    // const int edges_weight_rounding_down = std::accumulate(edges.begin(), edges.end(), 0, [](int sum, const Edge& e){
    //     return sum + std::floor(getDistance(e.v1, e.v2));
    // });
    // std::cout << "Spanning tree weight (rounding down): " << edges_weight_rounding_down << std::endl;

    // const int edges_weight_rounding = std::accumulate(edges.begin(), edges.end(), 0, [](int sum, const Edge& e){
    //     return sum + std::round(getDistance(e.v1, e.v2));
    // });
    // std::cout << "Spanning tree weight (rounding): " << edges_weight_rounding << std::endl;
}

void printCycle(const std::vector<Vertex>& cycle)
{
    // float distance = 0.f;
    // int rounding_up = 0;
    int rounding_down = 0;
    // int rounding = 0;

    for (int i = 0; i < cycle.size() - 1; i++){
        // distance += getDistance(cycle[i], cycle[i + 1]);
        // rounding_up += std::ceil(getDistance(cycle[i], cycle[i + 1]));
        rounding_down += std::floor(getDistance(cycle[i], cycle[i + 1]));
        // rounding += std::round(getDistance(cycle[i], cycle[i + 1]));
    }

    // distance += getDistance(cycle[0], cycle[cycle.size() - 1]);
    // rounding_up += std::ceil(getDistance(cycle[0], cycle[cycle.size() - 1]));
    rounding_down += std::floor(getDistance(cycle[0], cycle[cycle.size() - 1]));
    // rounding += std::round(getDistance(cycle[0], cycle[cycle.size() - 1]));

    // std::cout << "Cycle distance: " << distance << std::endl;
    // std::cout << "Cycle distance (rounding up): " << rounding_up << std::endl;
    std::cout << "Cycle distance (rounding down): " << rounding_down << std::endl;
    // std::cout << "Cycle distance (rounding): " << rounding << std::endl;
}

std::vector<Vertex> getCycle(const std::vector<Edge>& edges, const std::vector<Vertex>& vertices)
{
    std::vector<Vertex> cycle;

    std::vector<std::vector<size_t>> adjacency_list(vertices.size());
    for(const auto& e : edges)
    {
        adjacency_list[std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), e.v1))].push_back(std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), e.v2)));
        adjacency_list[std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), e.v2))].push_back(std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), e.v1)));
    }

    std::vector<size_t> stack;
    stack.push_back(0);

    std::vector<bool> visited(vertices.size(), false);
    visited[0] = true;

    while(!stack.empty())
    {
        size_t v = stack.back();
        stack.pop_back();

        cycle.push_back(vertices[v]);

        for(const auto& w : adjacency_list[v])
        {
            if(!visited[w])
            {
                visited[w] = true;
                stack.push_back(w);
            }
        }
    }

    return cycle;
}

void drawVertices(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, const std::vector<Vertex>& cycle);

std::vector<size_t> randomPermutation(const size_t size)
{
    std::vector<size_t> permutation(size);
    std::iota(permutation.begin(), permutation.end(), 0);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(permutation.begin(), permutation.end(), gen);

    return permutation;
}

void experimentMinimumOfPermutations(const std::vector<Vertex>& vertices, const int N, const int K)
{
    int sum = 0;
    for(size_t i = 0; i < N; i++)
    {
        int min = std::numeric_limits<int>::max();
        for(size_t j = 0; j < K; j++)
        {
            std::vector<size_t> permutation = randomPermutation(vertices.size());
            int distance = 0;
            for(size_t k = 0; k < permutation.size() - 1; k++)
            {
                distance += getDistance(vertices[permutation[k]], vertices[permutation[k + 1]]);
            }
            distance += getDistance(vertices[permutation[0]], vertices[permutation[permutation.size() - 1]]);
            min = std::min(min, distance);
        }
        sum += min;
    }

    std::cout << std::format("Average minimum of {} groups, each of {} permutations, for {} vertices: {}", N, K, vertices.size(), static_cast<float>(sum) / N) << std::endl;
}

int main(int arg_count, char** args)
{
    if(arg_count < 2)
        throw std::runtime_error("Error: no input file specified");

    std::vector<Vertex> vertices = getVerticesFromFile(args[1]);
    // std::vector<Vertex> vertices = getRandomVertices(800, 0, 100, 0, 100);

    // 1
    std::vector<Edge> edges = getMinimalSpanningTree(vertices);
    printSpanningTree(edges);

    // 2
    std::vector<Vertex> cycle = getCycle(edges, vertices);
    printCycle(cycle);

    // 3A
    experimentMinimumOfPermutations(vertices, 100, 10);
    // 3B
    experimentMinimumOfPermutations(vertices, 20, 50);
    // 3C
    experimentMinimumOfPermutations(vertices, 1, 1000);

    drawVertices(vertices, edges, cycle);

    return 0;
}

/* Sprawozdanie
    Weight is rounded down to the nearest integer.

    xqf131.tsp
    - Spanning tree weight: 463
    - Cycle weight: 761
    - Optimal: 564
    - 3A: 4272.22
    - 3B: 4133.9
    - 3C: 3873

    xqg237.tsp
    - Spanning tree weight: 878
    - Cycle weight:  1409
    - Optimal: 1019
    - 3A: 11739.83
    - 3B: 11495.45
    - 3C: 11103

    pma343.tsp
    - Spanning tree weight: 1143
    - Cycle weight: 1867
    - Optimal: 1368
    - 3A: 34165.05
    - 3B: 33565.4
    - 3C: 31394

    pka379.tsp
    - Spanning tree weight: 1117
    - Cycle weight: 1771
    - Optimal: 1332
    - 3A: 35317.01
    - 3B: 34646.6
    - 3C: 33226

    bcl380.tsp
    - Spanning tree weight: 1419
    - Cycle weight: 2223
    - Optimal: 1621
    - 3A: 24556.85
    - 3B: 24039.8
    - 3C: 23434

    pbl395.tsp
    - Spanning tree weight: 1097
    - Cycle weight: 1793
    - Optimal: 1281
    - 3A: 19030.79
    - 3B: 18662.1
    - 3C: 18179

    pbk411.tsp
    - Spanning tree weight: 1157
    - Cycle weight: 1846
    - Optimal: 1343
    - 3A: 21447.56
    - 3B: 21138.8
    - 3C: 20628

    pbn423.tsp
    - Spanning tree weight: 1180
    - Cycle weight: 1950
    - Optimal: 1365
    - 3A: 21766.73
    - 3B: 21482.3
    - 3C: 20819

    pbm436.tsp
    - Spanning tree weight: 1238
    - Cycle weight: 2015
    - Optimal: 1443
    - 3A: 22296.01
    - 3B: 21965.8
    - 3C: 20856

    xql662.tsp
    - Spanning tree weight: 2193
    - Cycle weight: 3557
    - Optimal: 2513
    - 3A: 50892.59
    - 3B: 50169.9
    - 3C: 49468

    This could be optimized by removing intersections from the cycle.
*/

void pollEvents(const sf::Event& event, sf::RenderTarget& window);

void drawVertices(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, const std::vector<Vertex>& cycle){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Vertices");
    window.setFramerateLimit(60);

    const int vertice_max_x = std::max_element(vertices.begin(), vertices.end(), [](const Vertex& v1, const Vertex& v2){
        return v1.x < v2.x;
    })->x;

    const int vertice_max_y = std::max_element(vertices.begin(), vertices.end(), [](const Vertex& v1, const Vertex& v2){
        return v1.y < v2.y;
    })->y;

    std::vector<sf::RectangleShape> rectangles(vertices.size());


    // sf::VertexArray vertex_array(sf::Points, vertices.size());
    for(size_t i = 0; i < vertices.size(); i++)
    {
        auto& v = rectangles[i];
        auto& p = vertices[i];
        float size = 0.5f;

        v.setPosition(
            static_cast<float>(p.x) - size / 2.f,
            static_cast<float>(vertice_max_y - p.y) - size / 2.f);
        v.setFillColor(sf::Color::Yellow);
        v.setSize({size, size});
    }

    // const int max_weight = std::max_element(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2){
    //     return e1.weight < e2.weight;
    // })->weight;
    const Edge& max_distance_edge = *std::max_element(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2){
        return getDistance(e1.v1, e1.v2) < getDistance(e2.v1, e2.v2);
    });
    const float max_distance = getDistance(max_distance_edge.v1, max_distance_edge.v2);

    sf::VertexArray edge_array(sf::Lines, edges.size() * 2);
    for(size_t i = 0; i < edges.size(); i++)
    {
        auto& e = edges[i];
        auto& v1 = e.v1;
        auto& v2 = e.v2;
        const sf::Uint8 alpha = 32u + static_cast<sf::Uint8>(100 * (max_distance - getDistance(v1, v2)) / max_distance);

        edge_array[i * 2].position = {
            static_cast<float>(v1.x),
            static_cast<float>(vertice_max_y - v1.y)};
        edge_array[i * 2].color = sf::Color::White;
        edge_array[i * 2].color.a = alpha;

        edge_array[i * 2 + 1].position = {
            static_cast<float>(v2.x),
            static_cast<float>(vertice_max_y - v2.y)};
        edge_array[i * 2 + 1].color = sf::Color::White;
        edge_array[i * 2 + 1].color.a = alpha;
    }

    float max_cycle_distance = 0.f;
    for(size_t i = 0; i < cycle.size(); i++)
    {
        auto& v1 = cycle[i];
        auto& v2 = cycle[(i + 1) % cycle.size()];
        max_cycle_distance = std::max(max_cycle_distance, getDistance(v1, v2));
    }

    sf::VertexArray cycle_array(sf::Lines, cycle.size() * 2);
    for(size_t i = 0; i < cycle.size(); i++)
    {
        auto& v1 = cycle[i];
        auto& v2 = cycle[(i + 1) % cycle.size()];
        const sf::Uint8 alpha = 32u + static_cast<sf::Uint8>(64u * (max_cycle_distance - getDistance(v1, v2)) / max_cycle_distance);

        cycle_array[i * 2].position = {
            static_cast<float>(v1.x),
            static_cast<float>(vertice_max_y - v1.y)};
        cycle_array[i * 2].color = sf::Color::Red;
        cycle_array[i * 2].color.a = alpha;

        cycle_array[i * 2 + 1].position = {
            static_cast<float>(v2.x),
            static_cast<float>(vertice_max_y - v2.y)};
        cycle_array[i * 2 + 1].color = sf::Color::Red;
        cycle_array[i * 2 + 1].color.a = alpha;
    }

    sf::View view(sf::FloatRect(-10.f, -10.f, vertice_max_x + 20.f, vertice_max_y + 20.f));
    window.setView(view);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            pollEvents(event, window);
        }

        window.clear(sf::Color::Black);
        window.draw(cycle_array);
        window.draw(edge_array);
        for(const auto& v : rectangles)
            window.draw(v);
        window.display();
    }
}

void pollEvents(const sf::Event& event, sf::RenderTarget& window)
{
    static bool is_mouse_button_pressed = false;
    static sf::Vector2f mouse_position = {0.f, 0.f};
    switch(event.type)
    {
        case sf::Event::Closed:
            exit(0);
            break;
        case sf::Event::MouseButtonPressed:
            is_mouse_button_pressed = true;
            break;
        case sf::Event::MouseButtonReleased:
            is_mouse_button_pressed = false;
            break;
        case sf::Event::MouseMoved:
            if(is_mouse_button_pressed)
            {
                auto delta = mouse_position - sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                mouse_position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);

                sf::View view = window.getView();

                if(std::abs(delta.x + delta.y) < 10.f)
                    view.move(delta * 1.f * (view.getSize().x / window.getSize().x));

                window.setView(view);
            }
            break;
        case sf::Event::MouseWheelScrolled:
            {
                sf::View view = window.getView();
                view.zoom(1.f - event.mouseWheelScroll.delta * 0.1f);
                window.setView(view);
            }
            break;
        default:
            break;
    }
}