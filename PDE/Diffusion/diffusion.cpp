#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "parameter.h"

using namespace std;

void tstep(double*,double);

int main(){
    ostringstream fout;
    fout << "wire.dat";
    ofstream write(fout.str().c_str());
    double L = 1.0;
    double hx = L/(N-1);
    double* T = new double[N];
    
    //check stability
    double coeff = k*tau/(hx*hx);
    if(coeff< 0.5){
        cerr << "Solution is expected to be stable." << '\n';
    }
    else{
        cerr << "WARNING: Solution is not expected to be stable." << '\n';
    }
    
    //initial conditions
    for(int i=0;i<N;i++){
        T[i] = -4.0*i*(i-N+1)/(N*N);
    }
    //cerr << "These are the initial conditions:" << '\n';
    for(int i=0;i<N;i++){
        write << T[i] << '\t';
    }
    write << '\n';    
    
    //time steps
    for(int t=0;t<tend/tau;t++){
        tstep(T,coeff);
        if( (t%plot_step) < 1){
            for(int i=0;i<N;i++){
       		 write << T[i] << '\t';
	    }
	    write << '\n';
        }
    }
    write.close();
    return 0;
}

void tstep(double *T, double coeff){
   double* Tn = new double[N];
   Tn[0] = T[0];
   Tn[N-1] = T[N-1];
   for(int i=1;i<N-1;i++){
      Tn[i] = T[i] + coeff*(T[i+1]+T[i-1]-2*T[i]);
   }
   for(int i=0;i<N;i++){
      T[i] = Tn[i];
   }
   delete[] Tn;
}
