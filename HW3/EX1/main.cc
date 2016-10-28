#include <cmath>
#include <vector>
#include <iostream>
#include "jacobi.h"

using namespace std;

typedef vector<double> Row; // One row of the matrix
typedef vector<Row> Matrix; // Matrix: a vector of rows

/*
	To do:
		Compare with Python implementation
		Implement timer for performance
		Structure program so that it automatically does everything I need it to do, and outputs the appropriate data
		Output data to csv file
		Get program to take in inputs through a csv file that it reads, and then runs the program automatically
*/

int main()
{

	Matrix A;

	Row d;
	
	int n = 40;

	A.resize(n, vector<double>(n));
	d.resize(n);

	/*A = {
			{1,2,3},
			{2,2,2},
			{3,2,3}
		};*/

	initializeEnergy(A);

	printMatrix(A);


	for(int i = 0; i < 10; ++i)
	{
		cout<<"The sum of squares is: "<<sqSum(A)<<endl;
		jacdiag(A, d);
		printMatrix(A);
	}

	printf("The eigenvalues are: \n");
	for(int i = 0; i < d.size(); ++i)
	{
		printf("%f \n", d[i]);
	}

	return 0;
}
