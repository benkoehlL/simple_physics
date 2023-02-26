#include <iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define T 7
using namespace std;

int main()
{
  int seed=14;
  double z;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  int Test=0;
  double B1[6]={0.9,0.5,0.2,0.1,0.5,0.8},B2[16]={0.2,0.6,0.2,0,0.2,0.1,0.2,0.2,0.5,0.1,0.4,0.2,0.1,0.2,0.2,0.6};
  int O1[T]={0,1,1,0,0,0,1};
  int O2[T]={2,2,2,2,2,2,2};
  double alpha1[3*T];
  double alpha2[4*T];
  int Psi1[3*T];
  int Psi2[4*T];
  int q[T];
  int k;
  double A1[9]={0.5,0.25,0.25,0.375,0.125,0.375,0.125,0.625,0.375},A2[16]={0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25}; 
  cout << "Geben Sie (1) für das Wettermodel oder (2) für das Kugelmodel ein: " << '\n';
  cin >> Test;
  if(Test==1)
  {
    alpha1[0]=0.9;
    alpha1[1]=0;
    alpha1[2]=0;
    Psi1[0]=0;
    Psi1[1]=0;
    Psi1[2]=0;
    for(int t=1;t<T;t++)
    {
	for(int i=0;i<3;i++)
	{
	  if(A1[i]*alpha1[(t-1)*3]>A1[i+3]*alpha1[(t-1)*3+1] && A1[i]*alpha1[(t-1)*3]>A1[i+6]*alpha1[(t-1)*3+2])
	  {
	    alpha1[3*t+i]=B1[O1[t]*3+i]*A1[i]*alpha1[(t-1)*3];
	    Psi1[3*t+i]=0;
	  }
	  if(A1[i+3]*alpha1[(t-1)*3+1]>A1[i]*alpha1[(t-1)*3] && A1[i+3]*alpha1[(t-1)*3+1]>A1[i+6]*alpha1[(t-1)*3+2])
	  {
	    alpha1[3*t+i]=B1[O1[t]*3+i]*A1[i+3]*alpha1[(t-1)*3+1];
	    Psi1[3*t+i]=1;
	  }
	  if(A1[i+6]*alpha1[(t-1)*3+2]>A1[i]*alpha1[(t-1)*3] && A1[i+6]*alpha1[(t-1)*3+2]>A1[i+3]*alpha1[(t-1)*3+1])
	  {
	    alpha1[3*t+i]=B1[O1[t]*3+i]*A1[i+6]*alpha1[(t-1)*3+2];
	    Psi1[3*t+i]=2;
	  }
	  cout << alpha1[3*t+i] << '\t';
	}
	cout << '\n';
    }
    if(alpha1[3*T-3]>alpha1[3*T-2] && alpha1[3*T-3]>alpha1[3*T-1])
	{
	  q[T-1]=0;
	  k=0;
	}
    if(alpha1[3*T-2]>alpha1[3*T-3] && alpha1[3*T-2]>alpha1[3*T-1])
	{
	  q[T-1]=1;
	  k=1;
	}
    if(alpha1[3*T-1]>alpha1[3*T-2] && alpha1[3*T-1]>alpha1[3*T-3])
	{
	  q[T-1]=2;
	  k=2;
	}
    for(int j=0;j<T;j++)
    {
      q[T-j-1]=Psi1[(T-j-1)*3+k];
    }
    for(int j=0;j<T;j++)
    {
      cout << q[j] << '\n';
    }
  }
  else
  {
    alpha2[0]=0;
    alpha2[1]=0;
    alpha2[2]=0.4;
    alpha2[3]=0;
    for(int t=1;t<T;t++)
    {
	for(int i=0;i<4;i++)
	{
	  alpha2[t*4+i]= B2[O2[t]*4+i]*(A2[i*4+0]*alpha2[4*(t-1)]+A2[i*4+1]*alpha2[(t-1)*4+1]+A2[i*4+2]*alpha2[4*(t-1)+2]+A2[i*4+3]*alpha2[4*(t-1)+3]);
	}
	cout << alpha2[t*4] << '\t' << alpha2[t*4+1] << '\t' << alpha2[t*4+2] << '\t' << alpha2[t*4+3] << '\n';
    }
    cout << '\n' <<  log(alpha2[4*T-4]+alpha2[4*T-3]+alpha2[4*T-2]+alpha2[4*T-1]) << '\n';
  }
  return 0;
}

