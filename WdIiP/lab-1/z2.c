#include<stdio.h>
#include<math.h>

int main(){
    double a,b,c;
    printf("Write 3 real numbers: ");
    scanf("%lf %lf %lf",&a,&b,&c);
    printf("%lf*x^2 + %lf*x + %lf = 0\n",a,b,c);
    double delta = (b*b)-(4*a*c);
    if(a!=0){
        if(delta<0)
            printf("X doesn't exist.\n");
        else if(delta==0)
            printf("x = %lf.\n",-b/2*a);
        else{
            double sqrtDelta = sqrt(delta);
            double x1=((-b)+sqrtDelta)/(2*a);
            double x2=((-b)-sqrtDelta)/(2*a);
            printf("x = %lf, or x = %lf.\n",x1,x2);
        }
    }
    else{
        printf("x = %lf.\n",-c/b);
    }
    return 0;
}
