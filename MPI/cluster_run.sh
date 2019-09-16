#!/bin/sh

rm -f a.out

rm -f *log*

mpic++ hello_world_tutorial.cpp

export NUM_PROCS=4
export OMP_NUM_THREADS=3
mpirun -x OMP_NUM_THREADS -np $NUM_PROCS --output-filename log --map-by ppr:2:socket:pe=$OMP_NUM_THREADS --bind-to core --report-bindings ./a.out

#export NUM_PROCS=9
#export OMP_NUM_THREADS=4
#mpirun -x OMP_NUM_THREADS -np $NUM_PROCS --output-filename log --map-by node:pe=$OMP_NUM_THREADS --report-bindings ./a.out
