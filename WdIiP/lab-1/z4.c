#include<stdio.h>

int main(){
    int n=0;
    printf("Write a one natural number: ");
    scanf("%i",&n);
    int rowLength = 1+2*(n-1);
    for(int i=0; i<n; i++){
        char str[rowLength+1];
        for(int j=0; j<=rowLength; j++)
            str[j]=' ';
        str[rowLength+1]='\0';
        for(int j=n-i;j<=n+i;j++){
            str[j]='*';
        };
        printf("%s\n",str);
    }
    return 0;
}
