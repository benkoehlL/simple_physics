#include <iostream>
using namespace std;

#define N 10
#define J 1

void flip(bool[N+1], int); 

int main()
{
  int k;
  bool state[N+1];
  double H[N*N];
  for(int i = 0 ; i < N ; i++){
    cout << "Die Orientierung des " << i+1 << "ten Spinplatzes eingeben (0 für down und Sonstiges für up):" << '\n';
    cin >> k;
    if(k){
      state[i] = 1;
    }
    else{
      state[i] = 0;
    }
    cout << '\n';
  }
  state[N] = state[0];
  cout << "Der Zustand ist: ";
  for(int i = 0 ; i < N ; i++){
    if(state[i]){
      cout << "1";
    }
    else{
      cout << "0";
    }
  }
  cout << '\n';
  cout << "Welcher Spin soll gedreht werden? ";
  cin >> k;
  flip(state,k-1);
  cout << "Der Zustand ist nun: ";
  for(int i = 0 ; i < N ; i++){
    if(state[i]){
      cout << "1";
    }
    else{
      cout << "0";
    }
  }
  cout <<'\n';
  return 0;
}

void flip(bool *state, int i){
  state[i]= (!state[i]);
}