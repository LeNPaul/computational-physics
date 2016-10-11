#include <random>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

double rando()
{

	//Returns a random number between 0 and 1

	typedef high_resolution_clock myclock;

	myclock::time_point beginning = myclock::now();

	// obtain a seed from the timer

	myclock::duration d = myclock::now() - beginning;

	unsigned seed = d.count();

	// define the generator

	mt19937 generator(seed);

	uniform_real_distribution<double> distribution(0,1.0);

	return distribution(generator);

}

void spinFlip(vector<vector<int>>& lattice)
{
	//Pick a random spin
	
	int i,j;
	int L = lattice.size();

	i = round(rando() * (L-1));
	j = round(rando() * (L-1));

	//Flip the spin

	lattice[i][j] = - lattice[i][j];
	
}

void initializeSpin(vector<vector<int>>& lattice)
{
	//Take an empty lattice array and initialize spins
	//Commenting out the printf parts will print the lattice after it is initialized	

	int i,j;
	int L = lattice.size();

	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){
			if(rando() < 0.5){
				lattice[i][j] = 1;
				//printf(" 1 ");
			}
			else
			{
				lattice[i][j] = -1;
				//printf("-1 ");
			}
		}
		//printf("\n");
	}
}

void printLattice(vector<vector<int>>& lattice)
{
	//Print out the lattice to the command line
	
	int i,j;
	int L = lattice.size();

	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){
			printf(" %i ", lattice[i][j]);
		}
		printf("\n");
	}	
}

double Magnetization(vector<vector<int>>& lattice)
{
	int i,j;
	double total;
	int L = lattice.size();

	for(i = 0; i < L; ++i)
	{
		for(j = 0; j < L; ++j)
		{
			total += lattice[i][j];
		}
	}
	
	return total;

}

double Energy(vector<vector<int>>& lattice)
{
	double energy = 0;
	int L = lattice.size();
	int i,j;

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

	return energy;

}
