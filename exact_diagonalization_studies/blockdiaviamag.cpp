#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

using namespace std;

#define N 4
#define J 1
#define numberofstates 16

void flip1(bool[numberofstates*(N+1)], int, int);
void flip2(bool[numberofstates*(N+1)], int, int, int);
int find(bool[numberofstates*(N+1)],int[numberofstates],int,int);
int numbnry(bool[numberofstates*(N+1)],int);
void copy(bool[numberofstates*(N+1)],int);
void copy(bool[numberofstates*(N+1)],int,bool[N+1]);
void print(bool[numberofstates*(N+1)],int);
int fak(int);
int jstatenumber(bool[numberofstates*(N+1)],int,int);

int main()
{
  bool states[numberofstates*(N+1)] = {0};
  int helparray[numberofstates];
  int mstatenumber[N+1] = {0};
  vector<vector<int> > magnetordered;
  vector<double> moHamilton;
  magnetordered.resize(N+1);
  double Hamilton[numberofstates*numberofstates] = {0};
  int k = 0;
  int n = 1;
  int m = 0;
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
    m=0;
    for(k=0; k<N; k++){
      m = m + states[n*(N+1) + k];
    }
    magnetordered[m].push_back(n);
    mstatenumber[m] += 1;
  }
  
  /*for(int i=0; i< N+1; i++){
    for(int j=0; j< int(fak(N)/(fak(i)*fak(N-i))); j++){
      cout << magnetordered[i][j] << '\t';
    }
    cout <<'\n';
  }*/
  
  /*for(int i=0; i<numberofstates; i++){
    cout << "Der Zustand ";
    print(states,i);
    cout << " entspricht " << numbnry(states,i) << " in Binaerdarstellung." << '\n';
  }*/
  cout << '\n';
  for(int a=0; a<N+1; a++){   
    moHamilton.resize(int(fak(N)/(fak(a)*fak(N-a)))*int(fak(N)/(fak(a)*fak(N-a))));
    for(int i=0; i< int(fak(N)/(fak(a)*fak(N-a))); i++){
      for(int j=0; j<int(fak(N)/(fak(a)*fak(N-a))); j++){
	moHamilton[i*int(fak(N)/(fak(a)*fak(N-a)))+j] = 0;
      }
    }
    
    for(int i=0; i< int(fak(N)/(fak(a)*fak(N-a))); i++){
      helparray[i] = magnetordered[a][i];
    }
    for(m=0; m< int(fak(N)/(fak(a)*fak(N-a))); m++){
      for(k=0; k<N; k++){
	if(states[helparray[m]*(N+1) + k] == states[helparray[m]*(N+1) + (k+1)%N]){
	  moHamilton[m*(int(fak(N)/(fak(a)*fak(N-a)))+1)] = moHamilton[m*(int(fak(N)/(fak(a)*fak(N-a)))+1)] + 0.25;
	}
	else{
	  moHamilton[m*(int(fak(N)/(fak(a)*fak(N-a)))+1)] = moHamilton[m*(int(fak(N)/(fak(a)*fak(N-a)))+1)] - 0.25;
	  moHamilton[int(fak(N)/(fak(a)*fak(N-a))) * find(states,helparray,jstatenumber(states,helparray[m],k),int(fak(N)/(fak(a)*fak(N-a)))) + m] = 0.5;
	 // cout << find(states,helparray,jstatenumber(states,helparray[m],k),int(fak(N)/(fak(a)*fak(N-a)))) << '\n';
	}
      }
    }
    for(int i=0; i< int(fak(N)/(fak(a)*fak(N-a))); i++){
      for(int j=0; j< int(fak(N)/(fak(a)*fak(N-a))); j++){
	cout << moHamilton[int(fak(N)/(fak(a)*fak(N-a)))*i + j] << '\t';
      }
      cout << '\n';
    }
    cout << '\n' << '\n';
  }
/*  for(n=0; n<numberofstates; n++){
    for(k=0; k<N; k++){
      if(states[n*(N+1) + k] == states[n*(N+1) + (k+1)%N]){
	Hamilton[n*(numberofstates+1)] = Hamilton[n*(numberofstates+1)] + 0.25;
      }
      else{
	Hamilton[n*(numberofstates+1)] = Hamilton[n*(numberofstates+1)] - 0.25;
	Hamilton[(jstatenumber(states,n,k)) * numberofstates + n] = 0.5;
	}
    }
  }
  cout << "Der Hamiltonian in Polarisationsdarstellung lautet: " << '\n' << '\n';
  for(int i=0; i<numberofstates; i++){
    for(int j=0; j< numberofstates; j++){
      cout << Hamilton[numberofstates*i + j] << '\t';
    }
    cout << '\n' << '\n';
  }*/
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

int find(bool *states, int *basis, int statetofind, int M){
  int bmin = 1;
  int bmax = M;
  int b;
  while(1){
    b = int(bmin + 0.5 * (bmax - bmin));
    /*cout << "Ich suche den Zustand ";
    print(states,statetofind);
    cout << '\n';*/
    if(numbnry(states,statetofind) < numbnry(states,basis[b])){
      //cout << numbnry(states,statetofind) << " < " << numbnry(states,basis[b]) << '\n';
      bmax = b - 1;
    }
    else if(numbnry(states,statetofind) > numbnry(states,basis[b])){
      //cout << numbnry(states,statetofind) << " > " << numbnry(states,basis[b]) << '\n';
      bmin = b + 1;
    }
    else{
    /*cout << "Ich habe den Zustand ";
    print(states,basis[b]);
    cout << " gefunden." << '\n';*/
    return b;
    }
    /*if(bmin > bmax){
      return -1:
    }*/
  }
}

/*int find(bool *states, int *magorderedstates, int jstate, int m){
  int found=-1;
  cout << "Ich suche den Zustand ";
  print(states,jstate);
  cout << '\n';
  for(int j=0; j<m; j++){
    if(numbnry(states,jstate) == numbnry(states,magorderedstates[j])){
      found = j;
      }
  }
  cout << "Ich habe den Zustand ";
  print(states,magorderedstates[found]);
  cout << " gefunden. " << '\n';
  return found;
}*/
    
int numbnry(bool *states, int n){
  int bin = 0;
  for(int i=0; i<N; i++){
    bin += states[n*(N+1) + i] * pow(2,i);
  }
  return bin;
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
  for(int j=0; j<N; j++){
      cout << states[(N+1)*n + j];
  }
   // cout << '\n';
}

int fak(int n){
  int fakul=1;
  for(;n>0;n--){
    fakul *= n;
  }
  return fakul;
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