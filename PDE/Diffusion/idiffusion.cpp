#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "parameter.h"

using namespace std;

void FTCS_tstep(double*,double*,double);
void RS_tstep(double*, double*,double);

int main(){
    ostringstream fout;
    fout << "iwire.dat";
    ofstream write(fout.str().c_str());
    double L = 1.0;
    double hx = L/(N-1);
    double* T = new double[N];
    double* Tn = new double[N];
    double coeff = tau*k/(hx*hx);
    //initial conditions
    for(int i=0;i<N;i++){
        T[i] = -4.0*i*(i-N+1)/(N*N);
    }
    //cerr << "These are the initial conditions:" << '\n';
    for(int i=0;i<N;i++){
        write << T[i] << '\t';
    }
    write << '\n';    
    
    //first FTCS time step

    FTCS_tstep(T,Tn,coeff);    
    coeff = 2*coeff;
    for(int t=0;t<tend/tau;t++){
        RS_tstep(T,Tn,coeff);
        if( (t%plot_step) < 1){
            for(int i=0;i<N;i++){
       		 write << T[i] << '\t';
	    }
	    write << '\n';
        }
    }
    write.close();
    delete[] T;
    delete[] Tn;
    return 0;
}

void FTCS_tstep(double *T, double *Tn,double coeff){
   Tn[0] = T[0];
   Tn[N-1] = T[N-1];
   for(int i=1;i<N-1;i++){
      Tn[i] = T[i] + coeff*(T[i+1]+T[i-1]-2*T[i]);
   }
}

void RS_tstep(double *T, double *Tn,double coeff){
   double* Tnn = new double [N];
   Tnn[0] = Tn[0];
   Tnn[N-1] = Tn[N-1];
   for(int i=1; i<N-1; i++){
      Tnn[i] = coeff/(coeff+1.0)*(Tn[i+1]+Tn[i-1]-T[i])+1.0/(coeff+1)*T[i];
   }
   for(int i=0;i<N;i++){
      T[i] = Tn[i];
      Tn[i] = Tnn[i];
   }
   delete[] Tnn;
}
