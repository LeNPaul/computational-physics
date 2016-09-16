#include <stdio.h>

int main()
{
    float x = 0.5;
    float n = 20;

    float j0 = 0.938469807240813;
    float j1 = 0.2422684577;
    float j;

    int i, temp;

    for(i = 0; i <= 20; ++i){
        j = 2 * n * j1/ x - j0;

        temp = j1;
        j1 = j;
        j0 = temp;
    }

    printf("%f \n", j);

    return j;
}
