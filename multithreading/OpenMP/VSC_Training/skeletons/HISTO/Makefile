COMPILER=Intel
include ../make.inc


all : histogram_openmp_c.exe histogram_openmp_f.exe


histogram_openmp_c.exe : histogram_openmp_c.c timing.o
	$(CC) $(COPT) $(OMP) -o $@ $^
histogram_openmp_f.exe : histogram_openmp_f.f90 timing.o
	$(FC) $(FOPT) $(OMP) -o $@ $^

%.o : %.c
	$(CC) -c -o $@ $<

clean :
	rm -rf *.exe *.o *~
