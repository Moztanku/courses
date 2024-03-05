#include <iostream>
#include <algorithm>
#include <set>
#include <random>
#include <chrono>

inline int myRand() noexcept
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, std::numeric_limits<int>::max());

    return dis(gen);
}

int main(int arg_count, char** args)
{
    // std::set<std::pair<size_t, size_t>> tabu_list;

    // const auto [i, j] = std::minmax(
    //     size_t(1), size_t(2)
    // );

    // std::cout << i << " " << j << std::endl;
    // auto it = tabu_list.find({i, j});
    // it == tabu_list.end();
    // std::cout << i << " " << j << std::endl;

    myRand();

    int sum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000000; ++i)
    {
        sum += myRand();
    }
    auto end = std::chrono::high_resolution_clock::now();

    sum = 0;

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000000; ++i)
    {
        sum += rand();
    }
    end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;


    return 0;
}