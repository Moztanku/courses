#include<stdio.h>

int main(){
    int n = 0;
    printf("Podaj jedna liczbe naturalna: ");
    scanf("%i",&n);
    double x = 0;
    double sum = 0;
    for(int i=0; i<n; i++){
        printf("    Podaj liczbe rzeczywista: ");
        scanf("%lf",&x);
        sum+=x;
    };
    printf("Srednia arytmetyczna podanych liczb to: %lf\n",sum/n);
}
