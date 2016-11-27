#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include "numerov.h"

using namespace std;

//Set some constants as global variables
double pi = 3.14159265359;
double hbar = 1;
double m = 1;
double E;

//Set the grid size
int N = 10000;

//Set the boundary sizes for 1.3
double x_left = -100; //Left boundary
double x_right = 100; //Right boundary

//Set the boundary sizes for 1.6
//double x_left = 0; //Left boundary
//double x_right = pi / 2; //Right boundary

//Determine the step size
double h = (x_right - x_left) / N;

int i_match = 0;

//Wave function integrating from left to right
vector <double> phi_left(N + 1); 

//Wave function integrating from right to left
vector <double> phi_right(N + 1);

//Total wave function
vector <double> phi(N + 1); 

/*
    The following are potential functions that can be chosen by changing one of the functions to double V(double x)
*/

double V(double x)
{
	//This is the potential for 1.3
	if(x < 5 && x > -5)
	{
		return x * x / 5 - 14;
	}
	else
	{
		return 0;
	}
}

double V2(double x)
{
	//This is the potential for 1.6
	if(x < pi / 2 && x > 0)
	{
		return (hbar * hbar / (2 * m)) * (0.05 / (sin(x) * sin(x)) + 5 / (cos(x) * cos(x)));
	}
}

double V3(double x)
{
	//This is the potential for the hint that was given

    double lambda = 10;
    
    return (hbar * hbar / (2 * m)) * (lambda * (lambda - 1)) * (1 / 2 - 1 / (cosh(x) * cosh(x)));

}

//The k value
double kappa(double x)
{
	//Since kappa always appears squared, we can just return the unsquared value
	return m * (E - V(x)) / (hbar * hbar);
}

//The eigenvalue function
double F(double E)
{
    //Use the global E value
    ::E = E;
    
    //First find the match point starting from the right boundary, and increment to the left using steps of size h
    double x = x_right;
    i_match = N;
    
    while(V(x) > E)
    {
        --i_match;
        x-= h;
        if(i_match < 0)
        {
            cerr << "Can't find right turning point" << endl;
            exit(EXIT_FAILURE);
        }
    }

    //Integrate from left to right using Numerov algorithm for phi_left
    
    //Set the first value to 0 and the second value to 1E-10
    phi_left[0] = 0;
    phi_left[1] = 1e-10;

    for (int i = 1; i <= i_match; i++)
    {
        x = x_left + i * h;
        phi_left[i + 1] = ( 2 * (1 - 5 * h * h * kappa(x) / 12) * phi_left[i] - ( 1 + h * h * kappa(x - h) / 12 ) * phi_left[i - 1] ) / ( 1 + h * h * kappa(x + h) / 12 );
    }
        
    //Integrate from right to left using the Numerov algorithm for phi_right
    
    //We are going from right to left, so start from N
    //Set the first value to 0 and the second value to 1E-10
    phi[N] = phi_right[N] = 0;
    phi[N-1] = phi_right[N-1] = 1e-10;

    for(int i = N - 1; i>= i_match; i--)
    {
        x= x_right - i * h;
        phi_right[i - 1] = (2 * (1 - 5 * h * h * kappa(x) / 12) * phi_right[i] - (1 + h * h * kappa(x + h) / 12) * phi_right[i + 1] ) / (1 + h * h * kappa(x - h) / 12);
        
        phi[i-1] = phi_right[i - 1] /= 1 + h * h * kappa(x - h) / 12;
    }

    //Rescale the phi_l vector to match the points
    
    double scale = phi_right[i_match] / phi_left[i_match];
    
    for (int i= 0; i <= i_match + 1; i++)
    {
        phi[i] = phi_left[i] *= scale;
    }
     
    //Problems may occur if a discontinuity occurs in F(E)
    //To prevent this, do the following:
    
    static int sign = 1; // current sign used
    static int nodes = 0; // current number of nodes

    //Count number of nodes in phi_left
    int n = 0;
    for (int i = 1; i <= i_match; i++)
    {
        if (phi_left[i-1] * phi_left[i] < 0)
        {
            ++n;
        }
    }

    //Flip its sign when a new node develops
    if (n != nodes) 
    {
        nodes = n;
        sign = -sign;
    } 
    
    return sign * (phi_right[i_match - 1] - phi_right[i_match + 1] - phi_left[i_match - 1] + phi_left[i_match + 1]) / (2 * h * phi_right[i_match]);

}

