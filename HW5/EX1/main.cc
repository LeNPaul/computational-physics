#include "myhead.h"
#include "MDsim.h"
#include <fstream>
    
void readin(Params & mypars);
void pheader(Params & mypars);
void setparams(Params & mypars);

int main()
{     
    
    //Open the data files for recording observables
    ofstream myfile;
    myfile.open("data.csv");

    myfile << exact_grid[i][j] << ",";    
    
      Params simparams;
      readin(simparams);
      setparams(simparams);
      pheader(simparams);

      MDsim mysim(simparams);
      mysim.Initialize();
      for (int step=1; step <= simparams.stepLimit; step++) mysim.SingleStep();

    //Close opened data files
    myfile.close();  
    
      return 0;
}
