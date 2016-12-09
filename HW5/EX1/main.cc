#include "myhead.h"
#include "MDsim.h"
#include <fstream>
#include <algorithm>
    
void readin(Params & mypars);
void pheader(Params & mypars);
void setparams(Params & mypars);

int main()
{     
    //Open the data files for recording observables
    ofstream myfile;
    myfile.open("data.csv");
    
    ofstream myfile1;
    myfile1.open("data_002.csv");
    ofstream myfile2;
    myfile2.open("data_004.csv");
    ofstream myfile3;
    myfile3.open("data_006.csv");
    ofstream myfile4;
    myfile4.open("data_008.csv");
    ofstream myfile5;
    myfile5.open("data_01.csv");
    ofstream myfile6;
    myfile6.open("data_02.csv");
    ofstream myfile7;
    myfile7.open("data_04.csv");
    ofstream myfile8;
    myfile8.open("data_1.csv");
    
    Params simparams;
    readin(simparams);
    setparams(simparams);
    pheader(simparams);

    MDsim mysim(simparams);
    mysim.Initialize();
    
    for(int step=1; step <= simparams.stepLimit; step++)
    {
        mysim.SingleStep();

        //Data for 1.7
        
        //Average total energy - Error - Average total kinetic energy - Error
        myfile << mysim.Etot_Avrg << "," << mysim.Etot_Err_Avrg << "," << mysim.Ekin_Avrg << "," << mysim.Ekin_Err_Avrg << ",";

        //Average pressure - Error
        myfile<<mysim.Pressure_Avrg<<"," << mysim.Pressure_Err_Avrg << "\n";
        
        //Histograms for 1.8
        
        //Change the step number to appropriate step value to record observable
        if(step == 0.02 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile1 << mysim.v_h[i] << "\n";
            }        
        }
        else if(step == 0.04 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile2 << mysim.v_h[i] << "\n";
            }        
        }        
        else if(step == 0.06 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile3 << mysim.v_h[i] << "\n";
            }        
        } 
        else if(step == 0.08 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile4 << mysim.v_h[i] << "\n";
            }        
        } 
        else if(step == 0.1 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile5 << mysim.v_h[i] << "\n";
            }        
        } 
        else if(step == 0.2 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile6 << mysim.v_h[i] << "\n";
            }        
        } 
        else if(step == 0.4 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile7 << mysim.v_h[i] << "\n";
            }        
        }  
        else if(step == 1.0 * simparams.stepLimit)
        {
            //Sort vector
            sort(mysim.v_h.begin(), mysim.v_h.begin() + simparams.nAtoms);    

            for(int i = 0; i < simparams.nAtoms; ++i)
            {
                myfile8 << mysim.v_h[i] << "\n";
            }        
        }         
    }

    //Close opened data files
    myfile.close();  
    myfile1.close();
    myfile2.close();
    myfile3.close();
    myfile4.close();
    myfile5.close();
    myfile6.close();
    myfile7.close();
    myfile8.close();
    
      return 0;

}