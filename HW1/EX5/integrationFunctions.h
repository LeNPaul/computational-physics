#ifndef INTEGRATIONFUNCTIONS_H_INCLUDED
#define INTEGRATIONFUNCTIONS_H_INCLUDED

#include <stdio.h>

double myfunc(double x)
{
	double r;
	r = 4.0 / (1 + x * x);
	return r;
}

double trapazoid()
{
	int i;
	int n = 64;
	float xl = 0;
	float xh = 1;

	//Find interval size
	float dx = (xh - xl) / n;

    //Calculate end points
    float integral = dx * (myfunc(xh) + myfunc(xl)) / 2;

	for(i = 1; i <= n - 1; ++i){
        xl += dx;
		integral += dx * myfunc(xl);
	}

	printf("%f \n", integral);

	return integral;
}

double romberg()
{
	double h = 0.5;
	
}

#endif // INTEGRATIONFUNCTIONS_H_INCLUDED
