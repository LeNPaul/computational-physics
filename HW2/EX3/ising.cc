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

void printLattice(vector<vector<int>>& lattice)
{

	//Print out the lattice to the command line
	//To make it easier to read on the command line, a spin of 1 corresponds to 0, and -1 to an empty space
	
	int i,j;
	int L = lattice.size();

	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){
			if(lattice[i][j] == 1)
			{
				printf("0 ");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}	
}

double Energy(vector<vector<int>>& lattice)
{

	//Calculates the energy of the lattice

	double energy = 0;
	int L = lattice.size();
	int i,j;

	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){

			//Determining if atom is on the edge and applying periodic boundaries

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

void spinFlip(vector<vector<int>>& lattice, double T)
{
	int i,j;
	int L = lattice.size();

	//Initialize a temporary lattice
	vector<vector<int>> tempLattice = lattice;

	//Pick a random spin

	i = round(rando() * (L-1));
	j = round(rando() * (L-1));

	//Flip the spin of a temporary lattice

	tempLattice[i][j] = - lattice[i][j];
	
	//Compare energies of both lattices
	double iE, fE, dE;
	
	iE = Energy(lattice);
	fE = Energy(tempLattice);

	//Calculating change in energy, including the J value
	dE = (fE - iE);

	if(fE <= iE)
	{	
		//Flip the spin for the actual lattice
		lattice[i][j] = - lattice[i][j];
	}
	else if(fE > iE)
	{
		if(exp(- dE / T) > rando())
		{	
			//Flip the spin for the actual lattice
			lattice[i][j] = - lattice[i][j];
		}else
		{
			//Do nothing
		}
	}
}

void MCSweeps(vector<vector<int>>& lattice, int Nmcs, double T)
{
	int L = lattice.size();
	int i;

	Nmcs = Nmcs * L * L;

	for(i = 0; i < Nmcs; ++i)
	{
		spinFlip(lattice,T);
		printLattice(lattice);
	}
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
			}
			else
			{
				lattice[i][j] = -1;
			}
		}
	}
}

void warmup(vector<vector<int>>& lattice, int NWarmup, double T)
{
	//Performs warmup sweeps on an initialized lattice using the spinFlip function
	for(int i = 0; i < NWarmup; ++i)
	{
		spinFlip(lattice,T);
	}
}
