#include <iostream>

double energy(int x, int y, int lattice)
{
	double energy = 0;

	energy += - (lattice[x][y]) * (lattice[x + 1][y] + lattice[x - 1][y] + lattice[x][y + 1] + lattice[x][y - 1]);

	return energy;
}
