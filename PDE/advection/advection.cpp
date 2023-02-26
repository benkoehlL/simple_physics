#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "parameter.h"

using namespace std;

int mod(int,int);
void timestep(double*);

int main(){
    ostringstream fout;
    fout << "advection.dat";
    ofstream write(fout.str().c_str());
    double* T = new double[N];
    //initial conditions
    for(int i=0;i<N;i++){
        T[i] = sin(16*i*h*2*M_PI)*exp(-(i*h-L/2)*(i*h-L/2)/(0.02));
    }
    for(int t=0;t<(tend/(tau));t++){
        timestep(T);
        for(int i=0;i<N;i++){
            write << T[i] << '\t';
        }
        write << '\n';
    }
    delete[] T;
    return 0;
}

int mod(int i, int j){
    if(i>=0){
        return(i%j);
    }
    else{
        return((i+j)%j);
    }
}

void timestep(double* T){
    double* Tn = new double[N];
    double pre = c*(tau)/(2*h);
    for(int i=0;i<N;i++){
        Tn[i] = T[i] - pre*(T[mod(i+1,N)]-T[mod(i-1,N)]) + 2*pre*pre*(T[mod(i+1,N)]+T[mod(i-1,N)]-2*T[i]);
    }
    for(int i=0;i<N;i++){
        T[i] = Tn[i];
    }
}
