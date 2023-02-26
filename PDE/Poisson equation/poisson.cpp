#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "parameter.h"

using namespace std;

void update(double*,double*,bool &);
double chargedensity(double,double);

int main(){
    ostringstream fout;
    fout << "poisson.dat";
    ofstream write(fout.str().c_str());
    double* phi = new double[N*N];
    double* rho = new double[N*N];
    double phi0 = 1.0;
    double coeff = phi0 * 4.0/(M_PI*sinh(M_PI));
    //initial conditions
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            rho[i*N+j] = 100*chargedensity(i*h,j*h);
            phi[i*N+j] = coeff * sin(M_PI*i*h) * sinh(M_PI*j*h)+0.1;
        }
    }
    //boundary conditions
    for(int i=0;i<N;i++){
        phi[i*N] = 0.0;
        phi[i*N+N-1] = 0;
    }
    for(int i=0;i<N;i++){
        phi[i] = 0.0;
        phi[(N-1)*N+i] = 0.0;
    }
    
    bool condition = true;
    while(condition){
        update(phi,rho,condition);
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            write << phi[i*N+j] << '\t';
        }
        write << '\n';
    }
 delete[] phi;
 delete[] rho;
 return 0;
}

void update(double* phi, double* rho,bool &condition){
    double* newphi = new double[N*N];
    double sum = 0;
    for(int i=1;i<N-1-1;i++){
        for(int j=1;j<N-1-1;j++){
            newphi[i*N+j] = 0.25*(newphi[(i-1)*N+j] + phi[(i+1)*N+j] + phi[i*N+j+1] + newphi[i*N+j-1] + h*h*rho[i*N+j]);
            sum += fabs((1.0-phi[i*N+j]/newphi[i*N+j]));
        }
    }
    for(int i=1;i<N-1;i++){
        for(int j=1;j<N-1;j++){
            phi[i*N+j]=newphi[i*N+j];
        }
    }
    if(sum/(N*N)<=precision){
        condition = false;
    }
    delete[] newphi;
}

double chargedensity(double x,double y){
    return (1.0/(h*h)*exp(-((N*h/2-x)/(h)*(N*h/2-x)/(h)+(N*h/2-y)/(h)*(N*h/2-y)/(h))));
}