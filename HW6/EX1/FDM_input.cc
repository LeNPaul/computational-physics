#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <omp.h>

    using namespace std;
using namespace chrono;





int main()

{
int nthreads;// number of threads
int n_steps=  10000; //num of maximum steps
//number of divisions within the cavity
    
int N= 1000; 
    


     cout<<"Number of Threads (0 == serial   >0 == multi-thread)  : "<<endl; 
    cin>>nthreads; 
   
//multi-threading portion
    
    if (nthreads>0)
{
    
     omp_set_num_threads(nthreads);  
   vector <vector<double>> U1, U2;
U1.resize(N+1, vector<double>(N+1));  // OLD MATRIX
U2. resize(N+1, vector<double>(N+1)); // NEW MATRIX


//initialize boundary conditions of cavity
   

for (int i = 0 ; i<=N; ++i)
    {
        U1[N][i]= 100;
        U2[N][i]= 100;
    }


double epsilon= 0.005 ;
double max_diff= 0; //difference of maximum value of cavity
int leave_loop= 0; 
  
    
    
  typedef high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();
  
//finite difference method
#pragma omp parallel
{
    int i,j,k, id; 
       double max_diff_thread= 0.0 ; 
    id= omp_get_thread_num();
   
    
       #pragma omp critical
      {   
//checking all threads are running
cout << "Hi from thread " << omp_get_thread_num() <<"\n";
      }
            
    
    
    
    
for ( k = 0 ; k< n_steps; k++)
    
   {
       
#pragma omp for 
for( i=1; i < N; ++i)
    {
        for( j=1; j < N; ++j)
                {
//finite difference method 
                   U2[i][j]= 0.25*( U1[i+1][j] + U1[i-1][j] + U1[i][j+1] + U1[i][j-1] );
  
            
                   if  (abs(U2[i][j]-U1[i][j])  > max_diff_thread ) max_diff_thread = abs(U2[i][j]-U1[i][j]) ;
        
        
                }
    }
        
   #pragma omp critical
      {
      if (max_diff_thread>max_diff) max_diff = max_diff_thread;
      }
            
     max_diff_thread= 0.0; 
                
        
//synchronize all of the threads   
#pragma omp barrier 
        
        if (id==0) 
        {
 swap(U1,U2);
 if (max_diff < epsilon)
         {
               cout<<"Number of loops:"<< k<<endl;
               cout<<"maximum differene is :"<< max_diff <<endl;
               cout<<"the number of threads used was :"<< omp_get_num_threads()<<endl; 
               leave_loop= 1; 
         } 
        
 max_diff= 0.0;
 if (k==(n_steps))cout<<"Maximum  loops N ="<<k+1<<endl;

        } 
        
    
      #pragma omp barrier
      if (leave_loop) break;
       
        }
    }



  myclock::duration d = myclock::now() - beginning;
  printf("Time : %ims\n",duration_cast<milliseconds>(d));
    cout<<" "<<endl; 
        
}
      
    
    
    
    
   //serial code 
    
if (nthreads==0)
    
    
{
    
    
  
   vector <vector<double>> U1, U2;
U1.resize(N+1, vector<double>(N+1));  // OLD MATRIX
U2. resize(N+1, vector<double>(N+1)); // NEW MATRIX


//initialize boundary conditions of cavity
   

for (int i = 0 ; i<=N; ++i)
    {
        U1[N][i]= 100;
        U2[N][i]= 100;
    }


double epsilon= 0.005 ;
double max_diff= 0; //difference of maximum value of cavity
int leave_loop= 0; 
  
    
    
  typedef high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();
  
//finite difference method

   
    for (int k = 0 ; k< n_steps; k++)
    
    {
       
for(int i=1; i < N; ++i)
    {
        for(int j=1; j < N; ++j)
                {
//finite difference method 
   U2[i][j]= 0.25*( U1[i+1][j] + U1[i-1][j] + U1[i][j+1] + U1[i][j-1] );
  
            
            if  (abs(U2[i][j]-U1[i][j])  > max_diff ) max_diff = abs(U2[i][j]-U1[i][j]) ;
        
        
        }
}
        

 
       
 swap(U1,U2);
 if (max_diff < epsilon)
 {
  cout<<"Number # loops taken:"<< k<<endl;
   cout<<"max diff is :"<< max_diff <<endl;
     leave_loop= 1; 
 } 
        
 max_diff= 0.0;
 if (k==(n_steps))cout<<"Maximum  loops N ="<<k+1<<endl;;
      if (leave_loop) break;
        
       
    }



  myclock::duration d = myclock::now() - beginning;
  printf("Time : %ims\n",duration_cast<milliseconds>(d));
        
    
    
    
}
    
    
    
    
    
    
    
}






