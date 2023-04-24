#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <string>
#include <functional>

bool isSolvable(const std::vector<int>& puzzle);
std::vector<int> createPuzzle();

void printPuzzle(const std::vector<int>& puzzle);

int manhattanDistance(const int value, const int position){
    if(value == 0) return 0;

    return std::abs((value - 1) / 4  - position / 4)
        + std::abs((value - 1) % 4 - position % 4);
}

int hammingDistance(const int value, const int position){
    if(value == 0) return 0;

    return (value - 1) == position;
}

void solve(std::vector<int>& puzzle, std::function<int(const int, const int)> heuristic){
    
}

int main(int argc, char** argv) {
    std::vector<int> puzzle = createPuzzle();
    printPuzzle(puzzle);

    if(argv[1] == nullptr || argv[1] == std::string("manhattan")){
        solve(puzzle, manhattanDistance);
    } else if(argv[1] == std::string("hamming")){
        solve(puzzle,hammingDistance);
    } else {
        std::cout << "Invalid argument" << std::endl;
    }

    return 0;
}

bool isSolvable(const std::vector<int>& puzzle){
    int inversions = 0;
    for(int i = 0; i < puzzle.size() - 1; i++){
        for(int j = i + 1; j < puzzle.size() - 1; j++){
            if(puzzle[i] > puzzle[j]){
                inversions++;
            }
        }
    }
    return inversions % 2 == 0;
}

std::vector<int> createPuzzle(){
    std::vector<int> puzzle(16,0);
    std::iota(puzzle.begin(), puzzle.end() - 1, 1);

    do std::shuffle(puzzle.begin(), puzzle.end() - 1, std::mt19937{std::random_device{}()});
    while(!isSolvable(puzzle));

    return puzzle;
}


void printPuzzle(const std::vector<int>& puzzle){
    for(int i = 0; i < puzzle.size(); i++){
        if(i % 4 == 0){
            std::cout << std::endl;
        }
        std::cout << puzzle[i] << " ";
    }
    std::cout << std::endl;
}