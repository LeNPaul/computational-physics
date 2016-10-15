#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;
using namespace chrono;

double new_seed;


//All of the universal constants that are needed among multiple functions including the main


double Kb = 8.6173324 * pow(10, -5);//ELECTRON VOLTS PER KELVIN
double Tc= 2.83;
double factor= log(1+ sqrt(2))/2;
double J_const= Tc* factor;
double E_O,M_O;



//WE ONLY WANNA CALCULATE THE ENTIRE ENERGY ONCE
int energy_step= 0 ;
int magnet_count= 0;
int step1 = 0;
double rando()
{
new_seed= new_seed+1;
	//Returns a random number between 0 and 1

	typedef high_resolution_clock myclock;

	myclock::time_point beginning = myclock::now();

	// obtain a seed from the timer

	myclock::duration d = myclock::now() - beginning;

	unsigned seed = new_seed;

	// define the generator

	mt19937 generator(seed);

	uniform_real_distribution<double> distribution(0,1.0);

	return distribution(generator);

}

double Energy(vector<vector<int>>& lattice)
{
	double energy = 0;
	int L = lattice.size();
	int i,j;


	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){

			//Determining if atom is on the edge

			if(i+1 == L && j+1 != L){
				energy += - (lattice[i][j]) * (lattice[i][j + 1] + lattice[0][j]);
			}
			else if(j+1 == L && i+1 != L){
				energy += - (lattice[i][j]) * (lattice[i + 1][j] + lattice[i][0]);
			}
			else if(j+1 == L && i+1 == L){
				energy += - (lattice[i][j]) * (lattice[i][0] + lattice[0][j]);
			}
			else{
				energy += - (lattice[i][j]) * (lattice[i][j + 1] + lattice[i + 1][j]);
			}
		}
	}

	return energy;

}
//If we are flipping one spin at a time, it would save time and computations when we calculate the energy difference among the interacting neighbouring spins t
//than the whole system


int quick_energy(int neighbour_sum)
{
    double dE;
    if (neighbour_sum == -4)
    {
        dE = -8;
    }
    else if (neighbour_sum == -2)
    {
        dE = -4;
    }
     else if (neighbour_sum == 0)
    {
        dE = 0;
    }
     else if (neighbour_sum == 2)
    {
        dE = 4;
    }
     else if (neighbour_sum == 4)
    {
        dE = 8;
    }

    return dE;
}


void spinFlip(vector<vector<int>>& lattice, double T, double exp_4, double exp_8)
{

	int i,j;
	int L = lattice.size();



//Pick a random spin
	i = round(rando() * (L-1));
	j = round(rando() * (L-1));

	//Compare energies of both lattices
	double  dE;

	//TO AVOID CALCULATING THE ENTIRE LATTICE BY SUMMING THE ALL OF THE LOCATIONS, WE JUST SEE THE LOCAL SPINS SURROUNDING THE FLIPED SPIN, TO FIND THE ENERGY DIFFERENCE
        int j_p1, j_m1, i_p1, i_m1, sum_temp;


        //for J COORDINATE
        if (j+1== L)
        {
            j_p1= 0 ;
            j_m1= j-1;
        }

        else if (j==0)
        {
           j_p1= j+1 ;
            j_m1= L-1;
        }

        else
        {
            j_p1= j+1;
            j_m1= j-1;
        }

               //for I COORDINATE
        if (i+1 == L)
        {
            i_p1= 0 ;
            i_m1= i-1;
        }

        else if (i==0)
        {
           i_p1= i+1 ;
            i_m1= L-1;
        }

        else
        {
            i_p1= i+1;
            i_m1= i-1;
        }

sum_temp= lattice[i_p1][j]+lattice[i_m1][j]+lattice[i][j_p1]+lattice[i][j_m1];
    dE= quick_energy(sum_temp*lattice[i][j]);



	if(dE <= 0)
	{
		//Flip the spin for the actual lattice
		lattice[i][j] = - lattice[i][j];
	//	printf("First switch, (%i, %i) \n", i, j);

	//	myfile << "First switch\n" << endl;
	}
	else if(dE ==4 )
	{
		if (exp_4 > rando())
		{
			lattice[i][j] = - lattice[i][j];
		}
	}

		else if(dE ==8 )
	{
		if (exp_8 > rando())
		{
			lattice[i][j] = - lattice[i][j];
		}
	}


	//myfile.close();

}

