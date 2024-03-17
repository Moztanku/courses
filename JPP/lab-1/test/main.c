#include <stdio.h>

extern void adainit     (void);
extern void adafinal    (void);

#include "wrapper.h"

int main()
{

    adainit();
    printf("%d\n", test());
    adafinal();
    return 0;
}