#include <iostream>
#include "ranz.h"
#include <stdio.h>

using namespace std;

int main()
{     unlong idum;
      int irh[4];

      int steps = 10;

      double igenranTotal = 0;
      double mzranTotal = 0;

      cout << "igenran method: \n";	

      for (int i=1;i<=steps;i++){
      igenran(idum, irh,4);
      printf("%i %d %d %d %d %d \n",i,irh[0],irh[1],irh[2],irh[3],irh[4]);

      igenranTotal += irh[0];

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

      printf("mzran average: %d \n", mzranTotal);
}
