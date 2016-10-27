#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

void printMatrix(vector<vector<int>>& matrix)
{

	//Print out the Matrix to the command line
	//To make it easier to read on the command line, a spin of 1 corresponds to 0, and -1 to an empty space
	
	int i,j;
	int L = matrix.size();

	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){
			if(matrix)[i][j] == 1)
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

/*
void jacdiag(Matrix & A, vector<double> & d)
{
	//Taking in the required variables

	cout << "Enter the number of columns: " <<endl;

	int n;

	cin >> n;

	cout << "Enter the matrix size you wish to implement: " <<endl;

	int n;

	cin >> n;

}
*/
