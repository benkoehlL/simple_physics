#include <iostream>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define a 0.1
#define b 0.2
#define h 0.001

using namespace std;
void kstep (double[6],double[12],double);
void timestep (double[6],double [12],double);
double xstep (double[6]);
double ystep (double[6]);
double zstep (double[6],double);
int t;

int main()
{
  double k[12]={0,0,0,0,0,0,0,0,0,0,0,0};
  //double c=14;
  for(double c=0.5;c<50;){
	  double x[6]={1,1,1,0,0,0};
	  t=0;
	  for(int transient=0;transient<100000;transient++){
	  
		timestep(x,k,c);
		for(int i=0;i<3;i++){
		  x[i]=x[i+3];
		}
	  }
	  while(t<300){
		  	
	  //for(int t=0;t<100000;t++){
		timestep(x,k,c);
	  	if(abs(x[0])>abs(x[3]) && x[0]>0){
	 		cout << c << '\t' << x[0] << '\n';
			t++;
			for(int step=0;step<1000;step++){
				timestep(x,k,c);
				for(int i=0;i<3;i++){
				  x[i]=x[i+3];
				}
			}
		}      
			for(int i=0;i<3;i++){
			  x[i]=x[i+3];
			}
		//cout << x[0] << '\t' << x[1] << '\t' << x[2] << '\n';
	  }
  c+=0.1;
  }
  return 0;
}

void timestep (double *x,double *k, double c)
{
  kstep(x,k,c);
  for(int i=0;i<3;i++){
     x[i+3]=x[i]+h*(k[0+i*4]+2*(k[1+i*4]+k[2+i*4])+k[3+i*4])/6.0;
  }
}

void kstep (double *x,double *k,double c){

     k[0]=xstep(x);
     k[4]=ystep(x);
     k[8]=zstep(x,c);
     double xa[3]={x[0]+h/2*k[0],x[1]+h/2*k[4],x[2]+h/2*k[8]};
     k[1]=xstep(xa);
     k[5]=ystep(xa);
     k[9]=zstep(xa,c);
     double xb[3]={x[0]+h/2*k[1],x[1]+h/2*k[5],x[2]+h/2*k[9]};
     k[2]=xstep(xb);
     k[6]=ystep(xb);
     k[10]=zstep(xb,c);
     double xc[3]={x[0]+h*k[2],x[1]+h*k[6],x[2]+h*k[10]};
     k[3]=xstep(xc);
     k[7]=ystep(xc);
     k[11]=zstep(xc,c);
}

double xstep(double *x){
  
  return (-(x[1]+x[2]));
}

double ystep(double *x){

  return (x[0]+a*x[1]);
}

double zstep(double *x,double c){

  return (b+(x[0]-c)*x[2]);
}





