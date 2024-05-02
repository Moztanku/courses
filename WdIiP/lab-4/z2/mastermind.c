#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define UINT_MAX 4294967295

void setCode();
int* guess(int x[4]);
void decoder();

static int code[4];
int main(){
    setCode();
    decoder();
    //int* res;
    //int t1[2]={0,0};
    //int t2[2]={0,0};
    //int a1[4]={1,1,0,0};
    //int a2[4]={1,2,3,4};
    //res = guess(a1); t1[0]=res[0]; t1[1]=res[1];
    //res = guess(a2); t2[0]=res[0]; t2[1]=res[1];
    //printf("%i %i %i %i\n", t1[0],t1[1],t2[0],t2[1]);
    printf("%i %i %i %i\n", code[0],code[1],code[2],code[3]);
    //int g[4] = {1,2,3,4};
    //int* temp = guess(g);
    //printf("%i - red, %i white\n",temp[0],temp[1]);
    return 0;
}

int* guess(int x[4]){
    int res[2]={0,0};
    int t1[4] = {1,1,1,1};
    int t2[4] = {1,1,1,1};
    for(int i=0; i<4; i++)
        if(x[i]==code[i]){
            t1[i]=0; t2[i]=0;
            res[0]++;
        }
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            if(t1[i]&&t2[j]&&i!=j)
                if(x[i]==code[j]){
                    res[1]++;
                    t1[i]=0;
                    t2[j]=0;
            }
            //printf("I=%i J=%i : X[I]=%i - CODE[J]=%i : B=%i\n",i,j,x[i],code[j],res[1]);
            //printf("TAB1={%i,%i,%i,%i}, TAB2={%i,%i,%i,%i}\n",t1[0],t1[1],t1[2],t1[3],t2[0],t2[1],t2[2],t2[3]);
        }
    return res;
};
void setCode(){
    time_t tt;
    srand(time(&tt));
    for(int i=0;i<4;i++)
        code[i]=rand()%6;
    return;
};

void decoder(){
    unsigned char tab[1296];
    for(int i=0; i<1296; i++){
        tab[i]='1';
    };
    int* res; int t1[2]; int t2[2];
    int t[4] = {0,0,1,1};
    int a[4] = {0,0,0,0};
    int s1=0; int s2=0; int s3=0;
    int x=0;
    res = guess(t); t1[0]=res[0]; t1[1]=res[1];
    while(t1[0]!=4){
        printf("R-%i W-%i\nt={%i,%i,%i,%i}\n",res[0],res[1],t[0],t[1],t[2],t[3]);
        getchar();
        for(int i=0; i<1296; i++){
            a[0]=(i/216)%6;
            a[1]=(i/36)%6;
            a[2]=(i/6)%6;
            a[3]=(i)%6;
            res = guess(a); t2[0]=res[0]; t2[1]=res[1];
            if(t2[0]==t1[0] && t2[1]==t1[1])
                tab[i]=0;
        }
        if(x<5)
        for(int i=0; i<1296; i++){
            if(1){
                t[0]=(i/216)%6;
                t[1]=(i/36)%6;
                t[2]=(i/6)%6;
                t[3]=(i)%6;
                res = guess(t); t1[0]=res[0]; t1[1]=res[1];
                for(int j=0; j<1296; j++){
                    if(tab[j]){
                        a[0]=(j/216)%6;
                        a[1]=(j/36)%6;
                        a[2]=(j/6)%6;
                        a[3]=(j)%6;
                        res = guess(a); t2[0]=res[0]; t2[1]=res[1];
                        if(t2[0]==t1[0] && t2[1]==t1[1]){
                            s1++;
                        }
                    }
                }
            }
            if(s1>s2){
                s2=s1;
                s3=i;
                //printf("s1: %i , s2: %i , s3: %i , i: %i\n",s1,s2,s3,i);
                    }
            s1=0;
        }
        else{
            for(int i=0; i<1296;i++)
                if(tab[i]){
                s3=i;
                }
        }
        t[0]=(s3/216)%6;
        t[1]=(s3/36)%6;
        t[2]=(s3/6)%6;
        t[3]=(s3)%6;
        res=guess(t);
        t1[0]=res[0]; t1[1]=res[1];
        s1=0; s2=0; s3=0; x++;
    };
    printf("R-%i W-%i\nt={%i,%i,%i,%i}\n",res[0],res[1],t[0],t[1],t[2],t[3]);
};
