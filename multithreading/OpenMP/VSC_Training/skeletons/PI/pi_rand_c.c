#include <stdio.h>
#include <stdlib.h>
#include "timing.h"

const long int n = 100000000;

const double pi_ref = 3.1415926535897932384626433;

int main(int argc, char** argv) {
  int i, i_inside;
  unsigned int iseed = 5;
  int ir1, ir2;
  double rd1, rd2, pi_approx;
  double t1, t2, ct1, ct2;

  timing(&t1, &ct1);
 
/* calculate pi from random numbers on a quarter circle */
  i_inside = 0;
  for (i=0;i<n;i++) {
    ir1 = rand_r(&iseed); ir2 = rand_r(&iseed);
    rd1 = (double) ir1 / (double) RAND_MAX; rd2 = (double) ir2 / (double) RAND_MAX;
    if ((rd1*rd1 + rd2*rd2) <= 1.0) i_inside++;
  }
  pi_approx = 4.0 * (double) i_inside / (double) n;

  timing(&t2, &ct2);
  printf( "computed  pi     = %19.16f\n", pi_approx );
  printf( "reference pi_ref = %19.16f\n", pi_ref );
  printf( "error= pi-pi_ref = %19.16f\n", pi_approx - pi_ref );
  printf( "CPU time         = %12.6f sec\n", ct2-ct1 );
  printf( "wall clock time  = %12.6f sec\n", t2-t1 );
  return 0;
}
