#include<thread>
#include<sstream>
#include<iostream>

void foo(int r){
    for(int g = 0; g < 256; g++)
        for(int b = 0; b < 256; b++){
            std::stringstream ss;
            ss << "\033[38;2;"<<r<<";"<<g<<";"<<b<<"mHello World";
            std::cout << ss.str();
        }
}

int main(){
    // std::cout.sync_with_stdio(false);
    // std::cin.tie(NULL);

    int n = 256;
    std::thread thr[n];

    int r;
    for(r = 0; r < n; r++){
        thr[r] = std::thread(foo,r);
    }
    for(r = 0; r < n; r++){
        thr[r].join();
    }
    return 0;
}