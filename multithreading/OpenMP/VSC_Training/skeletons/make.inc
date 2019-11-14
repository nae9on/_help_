ifndef COMPILER
COMPILER=GCC
endif

ifeq ($(COMPILER),Intel)
FC=ifort
CC=icc
FFLAGS=-standard-semantics
DEBUG=-g -traceback 
FPP=-fpp
FOPT=-O3 -xAVX  # for Sandy Bridge
COPT=-O3 -xAVX  
#FOPT=-O3 -xSSE2
#FOPT=-O3
F_IEEE=-assume fpe_summary -assume ieee_fpe_flags
# the above is implied by -standard-semantics
#F_IEEE=
SOPT=-shared -fpic
OMP=-qopenmp
LM=
endif

ifeq ($(COMPILER),GCC)
FC=gfortran
CC=gcc
FFLAGS=
DEBUG=-g -fbacktrace
FPP=-cpp
#FOPT=-O3
FOPT=-O3 -march=sandybridge -mavx -funroll-loops 
COPT=-O3 -march=sandybridge -mavx -funroll-loops 
#FOPT=-O3 -march=opteron -msse3 -funroll-loops 
SOPT=-shared -fpic
OMP=-fopenmp
LM=-lm
endif

ifeq ($(COMPILER),NAG)
FC=nagfor
CC=gcc
FFLAGS=-f2003
DEBUG=-g -gline -mtrace -C=all
FPP=-fpp
FOPT=-O3
F_IEEE=-ieee=full
SOPT=-Wl,-shared -pic
OMP=-openmp
endif

ifeq ($(COMPILER),CRAY)
FC=ftn
CC=cc
FFLAGS=-e m
DEBUG=-g 
endif

ifeq ($(COMPILER),PGI)
FC=pgf90
CC=pgcc
FFLAGS=
DEBUG=-g 
FOPT=-O3 -tp=shanghai-64
FPP=-Mpreprocess
F_IEEE=-Kieee
# NOTE: the above only impacts precision, not exception handling
SOPT=-shared -fpic
OMP=-openmp
endif

ifeq ($(COMPILER),IBM)
FC=xlf2003_r
CC=xlc_r
FFLAGS=
DEBUG=-g 
FOPT=-O4 -q64 -qhot=vector -qcache=auto -qalias=noaryovrlp
FPP=-qsuffix=cpp=f90
OMP=-mp
endif
