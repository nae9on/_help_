COMPILER=GCC
include ../make.inc

all : mvm_f.exe mvm_c.exe tri_mvm_c.exe tri_mvm_f.exe



%.exe : %.c 
	$(CC) $(COPT) $(OMP) -o $@ $^
%.exe : %.f90 
	$(FC) $(FOPT) $(OMP) -o $@ $^

clean : 
	rm -rf *.exe *~ *.mod *.o
