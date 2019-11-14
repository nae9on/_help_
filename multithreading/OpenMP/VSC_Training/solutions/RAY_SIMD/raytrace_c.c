#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <string.h>
#include <stdlib.h>
#include "timing.h"

double objs[] = {
  0. ,0., -100.5, 10000., 0., 0., 0., 0.25,
  0.272166, 0.272166, 0.544331, .027777,
  0.643951, 0.172546, 0., .027777,
  0.172546, 0.643951, 0., .027777,
 -0.371785, 0.099620, 0.544331, .027777,
 -0.471405, 0.471405, 0., .027777,
 -0.643951,-0.172546, 0., .027777,
  0.099620,-0.371785, 0.544331, .027777,
 -0.172546,-0.643951, 0., .027777,
  0.471405,-0.471405, 0., .027777,
  4., 3., 2., 1., -4., 4., -3., 1., 5.
};

double *intersect(double x, double y, double z, double dx, double dy, double dz, double *maxp)
{
  int i;
  double *o = objs, *oo=0;
  double pmax = *maxp;
  double xx, yy, zz, b[11], t[11], tt;

#pragma omp simd private(xx, yy, zz)  
  for (i = 0; i < 11; i++)
    { 
      xx = o[4*i] - x; yy = o[4*i+1] - y; zz = o[4*i+2] - z;
      b[i] = xx * dx + yy * dy + zz * dz;
      t[i] = b[i] * b[i] - xx * xx - yy * yy - zz * zz + o[4*i+3];
    }

  for (i = 0; i < 11; i++)
    {
      if (t[i] >= 0) {
        tt = b[i]-sqrt(t[i]);
        if (tt >= 1e-6 && tt <= pmax) {
          oo = o + 4*i;
          pmax = tt;
        }
      }
    }
  *maxp = pmax;
  return oo;
}


double shade(double x, double y, double z, double dx, double dy, double dz, int de)
{
  double max = 1e6, c = 0, r[3], k, *o;
  double nx, ny, nz, ldx[3], ldy[3], ldz[3], rdx, rdy, rdz;
  int i;

  if (!(o = intersect(x, y, z, dx, dy, dz, &max)))
    return 0;
  x += max * dx; y += max * dy; z += max * dz;
  nx = x - *o++; ny = y - *o++; nz = z - *o++;
  r[0] = sqrt(nx * nx + ny * ny + nz * nz);
  r[1] = r[0]; r[2] = r[0];
  nx /= r[0]; ny /= r[0]; nz /= r[0];
  k = nx * dx + ny * dy + nz * dz;
  rdx = dx - 2 * k * nx; rdy = dy - 2 * k * ny; rdz = dz - 2 * k * nz;
  o = objs + 44;
#pragma omp simd
  for (i = 0; i < 3; i++)
    {  
      ldx[i] = *o++ - x; ldy[i] = *o++ - y; ldz[i] = *o++ - z;
      r[i] = sqrt(ldx[i] * ldx[i] + ldy[i] * ldy[i] + ldz[i] * ldz[i]);
      ldx[i] /= r[i]; ldy[i] /= r[i]; ldz[i] /= r[i];
    }
  for (i = 0; i < 3; i++)
    {
	if (intersect(x, y, z, ldx[i], ldy[i], ldz[i], &r[i]))
           continue; 
        if ((r[i] = ldx[i] * nx + ldy[i] * ny + ldz[i] * nz) < 0)
           continue;
        c += r[i];
        if ((r[i] = rdx * ldx[i] + rdy * ldy[i] + rdz * ldz[i]) > 0)
          c += 2 * pow(r[i], 15.);
    }
  if (de < 10)
    c += .5 * shade(x, y, z, rdx, rdy, rdz, de + 1);
  return c;
}


void calc_tile(int size, int xstart, int ystart, int tilesize, char* tile)
{
  double dx, dy, dz, c, r;
  int x, y, i;
  
  i=0;

  for (y = ystart; y < ystart+tilesize; y++)
  {
      double yy = 1. - y / (float)(size-1);
      dz = -2.72303                 + yy * 2.04606;
    for (x = xstart; x < xstart+tilesize; x++)
      {
        double xx = x / (float)(size-1);
        dx = -0.847569 - xx * 1.30741 - yy * 1.19745;
        dy = -1.98535  + xx * 2.11197 - yy * 0.741279;
        r = sqrt(dx * dx + dy * dy + dz * dz);
	c = 100 * shade(2.1, 1.3, 1.7, dx / r, dy / r, dz / r, 0);
	if (c < 0)
	  c = 0;
	if (c > 255)
	  c = 255;
	tile[i++]=c;
      }
  }
}

int main(int argc, char** argv)
{
  int size=2000,tilesize=200,xtiles,ytiles,xc,yc,count,tilebase,i;
  char *tile, *picture;
  double ws,we,cs,ce;

  if ((picture=(char*)malloc(size*size*sizeof(char)))==NULL)
    {
      fprintf(stderr,"Could not allocate picture memory!\n");
      exit(1);
    }
  for(i=0; i<size*size*sizeof(char); ++i)
     picture[i]=0;

  timing(&ws,&cs);
  
  /* number of tiles in x and y direction */
  xtiles=size/tilesize;
  ytiles=size/tilesize;
  
  count=0;
  if((tile=(char*)malloc(tilesize*tilesize*sizeof(char)))==NULL)
      {
	  fprintf(stderr,"Could not allocate tile memory!\n");
	  exit(1);
      }
  for(yc=0; yc<xtiles; yc++)
    for(xc=0; xc<ytiles; xc++)
      {
	/* calc one tile */
	calc_tile(size, xc*tilesize, yc*tilesize, tilesize, tile);
	/* copy to picture buffer */
	for(i=0; i<tilesize; i++)
	  {
	    tilebase=yc*tilesize*tilesize*xtiles+xc*tilesize;
	    memcpy((void*)(picture+tilebase+i*tilesize*xtiles),
		   (void*)(tile+i*tilesize),
		   tilesize*sizeof(char));
	  }
	count++;
      }
  free(tile);

  timing(&we,&ce);
  fprintf(stderr,"Time: %lf\n",we-ws);

  FILE *fd=fopen("result.pnm","w");
  fprintf(fd,"P5\n%d %d\n255\n",size,size);
  for(count=0; count<size*size; count++)
    fputc(picture[count],fd);
  fclose(fd);

  free(picture);
  exit(0);
}
