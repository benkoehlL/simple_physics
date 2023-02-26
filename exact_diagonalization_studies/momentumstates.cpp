#include <iostream>
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <complex>

using namespace std;

#define N 3
#define J 1
#define numberofstates 8

void copy(bool[numberofstates*(N+1)],int);
void copy(bool[numberofstates*(N+1)],int,bool[N+1]);
void copy(bool[N+1],bool[N+1]);
void print(bool[numberofstates*(N+1)],int);
void flip1(bool[numberofstates*(N+1)], int, int);
int numbnry(bool[numberofstates*(N+1)],int);
int fak(int);
int magnetisation(bool[numberofstates*(N+1)],int);
void cyclebits(bool[(N+1)]);
int checkstate(bool[numberofstates*(N+1)],int,int);
void representative(bool states[numberofstates*(N+1)],int,int[2]);
int find(bool[numberofstates*(N+1)],int[numberofstates],int,int);

int main(){
  bool states[numberofstates*(N+1)] = {0};
  int mstatenumber[N+1] = {0};
  vector<vector<int> > magnetordered;
  vector<int> momentumstate;
  vector<int> Rlist;
  vector<complex<double> > Hamilton;
  int k = 0;
  int n = 1;
  int m = 0;
  complex<double> I;
  I = -1;
  I = sqrt(I);
  int jstate;
  int helparray[numberofstates];
  bool help[N+1];
  int helprepresentative[2] = {0};
  magnetordered.resize(N+1);
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
  
/*Test, ob cycle funktioniert:
 * for(int a=0; a<N+1; a++){
    for(int i=0; i<int(fak(N)/(fak(a)*fak(N-a))); i++){
	helparray[i] = magnetordered[a][i];
	//cout << helparray[i] << '\t';
      }
      cout << '\n';
    for(m=0; m<int(fak(N)/(fak(a)*fak(N-a))); m++){
      copy(states,helparray[m],help);
      print (help,0);
      cout << '\n' << '\n';
      for(int j=0; j<N;j++){
	cyclebits(help);
	print(help,0);
	cout << '\n';
      }
      cout << '\n';
    }
    cout << '\n';
  }
  */
  for(int a=0; a<N+1; a++){
    k = a;
    for(m=0; m<int(fak(N)/(fak(a)*fak(N-a))); m++){
      for(int i=0; i<int(fak(N)/(fak(a)*fak(N-a))); i++){
	helparray[i] = magnetordered[a][i];		
      }
      if(checkstate(states,helparray[m],k) >= 0){
	momentumstate.push_back(helparray[m]);
	Rlist.push_back(checkstate(states,helparray[m],k));
      }
    }
  }
  int M = Rlist.size();
  //cout << M << '\n';
  /*Die Repräsentanten ausgeben:
   *for(int i=0; i<momentumstate.size(); i++){
    print(states,momentumstate[i]);
    cout << '\n';
  }*/
/*  Die Periode der Zustände ausgeben:
 *  for(int i=0; i<Rlist.size(); i++){
      cout << "Der Zustand ";
      print(states,momentumstate[i]);
      cout << " hat die Periode " << Rlist[i] << '\n';
    }*/
 //Die Repräsentantensuchfunktion testen:
 /* for(n=0; n<numberofstates; n++){
    cout << "Zustand ";
    print(states,n);
    copy(states,n,help);
    representative(states,numbnry(help,0),helprepresentative);
    cout <<'\t' << "Repräsentant " << helprepresentative[0] << '\t';
    print(states,helprepresentative[0]);
    cout << '\n';
  }/*
    
    /*for(int i=0; i<N; i++){
      flip1(states,i,n);
      flip1(states,i+1,n);
      print(states,n);
      cout << '\n';
      copy(states,n,help);
      flip1(states,i,n);
      flip1(states,i+1,n);
      representative(states,numbnry(help,0),helprepresentative);
      cout << helprepresentative[0] << '\t' << helprepresentative[1] << '\n';
    }*/
 /* Die Magnetisierungsfunktion testen:
  * for(n=0; n<numberofstates; n++){
   cout << "Der Zustand ";
   print(states,n);
   cout << " hat " << magnetisation(states,n) << " up-Spins." << '\n';
 }*/
 Hamilton.resize(M*M);
 for(n=0; n<M; n++){
   for(k=0; k<M; k++){
     Hamilton[M*n+k] = 0;
   }
 }
 for(int i=0; i<M; i++){
   helparray[i] = momentumstate[i];
 }
 for(n=0; n<M; n++){
  for(k=0; k<N; k++){
    if(states[helparray[n]*(N+1) + k] == states[helparray[n]*(N+1) + (k+1)%N]){
      Hamilton[n*(M+1)] = Hamilton[n*(M+1)] + 0.25;
    }
    else{
      Hamilton[n*(M+1)] = Hamilton[n*(M+1)] - 0.25;
     // print(states,helparray[n]);
     // cout << '\t' << k << '\t';
      flip1(states,k,helparray[n]);
      flip1(states,(k+1)%N,helparray[n]);
      copy(states,helparray[n],help);
     // print(help,0);
     // cout << '\t';
      flip1(states,k,helparray[n]);
      flip1(states,k+1,helparray[n]);
      representative(states,numbnry(help,0),helprepresentative);
     // cout << helprepresentative[0] << '\t';
     // print(states,helprepresentative[0]);
      cout << '\n';
      jstate = find(states,helparray,helprepresentative[0],M);
      if(find(states,helparray,helprepresentative[0],M)>=0){
	//cout << n << '\t' << jstate << '\t' << 0.5 * sqrt(double(Rlist[jstate])/Rlist[n]) * exp(2*M_PI*I*double(magnetisation(states,helparray[n]))*double(double(helprepresentative[1])/N)) << '\n';
	Hamilton[M*n+jstate] = Hamilton[M*n+jstate] + 0.5 * sqrt(double(Rlist[jstate])/Rlist[n]) * exp(2*M_PI*I*double(magnetisation(states,helparray[n]))*double(double(helprepresentative[1])/N));
	//Hamilton[M*jstate+n] = Hamilton[M*jstate+n] + 0.5 * sqrt(double(Rlist[jstate])/Rlist[n]) * exp(2*M_PI*I*double(magnetisation(states,helparray[n]))*double(double(helprepresentative[1])/N));
      }
    }
  }
 }
 
/* for(int i=0; i<M; i++){
   cout << find(states,helparray,i,M) << '\t' << i << '\n';
 }*/
 for(n=0; n<M; n++){
    for(k=0; k<M; k++){
      cout << Hamilton[M*n+k] << '\t';
    }
    cout << '\n';
 }
 cout << '\n';
 return 0;
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

void copy(bool *state, bool *help){
  for(int i=0; i<N+1; i++){
    help[i] = state[i];
  }
}

void print(bool *states, int n){
  for(int j=0; j< N; j++){
      cout << states[(N+1)*n + j];
  }
}

void flip1(bool *state, int i, int n){
  if(i%N==0){
    state[n*(N+1)] = (!state[n*(N+1)]);
    state[n*(N+1)+N] = (!state[n*(N+1)+N]);
  }
  else{
    state[n*(N+1)+i]= (!state[n*(N+1)+i]);
  }
}

int numbnry(bool *states, int n){
  int bin = 0;
  for(int i=0; i<N; i++){
    bin += states[n*(N+1) + i] * pow(2,i);
  }
  return bin;
}

int fak(int n){
  int fakul=1;
  for(;n>0;n--){
    fakul *= n;
  }
  return fakul;
}

int magnetisation(bool *states, int n){
  int m=0;
  for(int i=0; i<N; i++){
    m = m + states[n*(N+1)+i];
  }
  return m;
}

void cyclebits(bool *states){
  bool help[N+1] = {0};
  copy(states,help);
  for(int i=0; i<N; i++){
    states[i] = help[(i+1)];
  }
  states[N] = states[0];
}
 
int checkstate(bool *states, int n, int k){
  int R = -1;
  bool help[N+1];
  copy(states,n,help);
  for(int i=0; i<N; i++){
    cyclebits(help);
    if(numbnry(help,0) < numbnry(states,n)){
      //cout << "Zustand ";
      //print(help,0);
      //cout << " ist schon drin. " << '\n';
      return R;
    }
    if(numbnry(help,0) == numbnry(states,n)){
      //cout << "Zustand ";
      //print(help,0);
      //cout << " ist periodisch. " << '\n';
      //cout << "Periode  ist " << i+1 << '\n';
      if(k%int(double(N/(i+1))) != 0){
	cout << "Zustand ist inkompatibel. " << k%int(double(N/(i+1))) << '\n';
	return R;
      }
      R = i+1;
      return R;
    }
  }
}

void representative(bool *states, int statenumber, int *returnparameters){
  bool help[N+1];
  copy(states,statenumber,help);
  returnparameters[0] = numbnry(help,0);
  returnparameters[1] = 0;
  for(int i=1; i<N; i++){
    cyclebits(help);
  /*  print(help,0);
    cout << '\t' << numbnry(help,0) << '\n';
    */
    if(numbnry(help,0) < returnparameters[0]){
     // print(help,0);
     // cout << '\t' << numbnry(help,0) << '\n';
      returnparameters[0] = numbnry(help,0);
      returnparameters[1] = i;
    }
  }
}

int find(bool *states, int *basis, int statetofind, int M){
  int bmin = 1;
  int bmax = M;
  int b;
/*cout << "Ich suche den Zustand ";
  print(states,statetofind);
  cout << '\n';*/
  while(1){
    b = int(bmin + 0.5 * (bmax - bmin));
    if(numbnry(states,statetofind) < numbnry(states,basis[b])){
     // cout << numbnry(states,statetofind) << " < " << numbnry(states,basis[b]) << '\n';
      bmax = b - 1;
    }
    else if(numbnry(states,statetofind) > numbnry(states,basis[b])){
      bmin = b + 1;
     // cout << numbnry(states,statetofind) << " > " << numbnry(states,basis[b]) << '\n';
    }
    else{
     /* cout << "Ich habe den Zustand ";
      print(states,basis[b]);
      cout << " gefunden." << '\n';*/
      return b;
    }
    if(bmin > bmax && numbnry(states,statetofind) != numbnry(states,basis[0])){
      cout << "Kein solcher Zustand vorhanden." << '\n';
      return -1;
    }
  }
}