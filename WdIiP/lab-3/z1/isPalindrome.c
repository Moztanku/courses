#include<string.h>
#include<stdio.h>

int isPalindrome(char s[]){
    int strLength = strlen(s);
    for(int i=0; i<strLength; i++){
        if(s[i]!=s[strLength-i-1]){
            return 0;
        }
    }
    return 1;
};
