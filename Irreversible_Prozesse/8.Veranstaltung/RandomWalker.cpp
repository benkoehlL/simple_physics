#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#define N 100

using namespace std;


int main()
{
  
  double w[N][3];
  double p[N][2];
  double T;
  double Is;
  double Ir;
  double It;
  double ir;
  double q;

  
  T= 100000;
  q= 0.999999;
  for(int j=0;j<N;j++)
    {
      p[j][0]= 0;
      p[j][1]= 0;
    }
    
  p[N/2][0]= 1;

  for(int k= 0;k<N;k++)
    {
      for(int i= 0;i<3;i++)
	{
	  w[k][i]= 1./3.;
	}
    }
    
  w[0][0]= 0;
  w[0][1]= 2./3.;
  w[N-1][0]= 2./3.;
  w[N-1][2]= 0;


  for(int t= 1;t<T;t++)
    {
      for(int i=1;i<N-1;i++)    
	{
	  p[i][1]= p[i][0] * w[i][1] + p[i-1][0] * w[i][0] + p[i+1][0] * w[i][1];
	}
	
      p[0][1]= p[0][0] * 2./3. +p[1][0] * 1./3.;
      p[N-1][1]= p[N-1][0] * 2./3. + p[N-2][0] * 1./3.;
      
      for(int i=0;i<N;i++)
	{
	  p[i][0]=p[i][1];
	}
      
      Is=0;
      ir=0;
      
      for(int i= 0;i<N;i++)
	{
	  if(p[i][1]!= 0.)
	    {
	    Is= Is + p[i][1] * log(p[i][1]);
	    }
	  ir= ir + pow(p[i][1],q);
	  }
      Ir= 1./(q-1) * log(ir);
      It= 1./(1-q) * (1-ir);
      
      cout << t << '\t' <<  Is  << '\t' << Ir << '\t' << It <<  '\n';      
    }
    
  
  return 0;
}