void MCSweeps(vector<vector<int>>& lattice, int Nmcs, double T, double exp_4, double exp_8)
{
	int L = lattice.size();
	int i;

	Nmcs = Nmcs * L * L;

	for(i = 0; i < Nmcs; ++i)
	{
		spinFlip(lattice,T,exp_4, exp_8);
	}
}

void initializeSpin(vector<vector<int>>& lattice)
{
	//Take an empty lattice array and initialize spins
	//Commenting out the printf parts will print the lattice after it is initialized

	int i,j;
	int L = lattice.size();

	for(i=0; i < L; ++i){
		for(j=0; j < L; ++j){
			if(rando() < 0.5){
				lattice[i][j] = 1;
				//printf(" 1 ");
			}
			else
			{
				lattice[i][j] = -1;
				//printf("-1 ");
			}
		}
		//printf("\n");
	}
}

void printLattice(vector<vector<int>>& lattice)
{
	//Print out the lattice to the command line

	int i,j;
	int L = lattice.size();

	for(i=0; i < L; ++i)

        {
		for(j=0; j < L; ++j)
        {
		if (lattice[i][j]>0)
            {
           printf(" 1 ");
		}
		else
		{
	   printf(" 0 ");
		}

		}
		printf("\n");
	}
}

double Magnetization(vector<vector<int>>& lattice)
{
	int i,j;
	double M;
	int L = lattice.size();

	for(i = 0; i < L; ++i)
	{
		for(j = 0; j < L; ++j)
		{
			M += lattice[i][j];
		}
	}
	return M;

}

int main()

