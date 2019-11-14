#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1000000

double opt[N+1];

int main() {
    const double up = 1.00001;
    double Sn = 1.0;
    double origSn; 
    int n, lastn;

    origSn = Sn;
    lastn = -2;
#pragma omp parallel for firstprivate(lastn) lastprivate(Sn) 
    for (n=0; n<=N; ++n) {

	if ( lastn == n-1 ) { // still in same chunk?
	    Sn *= up;                          // yes: fast version
	} else {
	    Sn = origSn * pow(up, (double) n); // no: slow version
	}
	opt[n] = Sn;
	lastn = n;           // storing index
    }
    Sn *= up;

    printf("Result is %12.5f\n",Sn);
}
