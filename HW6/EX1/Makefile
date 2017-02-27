CPP=g++
LINKER=g++
#FFLAGS=-O3 -openmp -std=c++11 -lomp
FFLAGS= -Wall -O3 -fopenmp -std=c++11

LFLAGS=-fopenmp
OBJECTFILES=main.o\

default: open

open: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@ 

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

main.o: main.cc

clean:
	rm *.o
