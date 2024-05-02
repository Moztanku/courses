#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[]){
    char* word = argv[argc-1];
    int wordLength = strlen(word);
    for(int i=wordLength;i>0;i--){
        for(int j=wordLength-i;j>0;j--)
            printf(" ");
        for(int j=0; j<i; j++) 
            printf("%c ",word[j]);
        printf("\n");
    }
    return 0;
}
