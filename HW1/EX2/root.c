#include <stdio.h>
#include <time.h>
#include <math.h>
#include "rootFunctions.h"

int main()
{
    float x, i;
    double error;

    //Taking in input value for square root functions
    printf("Please enter a value to estimate the square root of, preferably close to 1, between 0 and 2: \n");
    scanf("%f", &x);

    //Calculating the square root using the sqrt() function in the math.h library for reference
	float square = sqrt(x);
	printf("Using math.h library: %f \n" , square);

    //Determine the time that this function takes
	clock_t tic = clock();
    for(i=0; i < 1000000; i++)
    {
        square = sqrt(x);
    }
	clock_t toc = clock();
	printf("Elapsed: %f \n", (double)(toc - tic)/ CLOCKS_PER_SEC);

    //Calculating the square root using the Taylor series
	float taylor = Sq_Tlr(x);
	printf("Using Taylor Series: %f \n" , taylor);

    //Calculating the error
    error = fabs(square - taylor);
	printf("The error in this value is: %f \n" , error);

    //Determine the time that this function takes
	tic = clock();
    for(i=0; i < 1000000; i++)
    {
        taylor = Sq_Tlr(x);
    }
	toc = clock();
	printf("Elapsed time: %f \n", (double)(toc - tic)/ CLOCKS_PER_SEC);

	float newton = Sq_Nwt(x);
	printf("Using Newton's Method: %f \n" , newton);

	tic = clock();
    for(i=0; i < 1000000; i++)
    {
        newton = Sq_Nwt(x);
    }
	toc = clock();
	printf("Elapsed time: %f \n", (double)(toc - tic)/ CLOCKS_PER_SEC);

    //Calculating the error
    error = fabs(square - newton);
	printf("The error in this value is: %f \n" , error);

	float fraction = Sq_Frc(x);
	printf("Using Continued Fractions: %f \n" , fraction);

	tic = clock();

    for(i=0; i < 1000000; i++)
    {
        fraction = Sq_Frc(x);
    }

	toc = clock();

	printf("Elapsed time: %f \n", (double)(toc - tic)/ CLOCKS_PER_SEC);

    //Calculating the error
    error = fabs(square - fraction);
	printf("The error in this value is: %f \n" , error);

}
//Calculate error between actual value and estimated value
