COMPILER=Intel
include ../make.inc

all : pi_rand_c.exe pi_rand_f.exe 

pi_rand_c.exe : pi_rand_c.c timing.o
	$(CC) $(COPT) $(OMP) -o $@ $^

pi_rand_f.exe : pi_rand_f.f90 timing.o
	$(FC) $(FOPT) $(OMP) -o $@ $^

%.o : %.c
	$(CC) -c -o $@ $<

clean :
	rm -rf *.exe *.o
