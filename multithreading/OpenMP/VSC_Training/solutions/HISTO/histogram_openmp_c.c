#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timing.h"

int main() {
  unsigned int seed = 123;
  long int i,me;
  double wcstart, wcend, ct;
  long int hist[16];
  long int hist_glob[16];
  for(i=0; i<16; ++i) 
    hist_glob[i]=0;
  timing(&wcstart, &ct);
#pragma omp parallel private(seed,i,hist,me)
  { 
    me = omp_get_thread_num();
    seed = 123 + 159*me;
   for (i=0;i<16; ++i) {
     hist[i] = 0;
   }
// cannot exactly reproduce serial results
// but with fixed thread number results should always be the same
// between runs
#pragma omp for
   for (i=0; i<1000000000; ++i) {
     hist[rand_r(&seed) & 0xf]++;
   }
#pragma omp critical
   for (i=0;i<16; ++i) {
     hist_glob[i] += hist[i];
   }
// Note: array reduction not available in C
// So we need to do it manually
  }
  timing(&wcend, &ct);
  for(i=0; i<16; ++i) {
    printf("hist[%li]=%li\n",i,hist_glob[i]);
  }
  printf("Time: %12.5f\n",wcend-wcstart);
}
