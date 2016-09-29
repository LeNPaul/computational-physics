#include <iostream>
#include "integrators.h"

using namespace std;

int main()
{
	//Finding the interval of integration
	double a,b;

	cout << "Enter the lower bound you wish to intergrate:" <<endl;

	cin >> a;

	cout << "Enter the upper bound you wish to intergrate:" <<endl;

	cin >> b;

	//Number of intervals
	int N;

	cout<< "Enter the number of interval points you wish to use:" <<endl;

	cin >> N;

	//Calling the Monte Carlo integration functions
	cout<< "The integral using simple Monte Carlo integration is " << simpleMonte(a, b, N) <<endl;

	cout<< "The integral using sample Monte Carlo integration is " << sampleMonte(a, b, N) <<endl;

	return 0;

}
