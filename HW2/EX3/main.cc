#include <iostream>
#include <math.h>
#include <vector>
#include "ising.h"

using namespace std;

/*
https://www.mpp.mpg.de/~caldwell/ss10/Lecture11.pdf
http://nbviewer.jupyter.org/github/s9w/magneto/blob/master/physics.ipynb

*/

int main()
{

	cout << "Enter the lattice size you wish to implement: " <<endl;

	int L;

	cin >> L;

	//Initialize an empty array with the appropriate size
	
	vector<vector<int>> lattice;
	lattice.resize(L, vector<int>(L));

	//Initializing the lattice with spin configurations

	initializeSpin(lattice);

	int i;
	double energy, iE, fE, dE;

	//Iterate through

	MCSweeps(lattice,10);

}
