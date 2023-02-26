#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

using namespace std;

double Pi = M_PI;

int main()
{
  double L= 10;
  double k= 1.5;
  double cp= 800;
  double rho= 1500;
  int n=100;
  int t=43800;
  int h[438];
  double T[100];
  double c[100-1];
  double d[100];
  double r= 60*60*n*n/L/L*k/(cp*rho);
  int seed=14;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  
  for(int i=0;i<n;i++)
  {
    T[i] = 283;
  }
  c[0]=0;
  for(int l=1;l<(n-1);l++)
  {
    c[l]=(-r)/((1+2*r)+r*c[l-1]);
  }
  for(int i=1;i<t;i++)
  {
    d[0]=(5*sin(2*Pi*i/24)+15*sin(2*Pi*i/(365*24))+283);
    for(int l=1;l<(n-1);l++)
    {
      d[l]=(T[l]+r*d[l-1])/((1+2*r)+r*c[l-1]);
    }
    for(int l=98;l>0;l--)
    {
      T[l]=d[l]-c[l]*T[l+1];
    }
    if(i%100==0){
      h[i]=0;
      for(int j=99;j>0;j--)
      {
	if(T[j]<273)
	{
	  h[i]=j;
	}
      }
      for(int j=0;j<n;j++)
      {
	cout << i << '\t' << j << '\t' << T[j] << '\t' << h[i] << '\n';
      }
      cout << '\n';
    }
    
  }
  return 0;
}