void normalize(vector<double> & phi)
{
    //This function normalizes the phi array
    
    double sum = 0;
    
    int N = phi.size();
    
    double norm = 0;
    for (int i = 0; i < N; ++i)
    {
        norm += phi[i] * phi[i];
    }

    //norm /= N;
    norm = sqrt(norm);

    for (int i = 0; i < N; ++i)
    {
        phi[i] /= (norm);
    }
}

double bisection(double  E_b, double  E_a)
{
    
    //At the end of this bisection routine, the function F(E) will be run with the outputed E value
    
    //Number of iterations before returning a root
    int i_max = 20;

    //Use F(E) to find values at boundaries
    double  F_b = F(E_b);
    double F_a = F(E_a);

    double  E_mid;
    double F_mid;

    //calculate the bisected region of the interval
    for (int i = 0 ; i< i_max; i++)
    {
        E_mid= (E_b + E_a) / 2;

        F_mid = F(E_mid);
        F_b = F(E_b);
        F_a = F(E_a);

        //Reference used for the bisection algorithm: https://en.wikipedia.org/wiki/Bisection_method

        if (F_mid > 0)
        {
            if (F_b > 0)
            {
               E_b = E_mid;
            }
        }
        
        if (F_mid < 0)
        {
            if (F_b > 0)
            {
               E_a = E_mid;
            }
        }

        if (F_mid > 0)
        {
            if (F_b < 0)
            {
               E_a = E_mid;
            }
        }

        if (F_mid < 0)
        {
            if (F_b < 0)
            {
               E_b = E_mid;
            }
        }
    }
    
    return E_mid;

}

int main()
{
    //This is the energy to start at
	double E_start = -14.0;    
    
    //This is the energy to stop at
	double E_stop = -6.0;
    
    //This is how much to increment the energy
	double step_E = (E_stop - E_start) / 4000;

    //Open the data files for recording observables
    ofstream myfile_potential;
    myfile_potential.open("data_potential_1_3.csv");
    
    ofstream myfile_phi;
    myfile_phi.open("data_phi_1_3.csv");
  	
    ofstream myfile_FE;
	myfile_FE.open("data_FE_1_3.csv");    

    //Draw the potential for visualization purposes
    for (int i = 0; i <= N; i++)
    {
        double x = x_left + i * h;
        myfile_potential << V(x) << '\n';
    }

    for (E = E_start; E <= E_stop; E = E + step_E)
    {
        normalize(phi);

        myfile_FE << E << "," << F(E) << "\n";
    }
   
    /*
        This is where the code that records the observables starts
    */
    
    //The following initial guesses were determined by inspection from plotting F(E) and estimating an interval of size 0.4 that contained a root
    
    vector <double> E_max(6), E_min(6);
    
    E_max[0] = -13.3; 
    E_min[0] = -13.7;

    E_min[1] = -12.3; 
    E_max[1] = -12.7;
    
    E_min[2] = -11.9; 
    E_max[2] = -11.5;
    
    E_min[3] = -11; 
    E_max[3] = -10.6;
    
    E_min[4] = -10; 
    E_max[4] = -9.6;
    
    E_min[5] = -9; 
    E_max[5] = -8.6;
    
    E_min[6] = -8; 
    E_max[6] = -7.6;    
    
    //Record all the wavefunctions in one file
   
    for (int j = 0; j <= 6; j++)
    {
        //Use the bisection routine to determine the roots
        E = bisection(E_min[j], E_max[j]);

        //Normalize the wavefunctions
        normalize(phi);
 
        for (int i = 0; i <= N; ++i)
        {
            //Record the eigenfunction and the probability density function
            myfile_phi << j << "," << x_left + h * i << "," << fabs(phi[i] * phi[i]) << "," << phi[i] << "\n";
        }
        
        //Print out the roots/eigenvalues
        cout << "The " << j << " eigenvalue is: " << E << "\n";
        
    }
    
    
    //Close opened data files
    myfile_FE.close();
    myfile_phi.close();
    myfile_potential.close();
}
