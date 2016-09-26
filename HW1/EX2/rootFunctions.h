#ifndef ROOTFUNCTIONS_H_INCLUDED
#define ROOTFUNCTIONS_H_INCLUDED

float Sq_Tlr(float x)
{
	//The Taylor series is computed with a = 1 for the first 8 terms

	float root = 1 + (x - 1) / 2 - (x - 1) * (x - 1) / 8 + (x - 1) * (x - 1) * (x - 1) / 16 - 5 * (x - 1) * (x - 1) * (x - 1) * (x - 1) / 128 + 7 * (x - 1) * (x - 1) * (x - 1) * (x - 1) * (x - 1) / 256 - 21 * (x - 1) * (x - 1) * (x - 1) * (x - 1) * (x - 1) * (x - 1) / 1024 + 231 * (x - 1) * (x - 1) * (x - 1) * (x - 1) * (x - 1) * (x - 1) * (x - 1) / 14336;

	return root;
}

float Sq_Nwt(float x)
{

	//Implementing the Babylonian method using a = 1 as our initial guess

	//Setting the initial guess

	float root = (1 + x) / 2;

	root = (root + x/root) / 2;

	//Iterating through the method

	int i = 0;

	for(i = 0; i <= 10; ++i){
		root = (root + x/root) / 2;
	}

	return root;
}

float Sq_Frc(float x)
{
    //Using the continued fractions representation of the square root function truncated after 6 terms
	int a = 1;

	float root =  a + (x - a*a) / (2*a + (x - a*a)/(2*a + (x - a*a)/(2*a + (x - a*a)/(2*a + (x - a*a)/(2*a + (x - a*a)/(2*a) + (x - a*a)/(2*a))))));
	// Look at http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.html

	return root;
}

#endif // ROOTFUNCTIONS_H_INCLUDED
