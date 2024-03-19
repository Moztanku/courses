#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <thread>

#include "misc.hpp"
#include "crossovers.hpp"
#include "selections.hpp"
#include "mutations.hpp"
#include "localsearch.hpp"

struct GAParams {
    uint popSize;
    uint maxStepsWOImprovement;
    Select select;
    CrossOver cross;
    Mutate mutate;
    bool elitism{};
    int memes{};
};

Population generateInitialPopulation(const Vertices& vertices, const uint popSize)
{
    Population population(popSize);

    for (auto& cycle : population)
        cycle = randomPermutation(vertices.size());

    return population;
}

struct Elite {
    const size_t size;
    std::vector<Cycle> members{};
    std::vector<uint> costs{};
    uint worst{UINT32_MAX};
};

void addToElite(const Cycle& cycle, const uint cost, Elite& elite)
{
    if (elite.members.size() < elite.size)
    {
        elite.members.push_back(cycle);
        elite.costs.push_back(cost);

        return;
    }

    for (size_t i = 0; i < elite.size; i++)
    {
        if (elite.costs[i] == elite.worst)
        {
            elite.members[i] = cycle;
            elite.costs[i] = cost;

            elite.worst = *std::max_element(elite.costs.begin(), elite.costs.end());

            return;
        }
    }
}

Cycle geneticAlgorithm(const Vertices& vertices, const GAParams& params)
{
    auto start = std::chrono::high_resolution_clock::now();
    const uint N = vertices.size();
    const auto& maxStepsWOImprovement = params.maxStepsWOImprovement;
    const auto& select = params.select;
    const auto& cross = params.cross;
    const auto& mutate = params.mutate;
    const auto& elitism = params.elitism;
    const auto& memes = params.memes;

    Population population = generateInitialPopulation(vertices, params.popSize);
    std::vector<size_t> changed;
    changed.reserve(population.size());

    std::vector<uint> costs;
    costs.reserve(population.size());

    Elite elite{.size = population.size() / 100};
    if (elitism) {
        elite.members.reserve(elite.size);
        elite.costs.reserve(elite.size);
    }

    for (size_t i = 0; i < population.size(); i++)
        costs[i] = getCost(population[i], vertices);

    if (elitism)
        for (size_t i = 0; i < population.size(); i++)
        {
            if (costs[i] < elite.worst)
            {
                addToElite(population[i], costs[i], elite);
            }
        }

    struct {
        Cycle cycle{};
        uint cost{UINT32_MAX};
    } best;

    uint stepsWOImprovement = 0;

    Parrents parrents(population.size() / 4);
    Cycle ch1(vertices.size());
    Cycle ch2(vertices.size());
    while (stepsWOImprovement <= maxStepsWOImprovement)
    {
        select(population, costs, parrents);

        for (auto& [p1,p2] : parrents)
        {

            Cycle& p1c = population[p1];
            Cycle& p2c = population[p2];

            cross(p1c,p2c,ch1);
            cross(p2c,p1c,ch2);
            
            p1c = ch1;
            p2c = ch2;

            mutate(p1c);
            mutate(p2c);

            changed.push_back(p1);
            changed.push_back(p2);

        }

        if (elitism)
            for (size_t i = 0; i < elite.size; i++)
            {
                const size_t index = myRand() % population.size();
                const Cycle& cycle = elite.members[i];

                population[index] = cycle;
                costs[index] = elite.costs[i];

                changed.push_back(index);
            }


        bool improvement = false;
        for (const size_t cycle : changed)
        {
            localSearch(population[cycle], vertices, memes);

            const uint cost = getCost(population[cycle], vertices);
            costs[cycle] = cost;

            if (elitism && cost < elite.worst)
            {
                addToElite(population[cycle], cost, elite);
            }

            if (cost < best.cost)
            {
                best.cost = cost;
                best.cycle = population[cycle];

                improvement = true;
            }
        }

        changed.clear();

        if (improvement)
            stepsWOImprovement = 0;
        else
            stepsWOImprovement++;
    }

    return best.cycle;
}

int main(int arg_count, char** args)
{
    auto start = std::chrono::high_resolution_clock::now();
    if(arg_count < 2)
        throw std::runtime_error("Error: no input file specified");

    uint threads = 1;

    if (arg_count > 2)
        threads = std::min(
            static_cast<uint>(std::stoi(args[2])),
            std::thread::hardware_concurrency()
        );

    Vertices vertices = getVerticesFromFile(args[1]);
    const uint N = 100;

    const GAParams params{
        .popSize = 10000,
        .maxStepsWOImprovement = 500,
        .select = islandTourneySelect,
        .cross = OXCrossOver,
        .mutate = mutateSwap,
        .elitism = false,
        .memes = 0
    };

    std::mutex mutex;
    uint bestCost = std::numeric_limits<uint>::max();
    uint worstCost = 0;
    float avgCost = 0.f;

    std::vector<std::thread> workers(threads);
    
    const int iterPerThread = N / threads;
    int remainder = N % threads;

    for (size_t i = 0; i < threads; i++)
    {
        auto& worker = workers[i];

        const int id = i + 1;
        const int n = iterPerThread + (i < remainder ? 1 : 0);

        worker = std::thread([&vertices, &params, &mutex, &bestCost, &worstCost, &avgCost, &N](const uint n, const int id)
        {
            repeat(n)
            {
                const Cycle cycle = geneticAlgorithm(vertices, params);

                const uint cost = getCost(cycle, vertices);

                std::clog << std::format("Thread {}: {} / {}", id, i + 1, n) << std::endl;
                std::lock_guard<std::mutex> lock(mutex);

                bestCost = std::min(bestCost, cost);
                worstCost = std::max(worstCost, cost);
                avgCost += static_cast<float>(cost) / N;
            }
        }, n, id);
    }

    for (auto& worker : workers)
        worker.join();

    std::clog << "Best cost: " << bestCost << std::endl;
    std::clog << "Worst cost: " << worstCost << std::endl;
    std::clog << "Avg cost: " << avgCost << std::endl;

    std::cout << args[1] << " " << bestCost << " " << worstCost << " " << avgCost << std::endl;

    return 0;
}