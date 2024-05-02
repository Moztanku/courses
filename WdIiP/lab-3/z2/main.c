#include<stdio.h>
#include"funs.h"

int main(){
    double x = rozwiazanie(2.0,4.0,0.1);
    printf("Rozwiazanie dla (2.0,4.0,0.1) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.01);
    printf("Rozwiazanie dla (2.0,4.0,0.01) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.001);
    printf("Rozwiazanie dla (2.0,4.0,0.001) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.0001);
    printf("Rozwiazanie dla (2.0,4.0,0.0001) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.00001);
    printf("Rozwiazanie dla (2.0,4.0,0.00001) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.000001);
    printf("Rozwiazanie dla (2.0,4.0,0.000001) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.0000001);
    printf("Rozwiazanie dla (2.0,4.0,0.0000001) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.00000001);
    printf("Rozwiazanie dla (2.0,4.0,0.00000001) = %lf \n",x);
    x = rozwiazanie(2.0,4.0,0.000000001);
    printf("Rozwiazanie dla (2.0,4.0,0.000000001) = %lf \n",x);
    return 0;
};
