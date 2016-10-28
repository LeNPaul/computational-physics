#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

void printMatrix(vector<vector<double>> & matrix)
{

	//Print out the Matrix to the command line
	
	int i,j;
	int n = matrix.size();

	for(i=0; i < n; ++i){
		for(j=0; j < n; ++j){
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}

void jacdiag(vector<vector<double>> & A, vector<double> & d)
{
	//Taking in the required variables

	cout << "Enter the number of columns: " <<endl;

	int n;

	cin >> n;

	cout << "Enter the number of rows: " <<endl;

	int m;

	cin >> m;

}

