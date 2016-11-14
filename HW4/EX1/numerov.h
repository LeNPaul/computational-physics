#include <vector>

using namespace std;

double V(double x);

double findMatch(int N, double x_right, double h);

double kappa(double x);

void right_phi(vector<double> & phi_r, double h, double x_right, int x_m);

void left_phi(vector<double> & phi_l, double h, double x_left, int x_m);

void rescale(vector<double> & phi_l, vector<double> & phi_r, int x_m);