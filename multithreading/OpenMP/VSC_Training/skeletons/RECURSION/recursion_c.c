#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1000000

double opt[N+1];

int main() {
    const double up = 1.00001;
    double Sn = 1.0;
    int n;

    for (n=0; n<=N; ++n) {
      opt[n] = Sn;
      Sn *= up;     
    }

    printf("Result is %12.5f\n",Sn);
}
