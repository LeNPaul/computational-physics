#include "ranz.h"
#include <stdio.h>
int main()
{     unlong idum;
      int irh[4];

      for (int i=1;i<=10;i++){
      igenran(idum, irh,4);
      printf("%d %d\n",i,irh[3]);
      }
      ranset(irh[0],irh[1],irh[2],irh[3]);
      for (int i=1;i<=10;i++){
      printf("%d %lu\n",i,mzran());
      }
}
