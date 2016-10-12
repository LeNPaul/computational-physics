#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include "ising.h"

using namespace std;

/*
https://www.mpp.mpg.de/~caldwell/ss10/Lecture11.pdf
http://nbviewer.jupyter.org/github/s9w/magneto/blob/master/physics.ipynb

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
http://farside.ph.utexas.edu/teaching/329/lectures/node110.html
https://www.physics.ohio-state.edu/~braaten/statphys/Ising_MatLab.pdf
http://fraden.brandeis.edu/courses/phys39/simulations/advancedlab1_Part1.pdf
http://math.arizona.edu/~tgk/541/chap1.pdf


https://en.wikipedia.org/wiki/Ising_model
https://en.wikipedia.org/wiki/Square-lattice_Ising_model

http://www.cplusplus.com/doc/tutorial/files/
https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
*/

int main()
{

	//Taking in the required variables

	cout << "Enter the lattice size you wish to implement: " <<endl;

	int L;

	cin >> L;

	//Initialize an empty array with the appropriate size then add spin configurations
	
	vector<vector<int>> lattice;
	lattice.resize(L, vector<int>(L));
	initializeSpin(lattice);

	cout << "Enter the temperature: " <<endl;

	int T;

	cin >> T;

	cout << "Enter number of sweeps: " <<endl;

	int Nmcs;

	cin >> Nmcs;

	//Iterate through

	MCSweeps(lattice,Nmcs,T);

}
