#COMPILER=Intel
include ../make.inc

all : hello_c.exe hello_f.exe

%.exe : %.c
	$(CC) $(COPT) -o $@ $^

%.exe : %.f90
	$(FC) $(COPT) -o $@ $^

clean :
	rm -rf *.exe *.o *.mod *~ 

