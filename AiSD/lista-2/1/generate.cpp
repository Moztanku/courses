#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

int main(int argc, char const *argv[]) {
    const int n = std::stoi(argv[1]);

    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 1);

    if(argv[2] == nullptr || argv[2] == std::string("random")){
        std::shuffle(
            v.begin(),
            v.end(),
            std::default_random_engine(std::random_device()())
        );
    } else if(argv[2] == std::string("reverse")){
        std::reverse(v.begin(), v.end());
    }

    std::cout << n << std::endl;
    for(int i = 0; i < n; i++)
        std::cout << v[i] << std::endl;

    return 0;
}