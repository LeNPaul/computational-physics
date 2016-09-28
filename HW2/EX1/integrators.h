#ifndef INTEGRATORS_H_INCLUDED
#define INTEGRATORS_H_INCLUDED

#include <random>
#include <chrono>
#include <iostream>
#include "integrators.h"

using namespace std;
using namespace chrono;

double function(double x)
{
	return exp (-x*x);
}

double simpleMonte(double a, double b, int N)
{
	//Pseudocode:
	//	Take in lower and upper bounds and calculate the integration interval size
	//	Take in number of intervals
	//	Calculate value of function at random values within interval
	//	Add all of these values together
	//	Multiply by interval length
	//	Divide by number of intervals

	//Generating random numbers

	typedef high_resolution_clock myclock;

	myclock::time_point beginning = myclock::now();

	//Obtain a seed from the timer

	myclock::duration d = myclock::now() - beginning;

	unsigned seed = d.count();

	//Define the generator

	mt19937 generator(seed);

	uniform_real_distribution<double> distribution(a,b);

	//Initialize the sum of the function evaluated at random points betweent he given interval
	double sum = 0;

	//Evaluate the function at random points between the given interval points and add them together
	for (int i=1;i<=N;i++){
		//cout<< i << " " << function(distribution(generator)) <<endl;
		sum += function(distribution(generator));
	}

	return ((b - a) / (N-1))*sum;

}

/*
	Implementing the sample Monte Carlo Method
*/

double g(double x)
{
	return (exp(1 - exp(-x))) / (exp(1) - 1);
}

double g_inverse(double u)
{
	return - 1 (u - log10 * (exp(1) - 1) / (exp(1)));
}

double sampleMonte(double a, double b, int N)
{
	//Generating random numbers

	typedef high_resolution_clock myclock;

	myclock::time_point beginning = myclock::now();

	//Obtain a seed from the timer

	myclock::duration d = myclock::now() - beginning;

	unsigned seed = d.count();

	//Define the generator

	mt19937 generator(seed);

	uniform_real_distribution<double> distribution(g(a),g(b));

	//Initialize the sum of the function evaluated at random points betweent he given interval
	double sum = 0;

	//Evaluate the function at random points between the given interval points and add them together
	for (int i=1;i<=N;i++){
		//cout<< i << " " << function(distribution(generator)) <<endl;
		sum += function(g_inverse(distribution(generator)));
	}

	return ((g(b) - g(a)) / (N-1))*sum;
}

#endif // INTEGRATORS_H_INCLUDED
