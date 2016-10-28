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
	printf("\n");
}

void jacdiag(vector<vector<double>> & A, vector<double> & d)
{

	int n = A.size();

	for(int p = 0; p < n; ++p)
	{
		for(int q = p + 1; q < n; ++q)
		{
			//Check that matrix element is large enough
			if(fabs(A[p][q]) > 2.2*pow(10,-16))
			{

				//Initialize a new matrix to store results
				vector<vector<double>> A_prime = A;

				//Calculate required variables first
				double theta = (A[q][q] - A[p][p]) / (2 * A[p][q]);
				double t = (theta / fabs(theta)) / (fabs(theta) + sqrt(theta*theta + 1));
				double c = 1 / sqrt(t * t + 1);
				double s = t * c;
				double tau = s / (1 + c);

				//Calculate output diagonal matrix elements
				A_prime[p][p] = A[p][p] - t * A[p][q];
				A_prime[q][q] = A[q][q] + t * A[p][q];

				//Calculate the rest of the matrix elements
				for(int r = 0; r < n; ++r)
				{
					//Check that elements aren't on the diagonal
					if(r != q && r != p)
					{
						A_prime[r][p] = A[r][p] - s * (A[r][q] + tau * A[r][p]);
						A_prime[r][q] = A[r][q] + s * (A[r][p] - tau * A[r][q]);

						A_prime[p][r] = A[p][r] - s * (A[q][r] + tau * A[p][r]);
						A_prime[q][r] = A[q][r] + s * (A[p][r] - tau * A[q][r]);
					}
				}
				//Set some elements to zero
				A_prime[p][q] = 0.0;
				A_prime[q][p] = 0.0;

				//Set the initial matrix with the new matrix
				A = A_prime;

				//Set the vector d with the eigenvalues of A
				for(int i = 0; i < n; ++i)
				{
					d[i] = A[i][i];
				}
			}
		}
	}
}

double sqSum(vector<vector<double>> & A)
{
	int n = A.size();
	double sum = 0.0;
	
	for(int i = 0; i < n; ++i)
	{
		for(int j = i + 1; j < n; ++j)
		{
			sum += A[i][j]*A[i][j];
		}
	}
	return sum;
}

void initializeEnergy(vector<vector<double>> & A)
{
	int n = A.size();

	//Constants
    double pi= 3.14159265359;
    double m= 1;//9.10938356*pow(10, -31);
    double h= 1; //6.2607004*pow(10, -34);
    double L = 1;//pow(10, -9);
    double E0= 0;
	
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(i == j)
			{
				E0 = ((i + 1) * (i + 1) * pi * pi * h * h) / (2 * m * L * L);
			}
			else
			{
				E0 = 0;
			}
			//Potential energy component
			A[i][j]= E0 + ((h * h)/(20 * m * L)) * pi * min(i+1,j+1) + ((5 * h * h) / (m*L)) * pow(-1, j-i) * pi * min(i+1,j+1);
		}
	}	
}
