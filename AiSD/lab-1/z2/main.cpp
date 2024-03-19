#include <iostream>
#include <format>
#include <random>
#include <array>

#include "List.hpp"

void printList(List<int>& list)
{
    for (size_t i = 0; i < list.size(); i++)
        std::cout << list[i] << " ";
    std::cout << std::endl;
}

void TestMerge()
{
    std::array<int,10> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    List<int> list1;
    List<int> list2;

    for (const auto i : data)
    {
        insert(list1, i);
        insert(list2, i);
    }


    std::cout << "List1: ";
    printList(list1);

    std::cout << "List2: ";
    printList(list2);

    merge(list1, list2);

    std::cout << "Merged: ";
    printList(list1);
}

int randomInt(int min, int max)
{
    static std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<int> dist{min, max};

    return dist(mt);
}

void Test10000()
{
    std::array<int, 10000> T{};
    for (size_t i = 0; i < T.size(); i++)
        T[i] = randomInt(0, 100000);

    List<int> L;
    for (const auto i : T)
        insert(L, i);

    uint cost_max = 0;
    uint cost_min = UINT32_MAX;
    float cost_sum = 0.f;

    uint N = 1000;
    for (size_t _ = 0; _ < N; _++)
    {
        int searched = T[randomInt(0, T.size() - 1)];
        uint cost = 0;

        for (size_t i = 0; i < L.size(); i++)
        {
            cost++;
            if (L[i] == searched)
                break;
        }

        cost_max = std::max(cost_max, cost);
        cost_min = std::min(cost_min, cost);
        cost_sum += cost;
    }

    std::cout << std::format(
        "1) Max: {}, Min: {}, Sum: {}, Avg: {}\n",
        cost_max, cost_min, cost_sum, cost_sum / N
    );

    cost_max = 0;
    cost_min = UINT32_MAX;
    cost_sum = 0.f;

    for (size_t _ = 0; _ < N; _++)
    {
        int searched = randomInt(0, 100000);
        uint cost = 0;

        for (size_t i = 0; i < L.size(); i++)
        {
            cost++;
            if (L[i] == searched)
                break;
        }

        cost_max = std::max(cost_max, cost);
        cost_min = std::min(cost_min, cost);
        cost_sum += cost;
    }

    std::cout << std::format(
        "2) Max: {}, Min: {}, Sum: {}, Avg: {}\n", 
        cost_max, cost_min, cost_sum, cost_sum / N
    );
}

int main()
{
    TestMerge();
    Test10000();
    return 0;
}
