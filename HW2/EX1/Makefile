CPP=g++
LINKER=g++
FFLAGS=-O -std=c++11
LFLAGS= 
OBJECTFILES=main.o integrators.o

default: monte

monte: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

main.o: main.cc

integrators.o: integrators.cc

clean:
	rm *.o
