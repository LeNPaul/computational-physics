#include <random>
#include <chrono>
#include <iostream>
#include "integrators.h"

using namespace std;
using namespace chrono;

int main()
{
	//Finding the interval of integration
	double a,b, dx;

	cout << "Enter the lower bound you wish to intergrate:" <<endl;

	cin >> a;

	cout << "Enter the upper bound you wish to intergrate:" <<endl;

	cin >> b;

	//Number of intervals
	int N;

	cout<< "Enter the number of interval points you wish to use:" <<endl;

	cin >> N;

	//Calling the Monte Carlo integration functions
	cout<< simpleMonte(a, b, N) <<endl;

}
