#pragma once

#include <random>
#include <functional>
#include <fstream>
#include <iostream>
#include <span>

#define repeat(n) for(int i = 0; i < n; i++)

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

using Cycle = std::vector<size_t>;
using Vertices = std::vector<Vertex>;
using Population = std::vector<Cycle>;
using Parrents = std::vector<std::pair<size_t, size_t>>;
using Select = std::function<void(const std::span<const Cycle>&, const std::span<const uint>&, std::span<std::pair<size_t,size_t>>)>;
using CrossOver = std::function<void(const Cycle&, const Cycle&, Cycle&)>;
using Mutate = std::function<void(Cycle&)>;

int myRand()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, std::numeric_limits<int>::max());

    return dis(gen);
}

float randomFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.f, 1.f);

    return dis(gen);
}

Vertices getVerticesFromFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::in);
    if(!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return Vertices();
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

    Vertices vertices;
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


constexpr float d(const Vertex& v1, const Vertex& v2)
{
    const float dx = v1.x - v2.x;
    const float dy = v1.y - v2.y;
    return sqrtf(dx * dx + dy * dy);
}

uint getCost(const Cycle& cycle, const Vertices& vertices)
{
    uint cost = 0;

    if (cycle.size() == 0)
        return cost;

    for (size_t i = 0; i < cycle.size() - 1; i++)
        cost += d(vertices[cycle[i]], vertices[cycle[i + 1]]) + 0.5f;

    cost += d(vertices[cycle[0]], vertices[cycle[cycle.size() - 1]]) + 0.5f;

    return cost;
}

Cycle randomPermutation(const size_t size)
{
    std::vector<size_t> permutation(size);
    std::iota(permutation.begin(), permutation.end(), 0);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(permutation.begin(), permutation.end(), gen);

    return permutation;
}