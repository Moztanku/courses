#include <iostream>
#include <array>

#include "Queue.hpp"
#include "Stack.hpp"

template <class DS>
void testDataStructure(DS& ds)
{
    constexpr std::array<int, 20> data = {
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    };

    for (const auto i : data)
        ds.push(i);

    while (!ds.empty())
        std::cout << ds.pop() << " ";
    std::cout << std::endl;
}

int main() {
    Queue<int> q;
    Stack<int> s;

    std::cout << "Queue: ";
    testDataStructure(q);

    std::cout << "Stack: ";
    testDataStructure(s);
    return 0;
}