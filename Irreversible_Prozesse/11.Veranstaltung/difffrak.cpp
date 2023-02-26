#include <iostream>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define L 3
#define N 10000
#define T 10000
using namespace std;

int check(int,int,int[L*L]);

int main()
{
  int seed=14;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  int generator[L*L];
  int x[N];
  int xstart,ystart;
  int y[N];
  int sum;
  double msd,z;
  /*for (int i=0;i<L;i++){
    	for (int j=0;j<L;j++){
      	cout << "Geben Sie die "<< "(" << i << "," << j << ")-Komponente des Generators ein:" << '\n';
      	cin >> generator[i*L+j];
   	}
  }*/
  generator[0*L+0]=1;
  generator[0*L+1]=1;
  generator[0*L+2]=1;
  generator[1*L+0]=0;
  generator[1*L+1]=1;
  generator[1*L+2]=1;
  generator[2*L+0]=0;
  generator[2*L+1]=1;
  generator[2*L+2]=0;
  for(int i=0;i<N;i++){
  	x[i]=1000000;
  	y[i]=1000000;
  		
  }
  while(check(x[0],y[0],generator)==0){
		for(int j=0;j<N;j++){
			x[j]++;
			y[j]++;
		}
  }
  xstart=x[0];
  ystart=y[0];
  for(int t=0;t<T;t++){
  	for(int i=0;i<N;i++){
		z= gsl_rng_uniform(rng);
		if(z < 0.25){
			if(check(x[i]-1,y[i],generator)){
				x[i]--;
			}
		}
		if(z > 0.25 && z < 0.5){
			if(check(x[i]+1,y[i],generator)){
				x[i]++;
			}
		}
		if(z > 0.5 && z < 0.75){
			if(check(x[i],y[i]-1,generator)){
				y[i]--;
			}
		}
		if(z > 0.75){
			if(check(x[i],y[i]+1,generator)){
				y[i]++;
			}
		}	
	}
	sum=0;
	for(int i=0;i<N;i++){
		sum=sum+(x[i]-xstart)*(x[i]-xstart)+(y[i]-ystart)*(y[i]-ystart);
	}
	msd= (double) sum/N;
	cout << t << '\t' << msd <<'\n';
  }
  return 0;
}

int check(int x,int y,int *generator){
  int it,i,j;
  if(x > y) {
    it= static_cast <int>(log(x)/log(L));
  }
  else {
    it= static_cast <int>(log(y)/log(L));
  }
  
  while(it >= 0){
   i= static_cast <int> (x/(pow(L,it))) % L;
    j= static_cast <int> (y/(pow(L,it))) % L;
    if(generator[i*L+j] == 0) {
    return 0;
    }
    if (generator[i*L+j] > 0) {
      it--;
    }
  }
  return 1;
}
