#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

//Set some constants as global variables
double pi = 3.14159265359;
double hbar = 1;
double m = 1;
double sum = 0;
double E;

//Set the grid size
int N = 10000;

//Set the boundary sizes
double x_left = -100; //Left boundary
double x_right =  100; //Right boundary

//Determine the step size
double h = (x_right - x_left) / N;

int i_match = 0;

vector <double> phi_left(N + 1); //wave function integrating from left
vector <double> phi_right(N + 1); //wave function integrating from right
vector <double> phi(N + 1); //Total wave function

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
		return 0.05 / sin(x) * sin(x) + 5 / cos(x) * cos(x);
	}
	else
	{
		return 0;
	}
}

double V3(double x)
{
	//This is the potential for the hint that was given
	if(x < 5 && x > -5)
	{
		return x * x / 5 - 14;
	}
	else
	{
		return 0;
	}
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
    ::E= E;
    double x = x_right; //start at right boundary
    i_match = N;
    
    while(V(x) > E) //in forbiden regon
    {
        --i_match;
        x-= h;
        if(i_match < 0)
        {
            cerr << "Can't find right turning point" << endl;
            exit(EXIT_FAILURE);
        }
    }

    // integrate phi_left using Numerov algorithm
    phi_left[0] = 0;
    phi_left[1] = 1e-10;

    for (int i = 1; i <= i_match; i++)
    {
        x = x_left + i * h;
        phi_left[i + 1] = ( 2 * (1 - 5 * h * h * kappa(x) / 12) * phi_left[i] - ( 1 + h * h * kappa(x - h) / 12 ) * phi_left[i - 1] ) / ( 1 + h * h * kappa(x + h) / 12 );
    }
        
    //integrate from right
    phi[N] = phi_right[N] = 0;
    phi[N-1] = phi_right[N-1] = 1e-10;

    for(int i = N - 1; i>= i_match; i--)
    {
        x= x_right- i*h;
        phi_right[i - 1] = (2 * (1 - 5 * h * h * kappa(x) / 12) * phi_right[i] - (1 + h * h * kappa(x + h) / 12) * phi_right[i + 1] ) / (1 + h * h * kappa(x - h) / 12);
        
        phi[i-1] = phi_right[i - 1] /= 1 + h * h * kappa(x - h) / 12;
    }

    //Rescale the phi_l vector to match the points
    for (int i= 0; i <= i_match + 1; i++)
    {
        phi[i] = phi_left[i] * phi_right[i_match] / phi_left[i_match];
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

void sum_check()
{
    sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += phi[i] * phi[i] * h;
    }
}

void normalize()
{
    if (sum != 1)
    {
        double norm = 0;
        for (int i = 0; i < N; i++)
        {
            norm += phi[i] * phi[i];
        }

        //norm /= N;
        norm = sqrt(norm);

        for (int i = 0 ; i <N ; i++)
        {
            phi[i] /= (norm * h);
        }
    }
}

//1.5
double F_symmmetry()
{
    normalize();
    double dev_sym = 0;
    int interval_sym = 5;
    double cnt = 0;
    int N_half = N/2;

    for (int i = 0; i <= interval_sym / h; i = i + 1 )
    {
        dev_sym += pow(pow(phi[N_half-i],2) - pow(phi[N_half + i],2), 2);
        cnt++;
    }

    dev_sym = sqrt(dev_sym / cnt);

    return dev_sym;
}

double bisection(double  E_b, double  E_a)
{
    //Number of iterations before returning a root
    int i_max = 15;

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

	//cout << " Eigenvalues of the Schroedinger equation\n" << " for V(x) = 0.2 x^2 - 14\n";

    //This is the energy to stop at
	double E_stop = -12.0;
    
    //This is the energy to start at
	double E_start = -14.0;
    
    //This is how much to increment the energy
	double step_E = (E_stop - E_start) / 4000;

    //Open the data files for recording observables
    ofstream myfile_v;
    myfile_v.open("data_potential.csv");
    
    ofstream myfile_phi;
    myfile_phi.open("data_phi.csv");
  	
    ofstream myfile;
	myfile.open("data_1_5_symm.csv");

    //Draw the potential for visualization purposes
    for (int i = 0; i <= N; i++)
    {
        double x = x_left + i * h;
        myfile_v << V(x) << '\n';
    }
    
    //Set up header for data files
	//myfile << "E" << "," << "F_E" << "," << "F_symm" << "\n";

	double temp_F_E, temp_F_symm;

    for (E = E_start; E <= E_stop; E = E + step_E)
    {
        normalize();
        temp_F_E = F(E);
        temp_F_symm = F_symmmetry();

        myfile << E << "," << temp_F_E << "," << temp_F_symm << "\n";
    }
   
    //This is where the code that records the observables starts
    
    //cout << "Eigenvalues of the Schroedinger equation\n" << " for V(x) = 0.2 x^2 - 14\n";

    //Set up header for data files
    //myfile_phi << "E" << "," << "X" << "," << "PHI" << "\n";

    //eigenvalue 1
    vector <double> E_max(6), E_min(6);

    E_max[0] = -13.54; 
    E_min[0] = -13.56;

    E_min[1] = -12.7; 
    E_max[1] = -12.6;
    
    E_min[2] = -11.8; 
    E_max[2] = -11.75;
    
    E_min[3] = -10.9; 
    E_max[3] = -10.8;
    
    E_min[4] = -9.95; 
    E_max[4] = -9.85;
    
    E_min[5] = -8.95; 
    E_max[5] = -8.85;
    
    E_min[6] = -7.8; 
    E_max[6] = -7.7;

    //Record all the wavefunctions in one file
    
    double sum= 0 ;
    
    for (int j= 0 ; j <= 6; j++)
    {
        //Use the bisection routine to determine the roots
        E= bisection(E_min[j], E_max[j]);

        normalize();
 
        sum_check();
 
        for (int i= 0 ; i <= N ; i++)
        {
            myfile_phi << j << "," << x_left + h * i << "," << fabs(phi[i] * phi[i]) << "\n";
        }
    }
    
    //Close opened data files
    myfile.close();
    myfile_phi.close();
    myfile_v.close();
}
