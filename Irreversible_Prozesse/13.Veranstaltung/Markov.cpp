#include <iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define T 1000
using namespace std;

int main()
{
  int seed=14;
  double z;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  int Test=0;
  double p1[3]={1,0,0};
  double p2[4]={0,1,0,0};
  double b1[3];
  double b2[4];  
  double pn[4];
  double B1[6]={0.9,0.5,0.2,0.1,0.5,0.8},B2[16]={0.2,0.6,0.2,0,0.2,0.1,0.2,0.2,0.5,0.1,0.4,0.2,0.1,0.2,0.2,0.6};
  double A1[9]={0.5,0.25,0.25,0.375,0.125,0.375,0.125,0.625,0.375},A2[16]={0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25}; 
  cout << "Geben Sie (1) für das Wettermodel oder (2) für das Kugelmodel ein: " << '\n';
  cin >> Test;
  if(Test==1)
  {
    for(int t=0;t<T;t++)
    {
      pn={0,0,0,0};
      for(int i=0;i<3;i++)
      {
	for(int j=0;j<3;j++)
	{
	  pn[i]+=p1[j]*A1[i*3+j];
	}
      }
      z = gsl_rng_uniform(rng);
      if(z < pn[0]){
	pn[0]=1;
	pn[1]=0;
	pn[2]=0;
      }
      if(z > pn[0] && z < pn[0]+pn[1]){
	pn[0]=0;
	pn[1]=1;
	pn[2]=0;
      }
      if(z > pn[0]+pn[1]){
	pn[0]=0;
	pn[1]=0;
	pn[2]=1;
      }
      for(int j=0;j<3;j++)
      {
	p1[j] = pn[j];
      }
      b1={0,0};
      for(int i=0;i<2;i++)
      {
	for(int j=0;j<3;j++)
	{
	  b1[i]+=p1[j]*B1[i*3+j];
	}
      }
      z = gsl_rng_uniform(rng);
      if(z < b1[0] && p1[0]!=0){
	cout << "Sonne" << '\t' << "glücklich" << '\n';
      }
      if(z > b1[0] && p1[0]!=0){
	cout << "Sonne" << '\t' << "unglücklich" << '\n';
      }
      if(z < b1[0] && p1[1]!=0){
	cout << "Wolken" << '\t' << "glücklich" << '\n';
      }
      if(z > b1[0] && p1[1]!=0){
	cout << "Wolken" << '\t' << "unglücklich" << '\n';
      }
      if(z < b1[0] && p1[2]!=0){
	cout << "Regen" << '\t' << "glücklich" << '\n';
      }
      if(z > b1[0] && p1[2]!=0){
	cout << "Regen" << '\t' << "unglücklich" << '\n';
      }
    }
  }
  else
  {
    for(int t=0;t<T;t++)
    {
      pn={0,0,0,0};
	for(int i=0;i<4;i++)
	{
	  for(int j=0;j<4;j++)
	  {
	    pn[i]+=p2[j]*A1[i*4+j];
	  }
	}
	z = gsl_rng_uniform(rng);
	if(z < pn[0]){
	  pn[0]=1;
	  pn[1]=0;
	  pn[2]=0;
	  pn[3]=0;
	}
	if(z > pn[0] && z < pn[0]+pn[1]){
	  pn[0]=0;
	  pn[1]=1;
	  pn[2]=0;
	  pn[3]=0;
	}
	if(z > pn[0]+pn[1] && z < pn[0]+pn[1]+pn[2]){
	  pn[0]=0;
	  pn[1]=0;
	  pn[2]=1;
	  pn[3]=0;
	}
	if(z > pn[0]+pn[1]+pn[2]){
	  pn[0]=0;
	  pn[1]=0;
	  pn[2]=0;
	  pn[3]=1;
	}
	for(int j=0;j<4;j++)
	{
	  p2[j] = pn[j];
	}
      b2={0,0,0,0};
      for(int i=0;i<3;i++)
      {
	for(int j=0;j<3;j++)
	{
	  b2[i]+=p2[j]*B1[i*3+j];
	}
      }
      z = gsl_rng_uniform(rng);
      if(z < b2[0] && p2[0]!=0){
	cout << "rot" << '\t' << "Urne 1" << '\n';
      }
      if(z < b2[0] + b2[1] && z > b2[0] && p2[0]!=0){
	cout << "rot" << '\t' << "Urne 2" << '\n';
      }
      if(z < b2[0] + b2[1] + b2[2] && z > b2[0] + b2[1] && p2[0]!=0){
	cout << "rot" << '\t' << "Urne 3" << '\n';
      }
      if(z > b2[0] + b2[1] + b2[2] && p2[0]!=0){
	cout << "rot" << '\t' << "Urne 4" << '\n';
      }
      if(z < b2[0] && p2[1]!=0){
	cout << "gelb" << '\t' << "Urne 1" << '\n';
      }
      if(z < b2[0] + b2[1] && z > b2[0] && p2[1]!=0){
	cout << "gelb" << '\t' << "Urne 2" << '\n';
      }
      if(z < b2[0] + b2[1] + b2[2] && z > b2[0] + b2[1] && p2[1]!=0){
	cout << "gelb" << '\t' << "Urne 3" << '\n';
      }
      if(z > b2[0] + b2[1] + b2[2] && p2[1]!=0){
	cout << "gelb" << '\t' << "Urne 4" << '\n';
      }
      if(z < b2[0] && p2[2]!=0){
	cout << "grün" << '\t' << "Urne 1" << '\n';
      }
      if(z < b2[0] + b2[1] && z > b2[0] && p2[2]!=0){
	cout << "grün" << '\t' << "Urne 2" << '\n';
      }
      if(z < b2[0] + b2[1] + b2[2] && z > b2[0] + b2[1] && p2[2]!=0){
	cout << "grün" << '\t' << "Urne 3" << '\n';
      }
      if(z > b2[0] + b2[1] + b2[2] && p2[2]!=0){
	cout << "grün" << '\t' << "Urne 4" << '\n';
      }
      
      if(z < b2[0] && p2[3]!=0){
	cout << "blau" << '\t' << "Urne 1" << '\n';
      }
      if(z < b2[0] + b2[1] && z > b2[0] && p2[3]!=0){
	cout << "blau" << '\t' << "Urne 2" << '\n';
      }
      if(z < b2[0] + b2[1] + b2[2] && z > b2[0] + b2[1] && p2[3]!=0){
	cout << "blau" << '\t' << "Urne 3" << '\n';
      }
      if(z > b2[0] + b2[1] + b2[2] && p2[3]!=0){
	cout << "blau" << '\t' << "Urne 4" << '\n';
      }
      cout << b2[0]<< '\t' << b2[1] << '\t' << b2[2]  << '\t'<< b2[3] << '\n';
   }
  }
  return 0;
}

