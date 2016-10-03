#include <random>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

/*
https://breakingmuscle.com/olympic-weightlifting/the-free-4-week-stronger-than-ever-weightlifting-program
https://www.t-nation.com/training/olympic-lifting-made-simple
http://www.alltheheavylifting.com/five-online-olympic-weightlifting-beginner-programs/

http://farside.ph.utexas.edu/teaching/329/lectures/node110.html
*/

int main()
{

	//Initializing important variables
	int L = 8; //Latice size
	int lattice[L][L]; //Storing the lattice

	typedef high_resolution_clock myclock;

	myclock::time_point beginning = myclock::now();

	// obtain a seed from the timer

	myclock::duration d = myclock::now() - beginning;

	unsigned seed = d.count();

	// define the generator

	mt19937 generator(seed);

	uniform_real_distribution<double> distribution(0,1.0);

	//Initializing the lattice

	int i,j;
	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){
			if(distribution(generator) < 0.5){
				lattice[i][j] = 1;
				printf("1 ");
			}
			else
			{
				lattice[i][j] = 0;
				printf("0 ");
			}
		}
		printf("\n");
	}

	//Determining the energy of the system
	
	double totalEnergy = 0; //Setting the energy of the system


	//How to increment so that I don't double count
	for(i=0; i < L; i+=2){
		for(j=0; j < L; j+=2){
			printf("%i", lattice[i][j]);
		}
		printf("\n");
	}

}
