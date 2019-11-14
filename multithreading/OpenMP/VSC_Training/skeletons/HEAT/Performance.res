Results on a 2.6 Haswell node (two sockets, 14 cores per socket)

Size: 200 x 200
Intel Fortran 16.0.3 with AVX (but not AVX2)
V1:  standard solution
V3:  parallel region pulled outside iteration loop

Affinity: added settings
OMP_PLACES=cores(28)
OMP_PROC_BIND=true

Threads                  Mflop/s
               V1         v2+affinity   V3       V3+affinity  
--------------------------------------------------------------
  1           6790         6800        6800       6850
  2          12900        13000       13300      13600
  4          24500        24800       26400      26300
  7          30000        34000       34600      37500
 14          37000        42000       42700      44400
 21          35000        43000       39200      43200
 28           3830         3840        5400       6000

Results on a 2.7 Sandy Bridge node (two sockets, 8 cores per socket)

Size: 200 x 200
only SSE2 was used by 13.1 ifort
V1:   heat_omp.f90  "standard solution"
V2:   heat_omp.f90  collapse(2) added
V3:   heat_omp_tune1.f90 parallel region outside iteration loop



Threads                  Mflop/s
               V1         V2        V3 
-------------------------------------------------------------------------------
  1           5647       1679      5680
  2          10350       3261     11130
  4          18000       6118     19790
  8          20900      10060     24920
 16          23600      10690     26770

Rerun on a batch node with 2.3 GHz

export OMP_NUM_THREADS=16
export MP_TASK_AFFINITY=Core:16
poe bash

Serial version 3730 MFlop/s
Threads                  Mflop/s
               V1         V3 
-------------------------------------------------------------------------------
  1           3710       3740    
  2           7600       7760     
  4          15100      15300
  8          25100      25900
 16          29400      30100

Rerun on a batch node with 2.3 GHz
