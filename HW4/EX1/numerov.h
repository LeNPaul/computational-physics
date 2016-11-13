#include <vector>

using namespace std;

double V(double x);

double kappa(double x);

void right_phi(vector<double> & phi_r, double h, double x_right, int x_m);

void left_phi(vector<double> & phi_l, double h, double x_left, int x_m);
