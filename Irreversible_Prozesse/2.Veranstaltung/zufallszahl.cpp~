#include <iostream>
using namespace std;
class LCM{

  public:
  
   unsigned int zustand;
   static const unsigned int a=5;
   static const unsigned int c=0;
   static const int m=127;

  
  LCM(unsigned int s){
    zustand=s;
  }
//normal :
    int rand() {
      
    zustand=(a*zustand+c) % m;
    return zustand;
    }
};
  
class shuffle{
  
  private:
    
  LCM rnd;
  int feld[1000];
  int index;
  
  public:
  
  shuffle(int s) :  rnd(s){
    
    for(int j=1;j<1000;j++)
    {
    feld[j]=rnd.rand();
    }
    index = rnd.rand();
  }
  
  int rand() {
    int i = (int) 1000*index/(127.0);
    
    index = feld[i];

    feld[i]= rnd.rand();
    return index;
    
  }
  
  
};
    

int main()
{
  shuffle random(13);
  int seed=15;
  
  unsigned int I0=random.rand();
  unsigned int In=random.rand();
  unsigned int p=1;
  
  
// while(In!=I0)
//  {
//    In=random.rand();
//    p++;
//  }
  
//  cout << p <<'\n';

  shuffle random2(seed);
  
  int i=0;
  
  while (i<4000)
  {
    cout << random2.rand() << '\t' << random2.rand() << '\n';
    i++;
  }
}
