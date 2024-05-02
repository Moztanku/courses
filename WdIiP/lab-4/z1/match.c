#include<stdio.h>
#include<string.h>

#define true 1
#define false 0

int match(char* wz,char* la);

int main(int argc, char** argv){
    struct Pair{
        char* w;
        char* l;
    };
    struct Pair pair[5];
    pair[0].w = "a*b*a";
    pair[0].l = "ababababababababababababa";
    pair[1].w = "a*b*a";
    pair[1].l = "ababababababababababababab";
    pair[2].w = "*";
    pair[2].l = "a";
    pair[3].w = "a*b*b*c";
    pair[3].l = "aabada bec";
    pair[4].w = "a???";
    pair[4].l = "adam";
    
    for(int i=0; i<5; i++){
        char* str = match(pair[i].w,pair[i].l)?"pasuje do wzoru":"nie pasuje do wzoru";
        printf("\"%s\" %s \"%s\".\n",pair[i].l,str,pair[i].w);
    }
  
    for(int i=1; i<=(argc/2); i++){
        printf("match(\"%s\",\"%s\") = %s\n",argv[i*2-1],argv[i*2],match(argv[i*2-1],argv[i*2])?"True":"False");
    }
    return 0;
};

int match(char* wz,char* la){
    if(wz[0]=='\0' && la[0]=='\0')
        return true;
    if(wz[0]=='*'){
        for(int i=1; la[i-1]!='\0'; i++){
            if(match(wz+1,la+i))
                return true;
        }
    }
    if(wz[0]=='?' || wz[0]==la[0])
        return match(wz+1,la+1);
    else
        return false;
};
