#include <stdio.h>

double myfunc(double x)
{
	double r;
	r = 4.0 / (1 + x * x);
	return r;
}

int main()
{

	int i;
	int n = 20;
	float f1, f2, dx, xl, xh, integral;

	//Find interval size
	dx = (xh - xl) / n;
	
	float trapArea = (f1 + f2) * dx / 2;

	for(i = 0; i <= n; ++i){
		integral += myfunc(i);
	}
	
	printf("%f", integral);

	return integral;

} 
