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
#include <chrono>
#include <set>
#include <list>

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

int myRand()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, std::numeric_limits<int>::max());

    return dis(gen);
}

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

using Cycle = std::vector<size_t>;

constexpr float d(const Vertex& v1, const Vertex& v2)
{
    const float dx = v1.x - v2.x;
    const float dy = v1.y - v2.y;
    return sqrtf(dx * dx + dy * dy);
}

int getCostDifference(const Cycle& cycle, const std::vector<Vertex>& vertices, const size_t i, const size_t j)
{
    int cost_diff = 0;

    if (i == 0) {
        cost_diff -= d(
            vertices[cycle[i]], 
            vertices[cycle[cycle.size() - 1]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[j]],
            vertices[cycle[cycle.size() - 1]]) + 0.5f;
    } else {
        cost_diff -= d(
            vertices[cycle[i - 1]],
            vertices[cycle[i]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[i - 1]],
            vertices[cycle[j]]
            ) + 0.5f;
    }

    if (j + 1 == cycle.size()) {
        cost_diff -= d(
            vertices[cycle[0]],
            vertices[cycle[j]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[0]],
            vertices[cycle[i]]) + 0.5f;
    } else {
        cost_diff -= d(
            vertices[cycle[j + 1]],
            vertices[cycle[j]]) + 0.5f;
        cost_diff += d(
            vertices[cycle[j + 1]],
            vertices[cycle[i]]) + 0.5f;
    }

    return cost_diff;
}

void reverse(Cycle& cycle, const size_t i, const size_t j)
{
    if(i == j)
        return;

    for (size_t k = 0; k < (j - i + 1) / 2; k++)
        std::swap(cycle[i + k], cycle[j - k]);
}

uint getCost(const Cycle& cycle, const std::vector<Vertex>& vertices)
{
    uint cost = 0;
    for (size_t i = 0; i < cycle.size() - 1; i++)
        cost += d(vertices[cycle[i]], vertices[cycle[i + 1]]) + 0.5f;

    cost += d(vertices[cycle[0]], vertices[cycle[cycle.size() - 1]]) + 0.5f;

    return cost;
}

void localSearch(const Cycle& initialCycle = {}, const std::vector<Vertex>& vertices = {})
{
    static float avg_res = 0.f;
    static float avg_it = 0.f;
    static uint best_res = std::numeric_limits<uint>::max();
    static size_t count = 0;

    count++;

    if (initialCycle.size() == 0 && vertices.size() == 0)
    {
        std::cout << "Średnia wartość uzyskanego rozwiązania: " << avg_res << std::endl;
        std::cout << "Średnia liczba kroków poprawy: " << avg_it << std::endl;
        std::cout << "Najlepsze uzyskane rozwiązanie: " << best_res << std::endl;
        return;
    }

    Cycle r = initialCycle;
    bool maxima = true;
    int iterations = -1;

    do {
        maxima = true;
        int max_diff = 0;
        int min_i = 0;
        int min_j = 0;
        iterations++;
        for (size_t i = 0; i < r.size() - 1; i++)
            for (size_t j = i + 1; j < r.size(); j++)
            {
                if (j - i + 2 >= r.size())
                    continue;

                int cost_diff = getCostDifference(r, vertices, i, j);

                if (cost_diff < max_diff) {
                    max_diff = cost_diff;
                    min_i = i;
                    min_j = j;
                    maxima = false;
                }
            }

        reverse(r, min_i, min_j);
    } while (!maxima);

    uint cost = getCost(r, vertices);

    avg_res *= (count - 1) / static_cast<float>(count);
    avg_res += cost / static_cast<float>(count);

    avg_it *= (count - 1) / static_cast<float>(count);
    avg_it += iterations / static_cast<float>(count);

    best_res = std::min(best_res, cost);
}

// Tabu search
struct TabuParameters {
    uint tabu_size;
    uint iterations;
    uint max_iterations_without_improvement;
};

template<TabuParameters params>
void tabuSearch(const Cycle& cycle = {}, const std::vector<Vertex>& vertices = {})
{
    static struct {
        uint count = 0;
        uint best_res = std::numeric_limits<uint>::max();
        float avg_res = 0.f;
    } stats;

    if (vertices.size() == 0 && cycle.size() == 0)
    {
        std::cout << std::endl;
        std::cout << std::format("Parametry: tabu_size = {}, iterations = {}", params.tabu_size, params.iterations) << std::endl;
        std::cout << std::format("Wyniki: średnia = {}, najlepszy = {}", stats.avg_res, stats.best_res) << std::endl;

        return;
    }

    Cycle curr = cycle;
    Cycle best = cycle;
    std::list<std::pair<size_t, size_t>> tabu_list;
    int iterations_without_improvement = 0;
    
    do {
        int max_diff = 999;
        int min_i = 0;
        int min_j = 0;

        for (size_t _ = 0; _ < params.iterations; _++)
        {
            const auto [i, j] = std::minmax(
                static_cast<size_t>(myRand() % curr.size()),
                static_cast<size_t>(myRand() % curr.size())
            );

            if (j - i + 2 >= curr.size())
                continue;

            if (std::find(tabu_list.begin(), tabu_list.end(), std::pair{i, j}) != tabu_list.end()) {
                continue;
            }

            const int cost_diff = getCostDifference(curr, vertices, i, j);

            if (cost_diff < max_diff) {
                max_diff = cost_diff;
                min_i = i;
                min_j = j;
            }
        }

        if (max_diff >= 0)
            iterations_without_improvement++;
        else
            iterations_without_improvement = 0;

        reverse(curr, min_i, min_j);

        if (tabu_list.size() == params.tabu_size)
            tabu_list.pop_front();

        tabu_list.push_back({min_i, min_j});

        if (getCost(curr, vertices) < getCost(best, vertices))
            best = curr;

    } while (
        // tabu_list.size() < params.tabu_size
        iterations_without_improvement < params.max_iterations_without_improvement
    );

    stats.count++;

    uint cost = getCost(best, vertices);
    stats.avg_res *= (stats.count - 1) / static_cast<float>(stats.count);
    stats.avg_res += cost / static_cast<float>(stats.count);
    stats.best_res = std::min(stats.best_res, cost);
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

// Simulated annealing
struct AnnealingParameters {
    float T0;
    float Talpha;
    float Tend;
    uint iterations;
};

float randomFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.f, 1.f);

    return dis(gen);
}

