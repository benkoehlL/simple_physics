#include <iostream>
using namespace std;

#define N 30
#define J 1

void flip(bool[N], int); 
void print(bool[N]);

int main()
{
  bool state[N];
  int k=0;
  for(int i=0; i<N; i++){
    state[i]=0;
  }
 // cout << "Der Grundzustand ist: ";
  print(state);
  while(k<N){
    k=0;
    if(state[k]==0){
	    flip(state,k);
	    print(state);
	    k++;
    }
    else{
      while(state[k]==1){
          flip(state,k);
          k++;
      }
      flip(state,k);
      print(state);
    }
  }
  cout << '\n';
  return 0;
}

void flip(bool *state, int i){
  state[i] = (!state[i]);
}

void print(bool *state){
  for(int i = 0 ; i < N ; i++){
    if(state[i]){
      cout << "1";
    }
    else{
      cout << "0";
    }
  }
  cout <<'\n';
}
