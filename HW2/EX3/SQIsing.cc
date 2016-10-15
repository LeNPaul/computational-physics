#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include "ising.h"

using namespace std;

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

	//Initialize an empty array with the appropriate size then add spin configurations
	
	vector<vector<int>> SpinConf;
	SpinConf.resize(L, vector<int>(L));
	initializeSpin(SpinConf);

	cout << "Enter the temperature: " <<endl;

	double T;

	cin >> T;

	cout << "Enter number of sweeps: " <<endl;

	int Nmcs;

	cin >> Nmcs;

	//Iterate through

	double before = Energy(SpinConf);

	MCSweeps(SpinConf,Nmcs,T);

	double after = Energy(SpinConf);

	printf("Energy before is: %f \n", before);

	printf("Energy after is: %f \n", after);

}
