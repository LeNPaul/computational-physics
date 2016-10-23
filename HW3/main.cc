#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
using namespace chrono;

typedef vector<double> Row; // One row of the matrix 
typedef vector<Row> Matrix; // Matrix: a vector of rows

void hv(vector<double>& y, const vector<double>& x,int L);
void jacobi(Matrix &a, vector<double> &d, Matrix &v, int &nrot);
void eigsrt(vector<double> &d, Matrix &v);
inline double dotprod(const vector<double>& y, const vector<double>& x)
{ double sum = 0.0;
  for (int i=0;i<y.size();i++)
    sum += x[i]*y[i];
  return (sum);
}


int main()
{     
      typedef high_resolution_clock myclock;
      myclock::time_point beginning = myclock::now();
      // obtain a seed from the timer
      myclock::duration dur = myclock::now() - beginning;
      unsigned seed = dur.count();

      // define the geneator
      mt19937 generator(seed);
      uniform_real_distribution<double> distribution(0,1.0);
     
      int L,m;
      cout << "Size of system, L: ";
      cin >> L;
      cout << "Size of Lanczos matrix, m: ";
      cin >> m;
      int N=pow(2,L);
      vector<double> v1(N),v2(N),f(N),omega(N);

      Matrix Lan(m,Row(m)),v(m,Row(m));

      for (int i=0;i<N;i++){
        v1[i] = 1.0-2.0*distribution(generator);
        v2[i]=0.0;
      }
      .
      .

      return 0;
}
