#include <stdio.h>
#include <math.h>
#include "integrationFunctions.h"

int main()
{

	double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

	double trap = trapazoid();

	double error = fabs(pi - trap);

	printf("%f \n", error);

	return 0;

}
