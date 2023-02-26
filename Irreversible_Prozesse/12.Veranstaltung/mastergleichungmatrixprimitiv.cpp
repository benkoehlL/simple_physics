#include <iostream>
#include <time.h>
#define T 1000000000
using namespace std;

int main()
{
  clock_t time;
  time=clock();
  double P[2][3];
  P[0]={0.25,0.25,0.5};
  double gamma[3*3]={0.5,0.5,0,0.5,0,0.5,0,0.5,0.5};
  for(int t=0;t<T;t++)
  {
    for(int i=0;i<3;i++)
    {
      double sum=0;
      for(int j=0;j<3;j++)
      {
	sum+=P[0][j]*gamma[i*3+j];
      }
      P[1][i]=sum;
    }
    for(int i=0;i<3;i++)
    {
      P[0][i]=P[1][i];
    }
  }
  time=clock()-time;
  cout << '\t' << P[0][0] << '\t' <<  P[0][1] << '\t' << P[0][2] << '\t' << time << '\n';
  return 0;
}

