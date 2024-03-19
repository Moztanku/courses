#include <iostream>

#include "Galois.hpp"

using GF1234577 = Galois<1234577>;
using GF = GF1234577;

template<typename T>
bool CheckEQ(const T& a, const T& b)
{
    if (a != b)
    {
        std::cerr << "CheckEQ: " << a << " != " << b << std::endl;
        return false;
    }
    return true;
}

int TestComparisionOperators()
{
    GF a(1);
    GF b(2);
    GF c(3);

    return CheckEQ(a < b, true) && CheckEQ(b < c, true) && CheckEQ(a > c, false)
        && CheckEQ(a == a, true) && CheckEQ(b == b, true) && CheckEQ(c == a, false)
        && CheckEQ(a != b, true) && CheckEQ(b != c, true) && CheckEQ(a != a, false)
        && CheckEQ(a >= b, false) && CheckEQ(b >= c, false) && CheckEQ(a >= a, true)
        ? EXIT_SUCCESS : EXIT_FAILURE;
}

int TestArithmeticOperators()
{
    GF a(1);
    GF b(2);
    GF c(3);

    return CheckEQ(a + b, c) && CheckEQ(b - a, a) && CheckEQ(a * b, b)
        && CheckEQ(b * c, GF(6)) && CheckEQ(c / b, GF(617290)) && CheckEQ(-a, GF(1234576))
        ? EXIT_SUCCESS : EXIT_FAILURE;
}

int TestAssignmentOperators()
{
    GF a(1);
    GF b(2);
    GF c(3);
    GF d(4);

    a += GF(10);
    b -= GF(10);
    c *= GF(10);
    d /= GF(4);

    return CheckEQ(a, GF(11)) && CheckEQ(b, GF(1234569)) && CheckEQ(c, GF(30)) && CheckEQ(d, GF(1))
        ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main()
{
    return TestComparisionOperators()
        || TestArithmeticOperators()
        || TestAssignmentOperators();
}