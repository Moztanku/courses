#include<stdio.h>
#include"agents.h"

int main(void){
    struct agent Bob = newagent(0,0);
    struct agent Alice = newagent(3,3);
    north(&Bob);
    south(&Alice); // 3 2
    west(&Alice); // 2 2
    north(&Bob);
    east(&Bob);
    south(&Alice); // 2 1
    printf("odleglosc = %lf\n",distance(Bob,Alice));
}
