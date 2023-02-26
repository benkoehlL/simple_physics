#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

#define N 3
#define J 1
#define numberofstates 8

void flip1(bool[numberofstates*(N+1)], int, int);
void flip2(bool[numberofstates*(N+1)], int, int, int);
void copy(bool[numberofstates*(N+1)],int);
void copy(bool[numberofstates*(N+1)],int,bool[N+1]);
void print(bool[numberofstates*(N+1)],int);
int jstatenumber(bool[numberofstates*(N+1)],int,int);

int main()
{
  bool states[numberofstates*(N+1)] = {0};
//bool statei[N+1], statej[N+1];
  double Hamilton[numberofstates*numberofstates] = {0};
/*for(int i=0; i<numberofstates; i++){
    for(int j=0; j< N+1; j++){
      states[(N+1)*i + j]=0;
    }
  }*/
  int k = 0;
  int n = 1;
  while(k<N && n < numberofstates){
    k=0;
    if(states[k + n * (N+1)]==0 && k < N && n< numberofstates){
	    flip1(states,k,n);
	    copy(states,n);
	    n++;
	    k++;
    }
    else{
      while(states[k + n * (N+1)]==1 && k < N){
	flip1(states,k,n);
	k++;
      }
      flip1(states,k,n);
      copy(states,n);
      n++;
    }
  }
  for(n=0; n<numberofstates; n++){
    for(k=0; k<N; k++){
      if(states[n*(N+1) + k] == states[n*(N+1) + (k+1)%N]){
	Hamilton[n*(numberofstates+1)] = Hamilton[n*(numberofstates+1)] + 0.25;
      }
      else{
	Hamilton[n*(numberofstates+1)] = Hamilton[n*(numberofstates+1)] - 0.25;
	Hamilton[(jstatenumber(states,n,k)) * numberofstates + n] = 0.5;
	//Hamilton[(jstatenumber(states,n,k)) + n*(numberofstates)] = 0.5;
	}
    }
  }
  cout << "Der Hamiltonian in Polarisationsdarstellung lautet: " << '\n' << '\n';
  for(int i=0; i<numberofstates; i++){
    for(int j=0; j< numberofstates; j++){
      cout << Hamilton[numberofstates*i + j] << '\t';
    }
    cout << '\n' << '\n';
  }
  return 0;
}

void flip1(bool *state, int i, int n){
  if(i==0){
    state[n*(N+1)]= (!state[n*(N+1)]);
    state[n*(N+1)+N]=(!state[n*(N+1)+N]);
  }
  else{
    state[n*(N+1)+i]= (!state[n*(N+1)+i]);
  }
}

void flip2(bool *state, int i, int j, int n){
  if(i==0){
    state[n*(N+1)]= (!state[n*(N+1)]);
  }
  else{
    state[n*(N+1)+i]= (!state[n*(N+1)+i]);
  }
  if(j==0){
    state[n*(N+1)]= (!state[n*(N+1)]);
  }
  else{
    state[n*(N+1)+j]= (!state[n*(N+1)+j]);
  }
}

void copy(bool *state,int n){
  for(int i=0; i<N+1; i++){
    state[(n+1)*(N+1)+i]=state[n*(N+1)+i];
  }
}

void copy(bool *states,int n, bool *state){
  for(int i=0; i<N+1; i++){
    state[i] = states[(N+1)*n + i];
  }
}

void print(bool *states, int n){
  for(int j=0; j< N+1; j++){
      cout << states[(N+1)*n + j];
  }
    cout << '\n';
}

int jstatenumber(bool *states, int n, int k){
  if(states[n*(N+1) + k] && states[n*(N+1) + k+1]){
    return(n - (pow(2,(k+1)%N)+pow(2,k%N)));
  }
  if(states[n*(N+1) + k] && !(states[n*(N+1) + k+1])){
    return(n + (pow(2,(k+1)%N)-pow(2,k%N)));
  }
  if(!(states[n*(N+1) + k]) && states[n*(N+1) + k+1]){
    return(n - (pow(2,(k+1)%N)-pow(2,k%N)));
  }
  else{
    return(n + pow(2,(k+1)%N)+ pow(2,k%N));
  }
}