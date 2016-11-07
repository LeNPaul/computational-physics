#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double h = 1;
double m = 1;

double V(double x)
{
	//This is the potential for 1.3
	if(x < 5 && x > -5)
	{
		return x * x / 5 - 14;
	}
	else
	{
		return 0;
	}
}

double E;

double kappa(double x)
{
	return sqrt(2 * m * (E - V(x)) / (h * h));
}



double initial_phi(double c_phi, double p_phi)
{
	return 0;
}

double left_phi()
{
	return 0;
}

double right_phi()
{
	return 0;
}
