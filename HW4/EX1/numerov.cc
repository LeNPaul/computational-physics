#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

//Define some constants as global variables
double hbar = 1;
double m = 1;
double E = 1.0;

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

double kappa(double x)
{
	//Since kappa always appears squared, we can just return the unsquared value
	return 2 * m * (E - V(x)) / (hbar * hbar);
}

void right_phi(vector<double> & phi_r, double h)
{
	//This function generates the integration from right to left
	
	int N = phi_r.size();	

	//We are going from right to left, so start from N - 1 because vector index starts from 0
	//To make this easier, just start from 0 and go to N, since we can just reverse the indices later
	//Set the first value to 0 and the second value to 1E-10
	phi_r[0] = 0;
	phi_r[1] = 1 * pow(10,-10);

	for(int i = 2; i <= N; ++i)
	{
		phi_r[i] = (2 * (1 - 5 * h * h * kappa(i) / 12) * phi_r[i - 1] - (1 + h * h * kappa(i + h) / 12) * phi_r[i - 2] ) / (1 + h * h * kappa(i - h) / 12);
	}

}

void left_phi(vector<double> & phi_l, double h)
{
	//This function generates the integration from left to right
	
	int N = phi_l.size();

	//We are going from left to right, so star from 0
	//Set the first value to 0 and the second value to 1E-10
	phi_l[0] = 0;
	phi_l[1] = 1 * pow(10,-10);

	for(int i = 2; i <= N; ++i)
	{
		phi_l[i] = ( 2 * (1 - 5 * h * h * kappa(i) / 12) * phi_l[i - 1] - ( 1 + h * h * kappa(i - h) / 12 ) * phi_l[i - 2] ) / ( 1 + h * h * kappa(i + h) / 12 );
	}

}
