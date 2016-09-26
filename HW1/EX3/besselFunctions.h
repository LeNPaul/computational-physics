#ifndef BESSELFUNCTIONS_H_INCLUDED
#define BESSELFUNCTIONS_H_INCLUDED

float ascendingBessel()
{
    float x = 0.5;
    float n = 20;

    float j0 = 0.938469807240813;
    float j1 = 0.2422684577;
    printf("j 0 = %f \n",j0);
    printf("j 1 = %f \n",j1);

    float j;

    int i, temp;

    for(i = 2; i <= 20; ++i){
        j = 2 * n * j1/ x - j0;

        j0 = j1;
        j1 = j;

        printf("j %i = %f \n",i ,j);
    }

    return 0;
}

float descendingBessel()
{
    float x = 0.5;
    float n = 5;
    int N = 5;
    int i, temp;

    float j5 = 0;
    float j4 = 1;

    float j3 = 2*n*j4/x - j5;

    printf("The descending Bessel %f", j3);


    for(i=N; i > -1; --i)
    {
        printf("%i \n", i);
    }

    return 0;
}

#endif // BESSELFUNCTIONS_H_INCLUDED
