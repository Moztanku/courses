#include"agents.h"
#include<math.h>
double distance(struct agent a1,struct agent a2){
    double dx = a1.x-a2.x;
    double dy = a1.y-a2.y;
    return sqrt(dx*dx+dy*dy);
};
