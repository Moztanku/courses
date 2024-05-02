#include<stdio.h>

int main(){
    printf("Write a natural number: ");
    int n;
    scanf("%i",&n);
    char row[(2*n)+1];
    for(int i=0; i<2*n; i++)
        row[i]='*';
    row[(2*n)]='\0';
    for(int i=0; i<n; i++)
        printf("%s\n",row);
    return 0;
}
