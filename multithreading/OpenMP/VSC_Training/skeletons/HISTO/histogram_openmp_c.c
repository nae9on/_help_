#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timing.h"

int main() {
  unsigned int seed = 123;
  long int i,k,me;
  short int ir[10000];
  double wcstart, wcend, ct;
  long int hist[16];
  for(i=0; i<16; ++i) 
    hist[i]=0;
  timing(&wcstart, &ct);
#pragma omp parallel private(seed,i,k,me)
  { 
    me = omp_get_thread_num();
    seed = 123 + 159*me;
// cannot exactly reproduce serial results
// but with fixed thread number results should always be the same
// between runs
    for (k=0; k<100000; ++k) {
#pragma omp for
      for (i=0; i<10000; ++i) {
        ir[i] = rand_r(&seed) & 0xf;
      }
#pragma omp master
      for (i=0;i<10000; ++i) {
        hist[ir[i]]++;
      }
#pragma omp barrier
// barrier prevents ir from being modified before hist update is done
    }
  }
  timing(&wcend, &ct);
  for(i=0; i<16; ++i) {
    printf("hist[%li]=%li\n",i,hist[i]);
  }
  printf("Time: %12.5f\n",wcend-wcstart);
}
