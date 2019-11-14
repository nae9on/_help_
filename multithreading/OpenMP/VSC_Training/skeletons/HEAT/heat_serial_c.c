//  Serial C version
//  Numerical Solution of heat conduction equation in 
//  two dimensions
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#include "timing.h"

#define min(A,B) ((A) < (B) ? (A) : (B))
#define max(A,B) ((A) > (B) ? (A) : (B))

const int imax = 200;
const int kmax = 200;
const int itmax = 100000;
//const int imax = 20;
//const int kmax = 11;
//const int itmax = 20000;

double dwalltime();
void print_field(double **phi, int imax, int kmax);


int main()
{
  double eps = 1.0e-08;
  double **phi, **phin;
  double dx,dy,dx2,dy2,dx2i,dy2i,dt,dphi,dphimax;
  double mflops, ti, ti2, cti;
  int i,k,it;

  phi = malloc((imax+1)*sizeof(void *)); 
  phin = malloc(imax*sizeof(void *)); 
  for (i=0; i<=imax; i++) phi[i] = malloc((kmax+1)*sizeof(double));
  for (i=0; i<imax; i++) phin[i] = malloc((kmax)*sizeof(double));

  dx=1.0/kmax;
  dy=1.0/imax;
  dx2=dx*dx;
  dy2=dy*dy;
  dx2i=1.0/dx2;
  dy2i=1.0/dy2;
  dt=min(dx2,dy2)/4.0;
/* start values 0.d0 */
  for (i=1;i<imax;i++)
  {
    for (k=0;k<kmax;k++)
    {
      phi[i][k]=0.0;
    }
  }
/* start values 1.d0 */
  for (i=0;i<=imax;i++)
  {
    phi[i][kmax]=1.0;
  }
/* start values dx */
  phi[0][0]=0.0;
  phi[imax][0]=0.0;
  for (k=1;k<kmax;k++)
  {
    phi[0][k]=phi[0][k-1]+dx;
    phi[imax][k]=phi[imax][k-1]+dx;
  }

  printf("\nHeat Conduction 2d\n");
  printf("\ndx = %12.4g, dy = %12.4g, dt = %12.4g, eps = %12.4g\n",
         dx,dy,dt,eps);

  if (imax < 21 && kmax < 21) {
    print_field(phi, imax, kmax);
  }

  timing(&ti, &cti);

/* iteration */
  for (it=1;it<=itmax;it++)
  {
    dphimax=0.;
    for (i=1;i<imax;i++)
    {
      for (k=1;k<kmax;k++)
      {
        dphi=(phi[i+1][k]+phi[i-1][k]-2.*phi[i][k])*dy2i
            +(phi[i][k+1]+phi[i][k-1]-2.*phi[i][k])*dx2i;
        dphi=dphi*dt;
        dphimax=max(dphimax,dphi);
        phin[i][k]=phi[i][k]+dphi;
      }
    }
/* save values */
    for (i=1;i<imax;i++)
    {
      for (k=1;k<kmax;k++)
      {
	phi[i][k]=phin[i][k];
      }
    }
    if(dphimax<eps) break;
  }

  timing(&ti2, &cti);
  ti=ti2 - ti;
  printf("\n%d iterations\n",it);
  if (imax < 21 && kmax < 21) {
    print_field(phi, imax, kmax);
  }
  printf("\nCPU time = %#12.4g sec\n",ti);
  mflops = 11.0 * (float) (kmax-1)*(float) (imax-1)*(float)it / 1.e6;
  printf("\nMFlop/s = %#12.4g \n",mflops/ti);

  for (i=0; i<=imax; i++) free(phi[i]);
  for (i=0; i<imax; i++) free(phin[i]);
  free(phi);
  free(phin);
}

void print_field(double **phi, int imax, int kmax) {
  int i, k, kk, kl, kkk, l;
  kl=6;
  kkk=kl-1;
  for (k=0; k<=kmax;k+=kl) {
    if(k+kkk > kmax) kkk=kmax-k;
    printf("columns %5i to %5i\n",k,k+kkk);
    for (i=0; i<=imax;i++) {
      printf("%5i ",i);
      for (l=0; l<kl; l++) {
        printf("%12.4g", phi[i][k+l]);
      }
      printf("\n");
    }
  }
}
