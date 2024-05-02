#include<stdio.h>

int main(){
    int zl = 0; int gr = 0;
    printf("Podaj liczbe zloty: ");
    scanf("%i",&zl);
    printf("Podaj liczbe groszy: ");
    scanf("%i",&gr);
    int sum = zl*100+gr;
    printf(" Banknoty: \n");
    int temp = 0;
    for(int i=10000; i>99; i=i/10){
        if(i==100) printf(" Monety: \n");
        temp=sum/(i*5);
        if(temp!=0){
            printf("    %i x %i zl\n",temp,i/20);
            sum%=(i*5);
        };
        temp=sum/(i*2);
        if(temp!=0){
            printf("    %i x %i zl\n",temp,i/50);
            sum%=(i*2);
        }
        temp=sum/i;
        if(temp!=0){
            printf("    %i x %i zl\n",temp,i/100);
            sum%=i;
        }
    };
    for(int i=10; i>0; i=i/10){

        temp=sum/(i*5);
        if(temp!=0){
            printf("    %i x %i gr\n",temp,i*5);
            sum%=(i*5);
        };
        temp=sum/(i*2);
        if(temp!=0){
            printf("    %i x %i gr\n",temp,i*2);
            sum%=(i*2);
        };
        temp=sum/(i);
        if(temp!=0){
            printf("    %i x %i gr\n",temp,i);
            sum%=(i);
        };
    }
    // 50000,20000,10000,5000,2000,1000
    // 500,200,100,50,20,10,5,2,1
    // 
}
