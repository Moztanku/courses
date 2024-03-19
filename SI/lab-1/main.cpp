#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>
#include <set>
#include <time.h>
#include <queue>
#include <string>
#include <map>

using Puzzle = uint64_t;

Puzzle solved = 0x123456789ABCDEF0;
Puzzle easy = 0x123456789ABCD0EF;

bool isSolvable(const std::vector<int>& puzzle);
Puzzle createPuzzle();

int linearConflict(Puzzle puzzle);
int manhattanDistance(Puzzle puzzle);
int hammingDistance(Puzzle puzzle);

void printPuzzle(Puzzle puzzle);

Puzzle swap(Puzzle puzzle, int i, int j){
    uint8_t value_i = (puzzle >> ((15 - i) * 4)) & 0xF;
    uint8_t value_j = (puzzle >> ((15 - j) * 4)) & 0xF;
    puzzle &= ~(0xFul << ((15 - i) * 4));
    puzzle &= ~(0xFul << ((15 - j) * 4));
    puzzle |= static_cast<uint64_t>(value_i) << ((15 - j) * 4);
    puzzle |= static_cast<uint64_t>(value_j) << ((15 - i) * 4);
    return puzzle;
}

int getPosition(Puzzle p){
    for(int i = 0; i < 16; i++){
        uint8_t value = (p >> ((15 - i) * 4)) & 0xF;
        if(value == 0){
            return i;
        }
    }
    return -1;
}

std::vector<Puzzle> getPossibleMoves(Puzzle p){
    std::vector<Puzzle> moves;

    int position = getPosition(p);
    int row = position / 4;
    int col = position % 4;

    if(col != 0)
        moves.push_back(swap(p, position, position - 1));
    if(col != 3)
        moves.push_back(swap(p, position, position + 1));
    if(row != 0)
        moves.push_back(swap(p, position, position - 4));
    if(row != 3)
        moves.push_back(swap(p, position, position + 4));

    return moves;
}

char getMove(Puzzle p1, Puzzle p2){
    int pos1 = getPosition(p1);
    int pos2 = getPosition(p2);
    
    switch(pos1 - pos2){
        case -1:
            return 'L';
        case 1:
            return 'R';
        case -4:
            return 'U';
        case 4:
            return 'D';
        default:
            return 'X';
    }
}

void printHistory(std::map<Puzzle,Puzzle>& h, Puzzle i){
    std::cout << "History : ";

    std::vector<Puzzle> history;
    Puzzle previous;

    while((previous = h[i]) != 0 ){
        history.emplace(history.begin(), i);
        i = previous;
    }

    for(auto i = history.begin(); i != history.end() - 1; i++){
        std::cout << getMove(*i, *(i + 1));
    }
    std::cout << "\n";
}

void solve(Puzzle puzzle, std::function<int(Puzzle)> heuristic){
    std::priority_queue<std::pair<int, Puzzle>, std::vector<std::pair<int, Puzzle>>, std::greater<std::pair<int, Puzzle>>> queue;
    std::set<Puzzle> visited;
    std::map<Puzzle,Puzzle> history;

    queue.push(std::make_pair(heuristic(puzzle), puzzle));

    while(!queue.empty()){
        auto [d, p] = queue.top();
        queue.pop();
        visited.insert(p);

        int cost = d - heuristic(p);

        if(p == solved){
            std::cout << "\nSolved in " << std::dec << cost << " moves,\n";
            std::cout << "visited " << visited.size() << " nodes.\n";
            printHistory(history,p);
            return;
        }

        std::vector<Puzzle> moves = getPossibleMoves(p);
        for(Puzzle move : moves){
            if(visited.find(move) == visited.end()){
                history[move] = p;
                queue.push(std::make_pair(cost + 1 + heuristic(move), move));
            }
        }
    }
}

int randomMove(int position){
    int row = position / 4;
    int col = position % 4;

    std::vector<int> moves;
    if(col != 0)
        moves.push_back(position - 1);
    if(col != 3)
        moves.push_back(position + 1);
    if(row != 0)
        moves.push_back(position - 4);
    if(row != 3)
        moves.push_back(position + 4);
    
    return moves[std::rand() % moves.size()];
}

