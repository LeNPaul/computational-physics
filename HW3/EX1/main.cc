#include <cmath>
#include <time.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "jacobi.h"

using namespace std;

typedef vector<double> Row; // One row of the matrix
typedef vector<Row> Matrix; // Matrix: a vector of rows

int main()
{

	//Open a new file in write mode for the observables
	ofstream myfile;
	myfile.open("data.csv");

	for(int k = 1; k <= 5; ++k)
	{

		Matrix A;

		Row d;

		int n =	10 * k;

		A.resize(n, vector<double>(n));
		d.resize(n);

		initializeEnergy(A);

		//Determine the time that this function takes
		clock_t tic = clock();

		myfile << "*****************\nMatrx of size " << n << "\n" << "*****************\n";

		myfile << "\nThe sum of squares is:\n";

		for(int i = 1; i <= 10; ++i)
		{
			myfile << i << ": " << sqSum(A) << "\n";

			//Diagonalize matrix
			jacdiag(A, d);
		}

		//Print time elapsed
		clock_t toc = clock();

		//Sort the eigenvalues
		sort(d.begin(), d.begin() + n);

		myfile << "\nEigenvalues: \n";

		for(int i = 0; i < n; ++i)
		{
			myfile << d[i] << "\n";
		}

		myfile << "\nTime elapsed: " << (double)(toc - tic)/ CLOCKS_PER_SEC << "\n\n";

	}

	//Close the opened file
	myfile.close();

	return 0;
}
