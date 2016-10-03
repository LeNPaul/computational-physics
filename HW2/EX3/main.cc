#include <random>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

/*
https://breakingmuscle.com/olympic-weightlifting/the-free-4-week-stronger-than-ever-weightlifting-program
https://www.t-nation.com/training/olympic-lifting-made-simple
http://www.alltheheavylifting.com/five-online-olympic-weightlifting-beginner-programs/
*/

int main()
{

	//Initializing important variables
	int L = 10; //Latice size
	int lattice[L][L]; //Storing the lattice

	typedef high_resolution_clock myclock;

	myclock::time_point beginning = myclock::now();

	// obtain a seed from the timer

	myclock::duration d = myclock::now() - beginning;

	unsigned seed = d.count();

	// define the generator

	mt19937 generator(seed);

	uniform_real_distribution<double> distribution(0,1.0);

	double coinToss = distribution(generator);

	int i,j;
	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){
			if(distribution(generator) < 0.5){
				lattice[i][j] = 1;
				printf("Less than \n");
			}
			else
			{
				lattice[i][j] = 0;
				printf("Greater than \n");
			}
		}
	}

}
