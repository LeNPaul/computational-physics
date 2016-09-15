#include <stdio.h>

int Sq_Tlr(float x)
{
	//The Taylor series is computed with a = 1 for the first 5 terms

	float root = 2/3;

	//float root = 1 + (x - 1) / 2 - ((x - 1) * (x - 1)) / 8 + ((x - 1) * (x - 1) * (x - 1)) / 16 - (5 * (x - 1) * (x - 1) * (x - 1) * (x - 1)) / 128;

	return root;
}

int main() 
{ 	
	float value = Sq_Tlr(2);	

	printf("%f \n" , value);
}
