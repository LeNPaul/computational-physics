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
    
    return 0;
    
}