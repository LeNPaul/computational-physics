#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <omp.h>

using namespace std;

int main()
{     
    double start_time, parallel_run_time, serial_run_time;
    int nthreads;
    
    //j refers to the row, i to the column
    //j -> x-axis; i -> y-axis
    int i, j;    
         
    //Set the thread count
    cout << "Number of threads: ";
    cin >> nthreads;

    omp_set_num_threads(nthreads);
    
    //Set the grid size
    int N = 20;

    /*
        Parallel portion of the code
    */
    
	//Initialize an empty array with the appropriate grid size	
	vector<vector<double>> grid;
	grid.resize(N, vector<double>(N));
    
	//Take an empty array and initialize the boundary conditions

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
    
    //Start the time measurement
    start_time = omp_get_wtime();    
    
    double temp;
    int iterate = true;
    
    #pragma omp parallel
    {        
        while(iterate)
        {
            #pragma omp for
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
      
            //Synchronize all of the threads   
            #pragma omp barrier 
        /*
            #pragma omp critical
            {
                cout << "Hello from the " << omp_get_thread_num() << " thread \n";
            }
        */
        }
    }
    
    //End time measurement and output runtime
    parallel_run_time = omp_get_wtime() - start_time;
    cout << "Parallel run time: "<< parallel_run_time << endl;    

    /*
        Serial portion of the code for comparison
    */
    
	//Initialize the boundary conditions again
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

    //Start the time measurement
    start_time = omp_get_wtime();    
    
    iterate = true;    
    
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
    
    //End time measurement and output runtime
    serial_run_time = omp_get_wtime() - start_time;
    cout << "Serial run time: "<< serial_run_time << endl;
    
    //Output the speedup factor
    cout << "Speedup factor: "<< serial_run_time / parallel_run_time << endl;
        
    return 0;
}