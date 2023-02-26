#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>
#include <iostream>

using namespace std;

double zufall(double, double);
double p(double);
double f(double);
double pi =M_PI;

int main()
{
  double lambda=1.,x1,x2,y1,y2,z;
  int histo[10000],index,seed=14,i;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  int num2=gsl_rng_uniform_int(rng,5);
  
  for(i=0;i<10000;i++)
  {
    histo[i]=0;
  }
  for (i=0;i<1000000;i++)
  {
//    x2=sqrt(-2 * log(x1)) * sin(2*pi*x2);
    y1=zufall(gsl_rng_uniform(rng), gsl_rng_uniform(rng));
//    y2=sqrt(-2 * log(x1)) * sin(2*pi*x2);
    z = gsl_rng_uniform(rng)*f(y1);
    while (z>p(y1))
    {
      y1=zufall(gsl_rng_uniform(rng), gsl_rng_uniform(rng));
      z = gsl_rng_uniform(rng)*f(y1);
    }
    index = 5000 + (int) (100*y1); 
    if(index<10000)
    {
      histo[index]++;
    }
  }
  for (i=0;i<10000;i++)
  {
    cout << (i-5000)/100. << '\t' <<  histo[i] << '\n';
  }
  return 0;
}

double zufall(double x1, double x2){
  
  return sqrt(-2 * log(x1)) * cos(2*pi*x2);
}

double p(double x){
   return 4/(5*sqrt(pi))*(exp(-(x-1)*(x-1))+exp(-((4*x+0.5)*(4*x+0.5))));;
}

double f(double x){
  return 2/(sqrt(pi))*exp(-0.5*x);
}