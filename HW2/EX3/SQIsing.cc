#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include "ising.h"

using namespace std;

/*
	Program flow:
	Take input values for 
*/

/*
https://www.mpp.mpg.de/~caldwell/ss10/Lecture11.pdf
http://nbviewer.jupyter.org/github/s9w/magneto/blob/master/physics.ipynb
https://arxiv.org/pdf/0803.0217.pdf
http://web.mit.edu/krish_s/www/files/ising_Model.pdf
http://www-fcs.acs.i.kyoto-u.ac.jp/~harada/monte_en.html
https://cs.adelaide.edu.au/~paulc/teaching/montecarlo/node28.html#SECTION00041000000000000000
https://www.phas.ubc.ca/~berciu/TEACHING/PHYS503/PROJECTS/05_dominic.pdf
http://www.phys.ufl.edu/courses/phy7097-cmt/fall08/lectures/dufty111008.pdf
https://triqs.ipht.cnrs.fr/1.1/reference/c++/statistics/ising2d.html
https://people.sc.fsu.edu/~jburkardt/m_src/ising_2d_simulation/ising_2d_simulation.html
http://fraden.brandeis.edu/courses/phys39/simulations/AsherIsingModelReport.pdf
http://www3.nd.edu/~mcbg/tutorials/2006/tutorial_files/ising/matlab/ising.m
http://users.minet.uni-jena.de/~ullrich/matlab/ising.html
http://www.triplespark.net/sim/isingmag/
http://physics.usc.edu/~shaas/516/isingprograms/ising.h
http://www.physik.uni-bielefeld.de/~laine/lattice/l11.pdf
http://csc.ucdavis.edu/~chaos/courses/nlp/Projects2007/JimMa/2DIsingReport.pdf
https://www.physics.ohio-state.edu/~braaten/statphys/Ising_MatLab.pdf
http://fraden.brandeis.edu/courses/phys39/simulations/advancedlab1_Part1.pdf
*/

int main()
{

	//Taking in the required variables

	cout << "Enter the lattice size you wish to implement: " <<endl;

	int L;

	cin >> L;

	//Initialize an empty array with the appropriate size
	
	vector<vector<int>> SpinConf;
	SpinConf.resize(L, vector<int>(L));

	//Initialize spin configurations
	initializeSpin(SpinConf);

	//T is taken to be the KbTc/J value
	cout << "Enter the temperature: " <<endl;

	double T;

	cin >> T;

	//Take in number of warmup steps as well as the number of sweeps done

	cout << "Enter number of warmup sweeps: " <<endl;

	int NWarmup;

	cin >> NWarmup;

	cout << "Enter number of sweeps between measurements: " <<endl;

	int NStep;

	cin >> NStep;

	cout << "Enter number of measurements to be done: " <<endl;

	int Nmeas;

	cin >> Nmeas;

	cout << "Enter the name of the data file: " <<endl;

	string dataName;

	cin >> dataName;

	cout << "Enter the name of the observable file: " <<endl;

	string observName;

	cin >> observName;

	//Print lattice before warmup

	printf("The initial lattice is: \n");	
	printLattice(SpinConf);

	//Perform warmup sweeps

	warmup(SpinConf, NWarmup, T, L);

	//Print lattice after warmup

	printf("The lattice after warmup is: \n");	
	printLattice(SpinConf);

	//Open a file in write mode.
	ofstream myfile;
	myfile.open(dataName);
	//myfile << "Energy	Magnetization\n";

	double energy, magnetization;

	double totalE1, totalM1, totalE2, totalM2, totalE4, totalM4 = 0;

	//Iterate through Nmeas measurements, each one performing Nsteps iterations

	for(int i = 0; i < Nmeas; ++i)
	{
		energy = Energy(SpinConf);
		magnetization = Magnetization(SpinConf);

		//Calculate the sum of the observables
		totalE1 += energy;
		totalE2 += energy*energy;
		totalE4 += energy*energy*energy*energy;

		totalM1 += magnetization;
		totalM2 += magnetization*magnetization;
		totalM4 += magnetization*magnetization*magnetization*magnetization;

		//Measure the energy and output to data.csv
		myfile << i + 1;
		myfile << ",";
		myfile << energy;
		myfile << ",";

		//Measure the magnetic field and output to data.csv
		myfile << magnetization;		
		myfile << "\n";
		
		MCSweeps(SpinConf, NStep, T);

	}

	//Print lattice at the end
	printf("The final lattice is: \n");	
	printLattice(SpinConf);

	//Close the opened file
	myfile.close();

	//Calculate and record observables
	printObservables(totalE1, totalM1, totalE2, totalM2, totalE4, totalM4, Nmeas, T, L, observName);

}
