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

void warmup(vector<vector<int>>& lattice, int NWarmup, double T, int L);

void printObservables(double totalE1, double totalM1, double totalE2, double totalM2, double totalE4, double totalM4, int Nmeas, double T, int L, string filename);