template<AnnealingParameters params>
void simulatedAnnealing(const Cycle& initialCycle = {}, const std::vector<Vertex>& vertices = {})
{
    static struct {
        uint count = 0;
        uint best_res = std::numeric_limits<uint>::max();
        float avg_res = 0.f;
    } stats;

    if (vertices.size() == 0 && initialCycle.size() == 0)
    {
        std::cout << std::format("Parametry: T0 = {}, Talpha = {}, Tend = {}", params.T0, params.Talpha, params.Tend) << std::endl;
        std::cout << std::format("Wyniki: średnia = {}, najlepszy = {}", stats.avg_res, stats.best_res) << std::endl;
        std::cout << std::endl;

        return;
    }

    Cycle prev = initialCycle;
    Cycle curr = initialCycle;
    float T = params.T0;

    do {
        prev = curr;
        for (uint _ = 0; _ < params.iterations; _++) 
        {
            const auto [i, j] = std::minmax(
                static_cast<size_t>(myRand() % curr.size()),
                static_cast<size_t>(myRand() % curr.size())
            );

            if (j - i + 2 >= curr.size())
                continue;

            const int cost_diff = getCostDifference(curr, vertices, i, j);

            if (cost_diff < 0)
                reverse(curr, i, j);
            else if (randomFloat() < expf(-cost_diff / T)){
                reverse(curr, i, j);
            }
        }

        T *= params.Talpha;
    } while (T > params.Tend);

    stats.count++;

    uint cost = getCost(curr, vertices);
    stats.avg_res *= (stats.count - 1) / static_cast<float>(stats.count);
    stats.avg_res += cost / static_cast<float>(stats.count);
    stats.best_res = std::min(stats.best_res, cost);
}

int main(int arg_count, char** args)
{
    if(arg_count < 2)
        throw std::runtime_error("Error: no input file specified");

    std::vector<Vertex> vertices = getVerticesFromFile(args[1]);

    std::cout << args[1] << std::endl;

    std::clog << args[1] << std::endl;

    const uint N = vertices.size() > 1000 ? 100 : 1000;

    using AP = AnnealingParameters;
    {
        constexpr AP params = {
            .T0 = 1000.f,
            .Talpha = 0.8f,
            .Tend = 0.00001f,
            .iterations = 10000
        };

        for (size_t _ = 0; _ < N; _++)
        {
            simulatedAnnealing<params>(randomPermutation(vertices.size()), vertices);
            std::clog << std::format("{}% done", (_ + 1) * 100 / N) << std::endl;
        }
        simulatedAnnealing<params>();
    }
    {
        constexpr AP params = {
            .T0 = 10.f,
            .Talpha = 0.92f,
            .Tend = 0.000001f,
            .iterations = 10000
        };

        for (size_t _ = 0; _ < N; _++)
        {
            simulatedAnnealing<params>(randomPermutation(vertices.size()), vertices);
            std::clog << std::format("{}% done", (_ + 1) * 100 / N) << std::endl;
        }
        simulatedAnnealing<params>();
    }

    // using TP = TabuParameters;
    // {
    //     constexpr TP params = {
    //         .tabu_size = 100,
    //         .iterations = 1000,
    //         .max_iterations_without_improvement = 10
    //     };

    //     for (size_t _ = 0; _ < N; _++)
    //     {
    //         tabuSearch<params>(randomPermutation(vertices.size()), vertices);
    //         std::clog << std::format("{}% done", (_ + 1) * 100 / N) << std::endl;
    //     }

    //     tabuSearch<params>();
    // }
    // {
    //     constexpr TP params = {
    //         .tabu_size = 200,
    //         .iterations = 900,
    //         .max_iterations_without_improvement = 10
    //     };


    //     for (size_t _ = 0; _ < N; _++)
    //     {
    //         tabuSearch<params>(randomPermutation(vertices.size()), vertices);
    //         std::clog << std::format("{}% done", (_ + 1) * 100 / N) << std::endl;
    //     }

    //     tabuSearch<params>();
    // }

    return 0;
}