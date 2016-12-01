#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    
    double pi = 3.14159265359;
    
    //Set the grid size
    int N = 20;

    //Set the boundary sizes
    double L = 1;

	//Initialize an empty array with the appropriate grid size
	
	vector<vector<double>> grid;
	grid.resize(N, vector<double>(N));
    
	//Take an empty array and initialize the boundary conditions

    //j refers to the row, i to the column
    //j -> x-axis; i -> y-axis
    int i, j, k;

    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            //Initial guesses
            grid[i][j] = 0;
            //Boundary conditions
            grid[0][j] = 100;
            grid[N - 1][j] = 0;
        }
        grid[i][0] = 0;
        grid[i][N - 1] = 0;
    }
    
    double temp;
    int iterate = true;

    while(iterate)
    {
        for(i = 1; i < N - 1; ++i)
        {
            for(j = 1; j < N - 1; ++j)
            {
                temp = grid[i][j];
                
                //Perform iteration
                grid[i][j] = (grid[i][j + 1] + grid[i][j - 1] + grid[i + 1][j] + grid[i - 1][j]) / 4;

                //Check if the difference between the previous and current iteration is small enough to stop
                if(fabs(temp - grid[i][j]) < 1e-10)
                {
                    iterate = false;
                }
            }
        }
    }

    
    //Print out the array
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            printf("%f ", grid[i][j]);
        }
        printf("\n");
    }
    
    
    //Open the data files for recording observables
    ofstream myfile;
    myfile.open("data.csv");
    
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            myfile << grid[i][j] << ",";
        }
        myfile << "\n";
    }    
        
    //Close opened data files
    myfile.close();    
    
   //Plotting the exact solution 
    
	//Initialize an empty array with the appropriate grid size
	
	vector<vector<double>> exact_grid;
	exact_grid.resize(N, vector<double>(N));

    int N_prime = 100;
    
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            for(k = 1; k < N_prime; k = k + 2)
            {
                //Perform the summation for exact solution
                exact_grid[i][j] += (400 / (k * pi)) * sin(k * pi * j * h / L) * (sinh(k * pi * i * h / L)) / (sinh(k * pi));
            }
        }
    }

    printf("\n");
    
    //Print out the array
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            printf("%f ", exact_grid[i][j]);
        }
        printf("\n");
    }

    //Open the data files for recording observables
    myfile.open("exact_data.csv");
    
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            myfile << exact_grid[i][j] << ",";
        }
        myfile << "\n";
    }    

    //Close opened data files
    myfile.close();    
    
    return 0;
    
}