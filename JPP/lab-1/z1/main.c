#include "lib.h"

#include <stdio.h>

int main()
{
    Pair result = solve(17, 0, 17);

    printf("%d %d\n", result.x, result.y);
}