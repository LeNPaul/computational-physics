#include <vector>

using namespace std;

void printLattice(vector<vector<int>>& lattice);

double Magnetization(vector<vector<int>>& lattice);

void MCSweeps(vector<vector<int>>& lattice, int Nmcs, double T);

void spinFlip(vector<vector<int>>& lattice, double T);

void initializeSpin(vector<vector<int>>& lattice);

double rando();

int passArray(vector<vector<int>>& array);

double Energy(vector<vector<int>>& lattice);

void warmup(vector<vector<int>>& lattice, int NWarmup, double T);
