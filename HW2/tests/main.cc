#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int passArray(vector<vector<int>>& array)
{
	return 0;
}

int main()
{
	int i,L;
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

	lattice[5][5] = 1;

	int test = lattice[5][5];

	printf("testing: %i \n", test);

	passArray(lattice);

	return 0;
}
