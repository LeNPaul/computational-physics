#include <cmath>
#include <vector>
#include <iostream>
#include "jacobi.h"

using namespace std;

typedef vector<double> Row; // One row of the matrix
typedef vector<Row> Matrix; // Matrix: a vector of rows

int main()
{

	Matrix H;
	
	int L = 5;

	H.resize(L, vector<double>(L));

	for(int i = 0; i < L; ++i)
	{
		for(int j = 0; j < L; ++j)
		{
			H[i][j] = 9.0;
		}
	}

	printMatrix(H);


	return 0;
}
