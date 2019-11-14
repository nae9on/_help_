#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define DIM 4
int isz[] = { 1000, 2000, 4000, 8000 };

void mvm(const double *a, const double *x, double *r, int n) {
  int j, k;
  for (j=0; j<n; j++) {
     r[j] = 0.0;
  }
  for (k=0; k<n; k++) {
    for (j=k; j<n; j++) {
       r[j] = r[j] + a[k*n+j] * x[k];
    }
  }
}

int main() {
  int nt = 1;
  int in,it,j,k,n,nit;
  double *a, *col, *x, *r;
  double ops,ti,csum;

  printf("Size  Threads  Time(s)   Perf(Mflop/s)   Checksum\n");
  for (in=0; in<DIM; in++) {
     n = isz[in];
     a = (double *) malloc(n*n*sizeof(double));
     x = (double *) malloc(n*sizeof(double));
     r = (double *) malloc(n*sizeof(double));

     for (k=0; k<n; k++) {
       x[k] = 0.02;
       for (j=0; j<n; j++) {
          a[k*n+j] = 1.0;
       }
     }
     nit = (20000/n)*(20000/n);
     if (nit < 1) nit = 1;

     ops = (double) (n+1) * (double) (n);
     ti = omp_get_wtime();
     for (it=0; it<nit; it++) {
        mvm(a,x,r,n);
     }
     ti = omp_get_wtime() - ti;

     csum = 0.0;
     for (j=0; j<n; j++) {
       csum += r[j];
       if (n < 11) printf("r[%2i] == %15.8e\n",j,r[j]);
     }

     printf("%4i   %3i  %12.3f  %7.1f   %15.8e\n",
           n,nt,ti,nit*ops/(1.0e6*ti),csum);

     free(a); free(x); free(r);
  }
}
