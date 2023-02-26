#include <iostream>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define lambda 5
#define alpha 0.03
#define h 0.001

using namespace std;
void kstep (double[6],double[12]);
void timestep (double[6],double [12]);
double xstep (double[6]);
double ystep (double[6]);
double zstep (double[6]);
int t;

int main()
{
  double k[12]={0,0,0,0,0,0,0,0,0,0,0,0};
  double x[6]={20,-5,10,0,0,0};
  for(int transient=0;transient<1000;transient++){	  
	timestep(x,k);
	for(int i=0;i<3;i++){
	  x[i]=x[i+3];
	}
  }	  	
  for(int t=0;t<1000000;t++){
		timestep(x,k);
		for(int i=0;i<3;i++){
		  x[i]=x[i+3];
		}
  	cout << x[0] << '\t' << x[1] << '\t' << x[2] << '\n';
  }
  return 0;
}

void timestep (double *x,double *k)
{
  kstep(x,k);
  for(int i=0;i<3;i++){
     x[i+3]=x[i]+h*(k[0+i*4]+2*(k[1+i*4]+k[2+i*4])+k[3+i*4])/6.0;
  }
}

void kstep (double *x,double *k){

     k[0]=xstep(x);
     k[4]=ystep(x);
     k[8]=zstep(x);
     double xa[3]={x[0]+h/2*k[0],x[1]+h/2*k[4],x[2]+h/2*k[8]};
     k[1]=xstep(xa);
     k[5]=ystep(xa);
     k[9]=zstep(xa);
     double xb[3]={x[0]+h/2*k[1],x[1]+h/2*k[5],x[2]+h/2*k[9]};
     k[2]=xstep(xb);
     k[6]=ystep(xb);
     k[10]=zstep(xb);
     double xc[3]={x[0]+h*k[2],x[1]+h*k[6],x[2]+h*k[10]};
     k[3]=xstep(xc);
     k[7]=ystep(xc);
     k[11]=zstep(xc);
}

double xstep(double *x){
  
  return (x[1]);
}

double ystep(double *x){

  return (x[0]*(1-x[2])-lambda*x[1]);
}

double zstep(double *x){

  return (-alpha*x[2]+x[0]*x[0]);
}
