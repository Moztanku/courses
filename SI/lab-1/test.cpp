#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

using vector = std::vector<int>;

vector& inc(vector& v){
    std::for_each(v.begin(), v.end(), [](int& i){ i++; });
    return v;
}

vector& dec(vector& v){
    std::for_each(v.begin(), v.end(), [](int& i){ i--; });
    return v;
}

vector& sum(vector& v, int i){
    std::for_each(v.begin(), v.end(), [i](int& j){ j += i; });
    return v;
}

vector& mul(vector& v, int i){
    std::for_each(v.begin(), v.end(), [i](int& j){ j *= i; });
    return v;
}

vector& pow(vector& v, int i){
    std::for_each(v.begin(), v.end(), [i](int& j){ j = std::pow(j, i); });
    return v;
}

vector& mod(vector& v, std::function<int(int)> f){
    std::for_each(v.begin(), v.end(), [f](int& i){ i = f(i); });
    return v;
}

vector& fun(vector& v, std::function<void(int)> f){
    std::for_each(v.begin(), v.end(), [f](int& i){ f(i); });
    return v;
}

vector& zero(vector& v){
    std::for_each(v.begin(), v.end(), [](int& i){ i = 0; });
    return v;
}

vector& reverse(vector& v){
    std::reverse(v.begin(), v.end());
    return v;
}

vector& invert(vector& v){
    std::for_each(v.begin(), v.end(), [](int& i){ i = -i; });
    return v;
}

auto main() -> int
{
    vector v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    fun(
        reverse(
            mod(v, [](int i){ return i < 6? i : i % 5;})
        ),
        [](int i){ std::cout << i; }
    );

    return 0;
}