{
int step=0;


ofstream myfile;
  	myfile.open ("data_3_3_b.csv");
//Dimensions
int L;
//cout<< "How Large would you want the sqare to be"<< endl;
//cin >> L;

//Tempurature

double  Temp_K;
//cout<< "Enter the Temperature in Kelvin of the System"<< endl;
//cin >> Temp_K;


//Warm up time
int Nwarmup;
//cout<< "Enter the number of WARM UP  Monte Carlo Sweeps"<< endl;
//cin >> Nwarmup;

//Number of Monte Carlo Sweeps
int Nmcs;
//cout<< "Enter the number of Monte Carlo Sweeps"<< endl;
//cin >> Nmcs;

//Number of MCS between measurements of Observables

int NStep;
//cout<< "Enter the number of MCS between Measurements of Observables"<< endl;
//cin >> NStep;


L=50;
Temp_K= 5;
Nwarmup= 50;
NStep= 1;
Nmcs= 1000;



   vector <vector<int>> lattice;
   lattice.resize(L, vector<int>(L));
initializeSpin(lattice);
printLattice(lattice);

int cnt= 0 ; //counter

double sum_M_O_1=0 ;double sum_M_O_2= 0 ; double sum_M_O_4=0;
double  sum_E_O_1= 0 ;  double  sum_E_O_2=0 ;  double sum_E_O_4=0 ;

//Standard Deviation otherwise known as error for <E/M> or <E/M^2>

double abs_error_mean_M_O_1, abs_error_mean_M_O_2;
double abs_error_mean_E_O_1, abs_error_mean_E_O_2;



//precalculated exponentials: If we were to flip one spin, the difference would be either +4,-4,+8,-8 and zero.
//Because we are only concerned with positive differential energies, we will pre-calculate the
//exponential for +4 and +8
double exp_4,exp_8;


// Kb is not included as it cancels out, so its better to simplify
exp_4= exp(-4.0/2.45);
exp_8= exp(-8.0/2.45);


//WARMUP BEGINS
for (int B= 1; B<=Nwarmup;++B )

{

    ++step;
    cout<<"The number of steps are "<<step<< "out of"<<Nmcs+Nwarmup<<endl;

  MCSweeps(lattice,1, Temp_K, exp_4, exp_8);

}



//MCSWEEP BEGINS

for (int A=1; A<=Nmcs; ++A)
{

MCSweeps(lattice,1, Temp_K, exp_4, exp_8);




cnt= cnt+ 1;

if (cnt==(NStep+1))


{


E_O= Energy(lattice)*J_const*Kb;

sum_E_O_1= sum_E_O_1+ E_O;
sum_E_O_2= sum_E_O_2+ E_O*E_O ;
sum_E_O_4= sum_E_O_4+ E_O*E_O*E_O*E_O;


M_O= Magnetization(lattice);

sum_M_O_1= sum_M_O_1+ M_O;
sum_M_O_2= sum_M_O_2+ M_O*M_O;
sum_M_O_4= sum_M_O_4+ M_O*M_O*M_O*M_O;
myfile<<M_O<<",";



++step;
cout<<"The number of steps are "<<step<< "out of"<<Nmcs+Nwarmup<<endl;

cnt= 0 ;


}
//printf("\n");printf("\n");
//printLattice(lattice);
}


// VALUES
double mean_E_O_1= sum_E_O_1/Nmcs;
double mean_E_O_2= sum_E_O_2/Nmcs;
double mean_E_O_4= sum_E_O_4/Nmcs;

double mean_M_O_1= sum_M_O_1/Nmcs;
double mean_M_O_2= sum_M_O_2/Nmcs;
double mean_M_O_4= sum_M_O_4/Nmcs;

//ABSOLUTE ERROR BARS
abs_error_mean_E_O_1= sqrt((mean_E_O_2-mean_E_O_1*mean_E_O_1)/(Nmcs-1));
abs_error_mean_E_O_2= sqrt((mean_E_O_4-mean_E_O_2*mean_E_O_2)/(Nmcs-1));

abs_error_mean_M_O_1= sqrt((mean_M_O_2-mean_M_O_1*mean_M_O_1)/(Nmcs-1));
abs_error_mean_M_O_2= sqrt((mean_M_O_4-mean_M_O_2*mean_M_O_2)/(Nmcs-1));


//printing out the values


cout << "The value of <E> is:      " << mean_E_O_1 << " eV\n"<<endl;
cout << "The Error  of <E> is:   +-" << abs_error_mean_E_O_1 << " eV\n"<<endl;

cout << "The value of <E^2> is:    " << mean_E_O_2 << " eV\n"<< endl;
cout << "The Error  of <E^2> is: +-" << abs_error_mean_E_O_2 << " eV\n"<<endl;

cout << "The value of <E^4> is:    " << mean_E_O_4 << " eV\n"<< endl;

cout<<"\n"<<endl;

cout << "The value of <M> is:      " << mean_M_O_1 << "\n"<< endl;
cout << "The Error  of <M> is:   +-" << abs_error_mean_M_O_1 << "\n"<<endl;

cout << "The value of <M^2> is:    " << mean_M_O_2 << "\n"<< endl;
cout << "The Error  of <M^2> is: +-" << abs_error_mean_M_O_2 << " \n"<<endl;

cout << "The value of <M^4> is:    " << mean_M_O_4 << "\n"<< endl;

/*
//3.4
double C_v= (mean_E_O_2-mean_E_O_1*mean_E_O_1)/(L*L); //MISSING T^2
double abs_error_C_v= (abs_error_mean_E_O_2- 2*abs_error_mean_E_O_1)/(L*L) ;

double Xi= mean_M_O_2/(L*L);
double abs_error_Xi= abs_error_mean_M_O_2/(L*L);


//OUTPUT VALUES IN COMMAND PROMPT

cout << "The value of C_v is:    " << C_v << "\n"<< endl;
cout << "The Error of C_v is:  +-" << abs_error_C_v << "\n"<<endl;

cout<<end;

cout << "The value of Xi is:   " << Xi << "\n"<< endl;
cout << "The Error of Xi is: +-" << abs_error_Xi << " \n"<<endl;




    // number of monte carlo sweeps of the lattice

   // MCSweeps(lattice, Nmcs,Temp_K );

*/

}
