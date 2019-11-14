COMPILER=Intel
include ../make.inc
#
#FOPT+=$(DEBUG)


all: RAY_F.exe RAY_C.exe

RAY_C.exe: raytrace_c.o timing.o
	$(CC) $(OMP) -o RAY_C.exe raytrace_c.o timing.o $(LM)

RAY_F.exe: raytrace_f.o timing.o
	$(FC) $(OMP) -o RAY_F.exe raytrace_f.o timing.o

%.o: %.c
	$(CC) -c $(COPT) $(OMP) $(DIAG) $<

%.o: %.f90
	$(FC) -c $(FOPT) $(OMP) $(DIAG) $<

clean:
	rm -f *.o *.exe *.mod *.pnm *.optrpt

