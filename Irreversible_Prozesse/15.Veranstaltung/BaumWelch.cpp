#include <iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define T 10

using namespace std;

int main()
{
  int seed=14;
  double z;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  double p1[3]={1,0,0};
  double b1[2];
  int beob[T];
  double sumab,sumphi,sumgam,sumgammod;
  double pn[3];
  double B1[6]={0.9,0.5,0.2,0.1,0.5,0.8};
  double A1[9]={0.5,0.25,0.25,0.375,0.125,0.375,0.125,0.625,0.375};
  double alpha1[3*T];
  double beta1[3*T];
  double Bneu[6]={0.5,0.5,0.5,0.5,0.5,0.5};
  double Aneu[9]={0.2,0.2,0.2,0.2,0.2,0.2,0.6,0.6,0.6};
  double pneu[3]={0,1,0};
  double phi[9][T];
  double gamma[3][T];
  for(int t=0;t<T;t++)
    {
      pn[0]=0;
      pn[1]=0;
      pn[2]=0;
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
      b1[0]=0;
      b1[1]=0;
      for(int i=0;i<2;i++)
      {
	for(int j=0;j<3;j++)
	{
	  b1[i]+=p1[j]*B1[i*3+j];
	}
      }
      z = gsl_rng_uniform(rng);
      if(b1[0]<z)
      {
	beob[t]=0;
      }
      else{
	beob[t]=1;
      }
      cout << '\t' << z << '\t' << beob[t] << '\n';
    }
    for(int i=0;i<3;i++){
      alpha1[i]=Bneu[3*i]*pneu[0]+Bneu[3*i+1]*pneu[1]+Bneu[3*i+2]*pneu[2];
    }
    for(int t;t<T;t++){
	
      for(int i=0;i<3;i++)
	  {
	    alpha1[t*3+i]=B1[beob[t]*3+i]*(A1[i*3+0]*alpha1[3*(t-1)]+A1[i*3+1]*alpha1[(t-1)*3+1]+A1[i*3+2]*alpha1[3*(t-1)+2]);
	  }
    }
      
    beta1[3*(T-1)]=1;
    beta1[3*(T-1)+1]=1;
    beta1[3*(T-1)+2]=1;
    for(int t=T-2;t>-1;t--)
    {
	for(int i=0;i<3;i++)
	{
	  beta1[t*3+i]=B1[beob[t+1]*3]*A1[i]*beta1[(t+1)*3]+B1[beob[t+1]*3+1]*A1[3+i]*beta1[(t+1)*3+1]+B1[beob[t+1]*3+2]*A1[6+i]*beta1[(t+1)*3+2];
	}
    }
    for(int t=0;t<T;t++){
      sumab=0;
      for(int i=0;i<2;i++){
	sumab+=alpha1[t]*beta1[t];
      }
      if(t<T-1){
	for(int i=0;i<3;i++){
	  for(int j=0;j<3;j++){
	      phi[3*i+j][t]=alpha1[j]*Aneu[3*i+j]*Bneu[3*beob[t+1]+j]*beta1[t+1]/sumab;
	  }
	}
      }
      else{
	for(int i=0;i<3;i++){
	  for(int j=0;j<3;j++){
	    phi[3*i+j][t]=alpha1[j]*Aneu[3*i+j]/sumab;
	  }
	}
      }
      for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
	  gamma[j][t]=0;
	  for(int k=0;k<2;k++){
	    gamma[j][t]+=phi[3*i+j][t];
	  }
	}
    for(int i=0;i<3;i++){
      pneu[i]=gamma[i][0];
    }
    for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){	    
	sumphi=0;
	sumgam=0;
	for(int t=0;t<T-1;t++){
	  sumphi+=phi[3*i+j][t];
	  sumgam+=gamma[j][t];
	}
	Aneu[3*i+j]=sumphi/sumgam;
	sumgam+=gamma[T-1];
	sumgammod=0;
	for(int k=0;k<2;k++){  
	  for(int t=0;t<T;t++){
	      if(beob[t]==k){
		sumgammod+=gamma[j][t];
	      }
	  }
	  Bneu[2*k+j]=sumgammod/sumgam;

	}
      }
    }
    cout << "A[0][0] = " << Aneu[0] << '\t' << "A[0][1] = " << Aneu[1] << '\t' << "A[0][2] = " << Aneu[2] << '\n';
    cout << "A[1][0] = " << Aneu[3] << '\t' << "A[1][1] = " << Aneu[4] << '\t' << "A[1][2] = " << Aneu[5] << '\n';
    cout << "A[2][0] = " << Aneu[6] << '\t' << "A[2][1] = " << Aneu[7] << '\t' << "A[2][2] = " << Aneu[8] << '\n';
    cout << "A[0][0] = " << Aneu[0] << '\t' << "A[0][1] = " << Aneu[1] << '\t' << "A[0][2] = " << Aneu[2] << '\n';
    cout << "A[1][0] = " << Aneu[3] << '\t' << "A[1][1] = " << Aneu[4] << '\t' << "A[1][2] = " << Aneu[5] << '\n';
    cout << "A[2][0] = " << Aneu[6] << '\t' << "A[2][1] = " << Aneu[7] << '\t' << "A[2][2] = " << Aneu[8] << '\n';
    cout << "B[0][0] = " << Bneu[0] << '\t' << "B[0][1] = " << Bneu[1] << '\t' << "B[0][2] = " << Bneu[2] << '\n';
    cout << "B[1][0] = " << Bneu[3] << '\t' << "B[1][1] = " << Bneu[4] << '\t' << "B[1][2] = " << Bneu[5] << '\n';
    cout << "pi1 = " << pneu[0] << '\t' << "pi2 = " << pneu[1] << '\t' << "pi3 = " << pneu[2] << '\n';
    
    
      
    return 0;
}

