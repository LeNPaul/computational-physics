/*************************************************
*  Random number generator ranz
*************************************************/

#include "ranz.h"

unlong x=521288629, y=362436069, z=16163801, c=1,
       n=1131199209;

unlong mzran()
{ long int s;
  
  if (y>x+c){
    s=y-(x+c);
    c=0;
  }
  else {
    s=y-(x+c)-18;
    c=1;
  }
  x=y;
  y=z;
  return ((z=s)+(n=69069*n+1013904243));
}

void ranset(unlong xx,unlong yy,unlong zz,unlong nn)
{ x=xx;
  y=yy;
  z=zz;
  n=nn;
  c=y>z;
}

unlong M=714025, IA=1366, IC=150889;

void igenran(unlong idum, int *G, int K)
{ int i;
  for (i=1;i<=K;i++){
    idum = (IA*idum+IC)%M;
    G[i]=idum*36451;
  }
}

