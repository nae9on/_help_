FC=ifort
OMP=-qopenmp -g -O


all : race.exe

%.exe : %.f90
	$(FC) -o $@ $(OMP) $^


clean : 
	rm -rf *.exe *~ *.mod
