#ifndef BESSELFUNCTIONS_H_INCLUDED
#define BESSELFUNCTIONS_H_INCLUDED

#include <stdio.h>

double ascendingBessel()
{
    double x = 0.5;

    double j0 = 0.938469807240813;
    double j1 = 0.2422684577;

    printf("j 0 = %f \n",j0);
    printf("j 1 = %f \n",j1);

    double j;

    int n, temp;

    for(n = 2; n <= 20; ++n){
        j = 2 * n * j1/ x - j0;

        j0 = j1;
        j1 = j;

        printf("j %i = %f \n",n ,j);
    }

    return 0;
}

double descendingBessel()
{
	double x = 0.5;
	int n = 3;
	int N = 3;

	double j5 = 0;
	double j4 = 1;

	printf("j 5 = %f \n", j5);
	printf("j 4 = %f \n", j4);

	double j;

	double values[n+2];
	values[0] = j5;
	values[1] = j4;

	for(n; n > -1; --n){

		j = 2*(n+1)*j4/x - j5;

		values[n] = j;

		j5 = j4;
		j4 = j;

		printf("j %i = %f \n",n, j);
	}
	
	//Normalize
	double normalize = values[0];
	int i=2;
	
	//Finding normalization constant
	for(i; i < N + 2; i += 2){
		normalize += 2*values[i];
	}

	//Normalizing values
	i = 0;
	for(i=0; i < N + 3; ++i){
		values[i] = values[i] / normalize;
		printf("j %i = %f \n",i, values[i]);
	}
	
}

#endif // BESSELFUNCTIONS_H_INCLUDED
