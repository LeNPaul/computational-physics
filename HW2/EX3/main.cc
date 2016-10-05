#include <random>
#include <chrono>
#include <iostream>
#include "ising.h"

using namespace std;
using namespace chrono;

/*
http://www.alltheheavylifting.com/five-online-olympic-weightlifting-beginner-programs/
*/

int main()
{

	//Initializing important variables
	int L = 2; //Latice size
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
				printf(" 1 ");
			}
			else
			{
				lattice[i][j] = -1;
				printf("-1 ");
			}
		}
		printf("\n");
	}

	//Determining the energy of the system

	double energy = 0;

	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){

			//Determining if atom is on the edge

			if(i+1 == L && j+1 != L){
				energy += - (lattice[i][j]) * (lattice[i][j + 1] + lattice[0][j]);
			}
			else if(j+1 == L && i+1 != L){
				energy += - (lattice[i][j]) * (lattice[i + 1][j] + lattice[i][0]);
			}
			else if(j+1 == L && i+1 == L){
				energy += - (lattice[i][j]) * (lattice[i][0] + lattice[0][j]);
			}
			else{
				energy += - (lattice[i][j]) * (lattice[i][j + 1] + lattice[i + 1][j]);
			}
		}
	}
	printf("%f \n", energy);
}
