#include <stdio.h>
#include "funs.h"

int main(void){
    char* str1[4];
    str1[0] = "kajak";
    str1[1] = "ala ma kota";
    str1[2] = "c";
    str1[3] = "palindrom";
    
    for(int i=0; i<4; i++){
        if(isPalindrome(str1[i])==1){
            printf("\"%s\" jest palindromem.\n",str1[i]);
        }
        else{
            printf("\"%s\" nie jest palindromem.\n",str1[i]);
        }
    };
    return 0;
};
