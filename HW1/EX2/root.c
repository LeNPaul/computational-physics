#include <stdio.h>

int main() 
{
// Program for estimate Pi to a given accuracy
// Filename pi.c Src: JWW 2014

  int n;
  float term, small, sum, pi, t;
  
  printf("Welcome to the pi estimator program\n");

  printf( "Please enter the precision that you desire (how small you want the smallest term in the series to be): " );
  scanf("%f",&small);

  n = 1;
  term = 1;
  sum = term;

  if (small <= 0){
  printf("The valued entered was less than or equal to zero, and is therefore invalid. Please enter a positive number instead.");
  return 1;
}

  for (;;) {
    n++;
    t = term;
    term = t*(n-1)/(2*n-1);
    sum = term + sum;
    if (term <= small) break;
  }

  pi = 2*sum;

  printf("Our pi estimate is %25.20f\n",pi);
  printf("This differs from true pi by %25.20f\n", 
	 pi-3.141592653589793238462643383279502884197169399375105820974944e0 );
  printf("The smallest term included was %25.20f\n",term);
  printf("The number of terms summed was %i\n", n);
}