Puzzle createNMovePuzzle(int n){
    std::vector<int> puzzle(16, 0);
    std::iota(puzzle.begin(), puzzle.end() - 1, 1);

    int position = 15;
    for(int i = 0; i < n; i++){
        int newPosition = randomMove(position);
        std::swap(puzzle[position], puzzle[newPosition]);
        position = newPosition;
    }

    Puzzle puzzle64 = 0;
    for(int i = 0; i < puzzle.size(); i++){
        puzzle64 |= static_cast<uint64_t>(puzzle[i]) << ((15 - i) * 4);
    }
    return puzzle64;
}

int main(int argc, char** argv) {
    srand(time(NULL));
        Puzzle puzzle = createPuzzle();
        std::cout << "\nLinear conflict:\n";
        solve(puzzle, [](Puzzle p){
            return manhattanDistance(p) + linearConflict(p);
        }); 
        std::cout << "\nManhattah:\n";
        solve(puzzle, [](Puzzle p){
            return manhattanDistance(p);
        });
    // Puzzle puzzle = createPuzzle();
    // // Puzzle puzzle = createNMovePuzzle(100);
    // printPuzzle(puzzle);

    // // solve(puzzle, linearConflict);
    // // solve(
    // //     puzzle,
    // //     hammingDistance
    // // );
    // solve(puzzle, [](Puzzle p){
    //     return manhattanDistance(p) + linearConflict(p);
    // });
    // solve(puzzle, manhattanDistance);

    return 0;
}

Puzzle createPuzzle(){
    std::vector<int> puzzle(16, 0);
    std::iota(puzzle.begin(), puzzle.end() - 1, 1);

    do std::shuffle(puzzle.begin(), puzzle.end() - 1, std::mt19937{std::random_device{}()});
    while(!isSolvable(puzzle));

    Puzzle puzzle64 = 0;
    for(int i = 0; i < puzzle.size(); i++){
        puzzle64 |= static_cast<uint64_t>(puzzle[i]) << ((15 - i) * 4);
    }
    return puzzle64;
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

constexpr int getValue(Puzzle puzzle, int i){
    return (puzzle >> ((15 - i) * 4)) & 0xF;
}

int linearConflict(Puzzle puzzle){
    int conflicts = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int value = getValue(puzzle, i*4+j);
            if(value == 0){
                continue;
            }
            int rowGoal = (value - 1) / 4;
            int colGoal = (value - 1) % 4;
            if(i == rowGoal){
                for(int k = j + 1; k < 4; k++){
                    int v = getValue(puzzle, i*4+k);
                    if(v != 0 && (v - 1) / 4 == i && (v - 1) % 4 < colGoal){
                        conflicts+=2;
                    }
                }
            }
            if(j == colGoal){
                for(int k = i + 1; k < 4; k++){
                    int v = getValue(puzzle, k*4+j);
                    if(v != 0 && (v - 1) % 4 == j && (v - 1) / 4 < rowGoal){
                        conflicts+=2;
                    }
                }
            }
        }
    }
    return conflicts;
}

int manhattanDistance(Puzzle puzzle){
    int distance = 0;
    for(int i = 0; i < 16; i++){
        uint8_t value = (puzzle >> ((15 - i) * 4)) & 0xF;
        if(value == 0){
            continue;
        }
        int row = i / 4;
        int col = i % 4;
        int rowGoal = (value - 1) / 4;
        int colGoal = (value - 1) % 4;
        distance += std::abs(row - rowGoal) + std::abs(col - colGoal);
    }
    return distance;
}

int hammingDistance(Puzzle puzzle){
    int distance = 0;
    for(int i = 0; i < 16; i++){
        uint8_t value = (puzzle >> ((15 - i) * 4)) & 0xF;
        if(value == 0){
            continue;
        }
        if(value != i + 1){
            distance++;
        }
    }
    return distance;
}

void printPuzzle(Puzzle puzzle){
    for(int i = 0; i < 16; i++){
        uint8_t value = (puzzle >> ((15 - i) * 4)) & 0xF;
        if(value == 0){
            std::cout << "0 ";
        }else{
            std::cout << std::hex << (int)value << " ";
        }
        if(i % 4 == 3){
            std::cout << std::endl;
        }
    }
}