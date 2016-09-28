#include <random>
#include <chrono>
#include <iostream>
#include "integrators.h"

using namespace std;
using namespace chrono;

int main()
{

	//Pseudocode:
	//	Take in lower and upper bounds and calculate interval
	//	Take in number of intervals
	//	Calculate value of function at every interval
	//	Add all of these values together
	//	Multiply by interval length
	//	Divide by number of intervals

	//Interval of integration
	double a,b;

	cout << "Enter the lower bound you wish to intergrate: \n" <<endl;

	//Number of intervals
	int N;

	cin >> test;

	cout<< test <<endl;



	typedef high_resolution_clock myclock;

	myclock::time_point beginning = myclock::now();

	// obtain a seed from the timer

	myclock::duration d = myclock::now() - beginning;

	unsigned seed = d.count();

	// define the generator

	mt19937 generator(seed);

	uniform_real_distribution<double> distribution(0,1.0);

	for (int i=1;i<=10;i++){
		cout<< i << " " << distribution(generator) <<endl;
	}

	cout<< function(1) <<endl;

}
