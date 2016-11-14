#include <cmath>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "numerov.h"

using namespace  std;

int main()
{
    
	//Set the grid size
	int N = 100;
    
	vector<double> phi_r;
	phi_r.resize(N);
    
	vector<double> phi_l;
	phi_l.resize(N);

    //Set the boundary sizes
	double x_left = -6;//-5;
	double x_right = 6;//5;
    
    //Determine the step size
	double h = (x_right - x_left) / N;

    //Find matching point
	int x_m = findMatch(N, x_right, h);    
    
	//Open a new file in write mode for the observables
	ofstream myfile;
	myfile.open("data.csv");

	right_phi(phi_r, h, x_right, x_m);
	left_phi(phi_l, h, x_left, x_m);
    
    rescale(phi_l, phi_r, x_m);

	for(int i = N; i > 0; --i)
	{
		myfile << phi_r[i] << "\n";
	}

	for(int i = 0; i < N; ++i)
	{
		myfile << phi_l[i] << "\n";
	}

	//Close the opened file
	myfile.close();
    
	return 0;
}
