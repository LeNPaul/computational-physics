#include <iostream>
#include "ranz.h"
#include <stdio.h>

using namespace std;

int main()
{     

	//Seeding the programs

	unlong idum = 1234;
      
	int irh[4] = {1,2,3,4};

	int steps = 10;

 	int igenranTotal = 0;
	unlong mzranTotal = 0;

	cout << "igenran method: \n";	

	for (int i=1;i<=steps;i++){
		igenran(idum, irh,4);
		printf("%d %d \n",i,irh[3]);
		igenranTotal += irh[3];
    }

    igenranTotal = igenranTotal / steps;

    printf("igenran average: %d \n", igenranTotal);

    cout << "mzran method: \n";

      ranset(irh[0],irh[1],irh[2],irh[3]);
      for (int i=1;i<=steps;i++){
		  printf("%d %lu\n",i,mzran());
		  mzranTotal += mzran();
      }

      mzranTotal = mzranTotal / steps;

      printf("mzran average: %lu \n", mzranTotal);
}
