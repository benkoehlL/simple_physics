#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <iostream>

using namespace std;

int main()
{
  int seed=14;
  gsl_rng *rng;
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng,seed);
  double num1=gsl_rng_uniform(rng);
  int num2=gsl_rng_uniform_int(rng,5);
  cout << num1 << '\n' << num2 << '\n';
  return 0;
}
