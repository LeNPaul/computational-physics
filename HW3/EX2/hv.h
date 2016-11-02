#include <vector>

using namespace std;

void hv(vector<double>& y, const vector<double>& x,int L);

void jacobi(vector<vector<double>> &a, vector<double> &d, vector<vector<double>> &v, int &nrot);

void eigsrt(vector<double> &d, vector<vector<double>> &v);

double dotprod(const vector<double>& y, const vector<double>& x);

double rando();

double normalize(vector<double> & v);

double normConst(vector<double> & v);
