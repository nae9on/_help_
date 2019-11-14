COMPILER=Intel
include ../make.inc


all : heat_omp_c.exe heat_omp_f.exe 

heat_omp_c.exe : heat_omp_c.c timing.o
	$(CC) $(OMP) $(COPT) -o $@ $^

heat_omp_f.exe : heat_omp_f.f90 
	$(FC) $(OMP) $(FOPT) -o $@ $^

clean :
	rm -rf *.exe *.o *~ *.mod
