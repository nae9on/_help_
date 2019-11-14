#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define DIM 4
int isz[] = { 1000, 2000, 4000, 8000 };

void mvm1(const double *a, const double *x, double *r, int n) {
  int j, k;
#pragma omp parallel for
  for (j=0; j<n; j++) {
    r[j] = 0.0;
    for (k=0; k<n; k++) {
       r[j] += a[k*n+j] * x[k];
    }
  }
}

void mvm2(const double *a, const double *x, double *r, int n) {
  int j, k;
#pragma omp parallel
  {
#pragma omp for
    for (j=0; j<n; j++) {
       r[j] = 0.0;
    }
#pragma omp for reduction(+:r[0:n])
    for (k=0; k<n; k++) {
      for (j=0; j<n; j++) {
         r[j] += a[k*n+j] * x[k];
      }
    }
  }
}

// Use following version for icc 15, 16, which do not yet 
// support array sections
/*
void mvm2(const double *a, const double *x, double *r, int n) {
  int j, k;
  for (j=0; j<n; j++) {
     r[j] = 0.0;
  }
#pragma omp parallel 
  {
    double s[n];
    for (j=0; j<n; j++) {
       s[j] = 0.0;
    }
#pragma omp for 
    for (k=0; k<n; k++) {
      for (j=0; j<n; j++) {
         s[j] += a[k*n+j] * x[k];
      }
    }
#pragma omp critical
    {
      for (j=0; j<n; j++) {
        r[j] += s[j];
      }
    }
  }
}
*/

int main() {
  int nt = 1;
  int in,it,j,k,n,nit;
  double *a, *col, *x, *r;
  double ops,ti,csum;

#pragma omp parallel
#pragma omp master
  nt = omp_get_num_threads();

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

     ops = 2 * (double) (n) * (double) (n);
     ti = omp_get_wtime();
     for (it=0; it<nit; it++) {
//        mvm1(a,x,r,n);
        mvm2(a,x,r,n);
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
