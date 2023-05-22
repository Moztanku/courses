#include <stdio.h>
#include <unistd.h>
#include <math.h>

// void print(int number){
//     int length = log10(number) + 1;
//     for (int i = 0; i < length; i++){
//         int ld = number / pow(10, length - i - 1);
//         ld %= 10;
//         ld += '0';
//         write(STDOUT_FILENO, &ld, 1);
//     }
// }

int main(){
    int number = 100;
    int a = number;
    number /= 10;
    return 0;
}