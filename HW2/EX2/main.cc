#include <iostream>
#include "ranz.h"
#include <stdio.h>
#include <math.h>

using namespace std;

int main()
{     

	//Seeding the programs

	unlong idum;

	int iseed = 1;
      
	int irh[4];

	int steps = 100;

	int igenranArray[steps], mzranArray[steps]; 

	cout << "igenran method: \n";

	int r0, r1, r2;

	for (int i=1;i<=steps;i++){
		igenran(i, irh,4);

		int rando = irh[3];

		igenranArray[i] = rando;

		printf("%i: %d \n",i,rando);

		if(rando % 3 == 1)
		{
			r1 += 1;
		}
		else if(rando % 3 == 2)
		{
			r2 += 1;
		}
		else
		{
			r0 += 1;
		}
    }

    cout << "mzran method: \n";

	int rZero, rOne, rTwo = 0;

	ranset(irh[0],irh[1],irh[2],irh[3]);
   	for (int i=1;i<=steps;i++){
		
		int random = mzran();

		mzranArray[i] = random;

		//printf("%i: %lu\n",i,random);

		if(random % 3 == 1)
		{
			rOne += 1;
		}
		else if(random % 3 == 2)
		{
			rTwo += 1;
		}
		else
		{
			rZero += 1;
		}

	}

	//Print remainder for igenran function
	printf("Remainder 0: %i \nRemainder 1: %i \nRemainder 2: %i \n", r0, r1, r2);

	//Print remainder for mzran function
	printf("Remainder 0: %i \nRemainder 1: %i \nRemainder 2: %i \n", rZero, rOne, rTwo);
}
