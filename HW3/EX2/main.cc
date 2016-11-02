#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include "hv.h"
#include "jacobi.h"

using namespace std;

typedef vector<double> Row; // One row of the matrix 
typedef vector<Row> Matrix; // Matrix: a vector of rows

int main()
{          

	//Open a new file in write mode for the observables
	ofstream rawData;
	rawData.open("data.csv");

	//Write the header line of the data file
	rawData << "L, M, E0, E1, E2, dE0, dE1-0 \n";

	//Gather data; only allow even numbers
	for(int s = 10; s <= 20; s+=2)
	{
		//This sets the values of L
		int L = s;

		for(int k = 0; k <= 9; ++k)
		{
			//This sets the values of M
			int m = 5 + 5 * k;

			int N = pow(2,L);

			vector<double> v1(N),v2(N),f(N),omega(N);

			vector<double> d(m);

			Matrix Lan(m,Row(m)),v(m,Row(m));

			//Initialize the random vector and the initial empty vector
			for (int i=0;i < N;i++)
			{
				v1[i] = 1.0-2.0*rando();
				omega[i] = 0.0;
			}

			//Normalize the random vector

			normalize(v1);

			//Now get the Hamiltonian
			hv(omega,v1,L);

			//a0
			Lan[0][0] = dotprod(v1,omega);

			for (int i = 0; i < N; ++i)
			{
				f[i] = omega[i] - Lan[0][0] * v1[i];
			}

			//Loop to get Lan

			for(int j = 0; j < m - 1; ++j)
			{

				Lan[j][j + 1] = normConst(f);
				Lan[j + 1][j] = Lan[j][j + 1];

				for(int i = 0; i < N; ++i)
				{
					v2[i] = f[i] / Lan[j][j + 1];
				}

				hv(omega, v2, L);

				for(int i = 0; i < N; ++i)
				{
					omega[i] = omega[i] - Lan[j][j + 1] * v1[i];
					v1[i]= v2[i];
				}
		
				Lan[j + 1][j + 1] = dotprod(v2,omega);
		
				for(int i = 0; i < N; ++i)
				{
					f[i] = omega[i] - Lan[j + 1][j + 1] * v2[i];
				}

			}

			//Find eigenvalues
			for(int i = 0; i < 10; ++i)
			{
				jacdiag(Lan, d);
			}

			//Sort the eigenvalues
			sort(d.begin(), d.begin() + m);

			//Find the difference in grounnd energies
			double groundEDiff = fabs(-4.5154463544 - d[0]);

			//Find the difference in energies from E1 and E0
			double energyDiff = fabs(d[1] - d[0]);

			//Print data to file

			rawData << L << ", " << m << ", " << d[0] << ", " << d[1] << ", " << d[2] << ", " << groundEDiff << ", " << energyDiff << "\n";
		}

	}

	//Close the opened file
	rawData.close();

	return 0;

}
