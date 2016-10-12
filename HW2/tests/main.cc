#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int passArray(vector<vector<int>>& array)
{
	int test = array[5][5];

	printf("testing: %i \n", test);
	return 0;
}

int main()
{cd 



	printf("Enter lattice size: \n");
	scanf("%i", &L);

	/*int *array = new int[r];

	int** ary = new int*[L];
	for(i = 0; i < L; ++i)
	{
		ary[i] = new int[L];
	}*/

	vector<vector<int>> lattice;

	lattice.resize(L, vector<int>(L));

	lattice[5][5] = 1234;

	passArray(lattice);

	return 0;
}
