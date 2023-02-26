#include <iostream>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define a 1.013
#define b -0.011
#define c 0.02
#define d 0.96
#define e 0
#define f 0.01
#define g 1
#define u 0.05
#define j 0.05



#define h 0.01

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
  double x[6]={0.1,0.5,0.2,0,0,0};
  /*for(int transient=0;transient<100000;transient++){	  
	timestep(x,k,c);
	for(int i=0;i<3;i++){
	  x[i]=x[i+3];
	}
  }*/	  	
  for(int t=0;t<3000000;t++){
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
  
  return ((x[0]-a*x[1])*cos(x[2])-b*x[1]*sin(x[2]));
}

double ystep(double *x){

  return (sin(x[2])*(c*x[1]+x[0])+d*x[1]*cos(x[2]));
}

double zstep(double *x){

  return (e+f*x[2]+g*atan((1.-u)/(1.-j)*x[0]*x[1]));
}
