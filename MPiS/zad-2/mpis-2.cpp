#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

void experiment(int n, std::mt19937* rng, std::fstream* file);  //  Function for running experiment

int main(int argc, char const *argv[])
{
    std::random_device seed;   // Seed from hardware
    std::mt19937 rng(seed());   // Mersenne Twister 

    std::fstream file{"data.csv", file.out};    //  Open file
    if(!file.is_open()){    //  Check if file is open
        std::cerr << "Couldn't open file";  //  Print error
        return -1;  //  Exit program
    }

    int N = 100;    //  Number of experiments
    int K = 50;    //  Number of experiments for each N
    for(int n=1000; n <= N*1000; n+=1000){  //  For each N
        std::cout << "Experiments for N = " << n << "\n";   //  Print current N
        for(int k = 0; k < K; k++){ //  For each experiment
            experiment(n,&rng,&file);   //  Run experiment
        }   //  End of experiments for current N
    }

    return 0;   
}

void experiment(int n, std::mt19937* rng, std::fstream* file){ 
    int Bn = 0; //  moment pierwszej kolizji
    int Un = 0; //  liczba pustych urn po wrzuceniu n kul
    int Ln = 0; //  maksymalna liczba kul w urnie po wrzuceniu n kul 
    int Cn = 0; //  minimalna liczba rzutów, po której w ka ̇zdej z urn jest co najmniej jedna kula
    int Dn = 0; //  minimalna liczba rzutów, po której w ka ̇zdej z urn s  ̨a co najmniej dwie kule

    int BoxesWithOne = 0;   //  Number of boxes with one ball
    int BoxesWithTwo = 0;   //  Number of boxes with two balls

    std::vector<int> urn(n,0);  //  Urn with n boxes and 0 balls in each box
    std::uniform_int_distribution<int> dist(0,n-1); //  Uniform distribution of integers from 0 to n-1

    int k = 0;
    while(!Bn || !Un || !Ln || !Cn || !Dn){     // While we don't have all the data
        k++;    //  Increment number of throws
        int randomBox = dist(*rng); //  Get random box
        urn[randomBox]++;   //  Add ball to random boxS

        if(urn[randomBox] == 1){    //  If box has one ball
            BoxesWithOne++; //  Increment number of boxes with one ball
        } else if(urn[randomBox] == 2){ //  If box has two balls
            BoxesWithTwo++; //  Increment number of boxes with two balls

            if(Bn == 0){    //  If we don't have first collision
                Bn = k; //  Set first collision
            }
        }
        if(k == n){ //  If we have thrown n balls
            Un = n-BoxesWithOne-BoxesWithTwo;   //  Number of empty boxes is n - number of boxes with one ball - number of boxes with two balls
            Ln = *std::max_element(urn.begin(),urn.end());  // Max number of balls in a box
        }
        if(Cn == 0 && BoxesWithOne == n){   // If we have one ball in each box
            Cn = k;
        }
        if(Dn == 0 && BoxesWithTwo == n){   // If we have two balls in each box
            Dn = k;
        }
    }

    std::stringstream str;
    str << n << ";" << Bn << ";" << Un << ";" << Ln << ";" << Cn << ";" << Dn << ";" << Dn-Cn << "\n";  //  Create string with data
    *file << str.str(); //  Write data to file
};