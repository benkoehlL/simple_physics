#include <iostream>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

using namespace std;

double timestep(int,double,double,double,double);


int main()
{
  double L= 1;
  double k= 80;
  double c= 449;
  double rho= 7870;
  int n=100;
  int t=1000;
  double T[100];
  double r= n*n/L/L*k/(c*rho);
  int seed=14;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  
  for(int i=0;i<n;i++)
  {
    T[i] = 300 + (gsl_rng_uniform(rng)* 50);
  }
  for(int i=1;i<t;i++)
  {
    T[0]=(1-r)*T[0]+r*T[1];
    for(int j=1;j<(n-1);j++)
    {
      T[j]=timestep(j,T[j+1],T[j-1],T[j],r);
    }
    T[99]=(1-r)*T[n-1]+r*T[n-2];
    for(int j=0;j<n;j++)
    {
      cout << i << '\t' << j << '\t' << T[j] << '\n';
    }
    cout << '\n';
  }
  return 0;
}
  
  
  
  
  
  
  
double timestep(int n, double T2, double T0, double T1, double r){
  return ((1-2*r)*T1+r*T0+r*T2);
}



