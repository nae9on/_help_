#include <stdio.h>
#include <omp.h>
#include <unistd.h>

void f();

int main() {
  float ti;
  ti = omp_get_wtime();
#pragma omp parallel
  {
    f();
  } // end parallel
  ti = omp_get_wtime() - ti;
  printf("f took %8.3f seconds.\n",ti);
  return 0;
}

void f() {
  int me = 0;
#ifdef _OPENMP
  me = omp_get_thread_num();
#endif
  printf("Hello from thread %i\n", me);
  sleep( (unsigned int) me);
}
