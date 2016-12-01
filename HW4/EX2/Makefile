CPP=g++
LINKER=g++
FFLAGS=-O -std=c++11
LFLAGS= 
OBJECTFILES=main.o

default: laplace

laplace: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

main.o: main.cc

clean:
	rm *.o
