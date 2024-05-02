#include<math.h>
#include<stdio.h>
#include"funs.h"
double rozwiazanie(double a,double b,double eps){
    double c=(a+b)/2;
    while(fabs(f(c))>eps){
        c=(a+b)/2;
        if(f(a)*f(c)<0){
            b=c;
        }
        else{
            a=c;
        }
    };
    return c;
};
