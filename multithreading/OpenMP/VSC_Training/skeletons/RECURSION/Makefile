#
#       Makefile for Intel compiler
#
BHOME   =$(PWD)
#
F90     = ifort
CC      = icc
#
#
COMP    =  -openmp 
FOMP    =  -openmp
COPTS   =  -O3 -xSSE2 -fno-alias
FOPTS   =  -O3 -xSSE2 -fno-alias
FLONG   = -132
#
#
NOLINK= -c


all : recursion_f.exe recursion_c.exe

recursion_c.exe : recursion_c.c
	$(CC) -o $@ $(COMP) $^
recursion_f.exe : recursion_f.f90
	$(F90) -o $@ $(FOMP) $^

clean : 
	rm -f *~ *.o *.exe