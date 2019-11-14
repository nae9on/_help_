#include <cmath>
#include <iostream>
#include <omp.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BILLION  1000000000L;

int main(){
	
std::cout<<"No of threads="<<omp_get_max_threads()<<std::endl;

const int size = 1000000;

double sinTable[size];

struct timespec start, stop;
double accum;

if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
perror( "clock gettime" );
exit( EXIT_FAILURE );
}

for(int i = 0; i<100; i++)
{
    #pragma omp parallel for
    for(int n=0; n<size; ++n)
      {
       sinTable[n] = sqrt(std::sin(2 * M_PI * n / size));
       sinTable[n] = sqrt(std::sin(2 * M_PI * n / size));
       sinTable[n] = sqrt(std::sin(2 * M_PI * n / size));
       sinTable[n] = sqrt(std::sin(2 * M_PI * n / size));
      }  
}

if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
perror( "clock gettime" );
exit( EXIT_FAILURE );
}

accum = ( stop.tv_sec - start.tv_sec )
  + ( stop.tv_nsec - start.tv_nsec )
    / BILLION;

int Hours = accum/3600; 
int Minutes = (accum-Hours*3600)/60;
int Seconds = accum - Hours*3600 - Minutes*60;
std::cout<<"Elapsed time = "<<Hours<<":"<<Minutes<<":"<<Seconds<<"\n";

return( EXIT_SUCCESS );
}
