CPP=g++
LINKER=g++
FFLAGS=-O -std=c++11
LFLAGS= 
OBJECTFILES=main.o jacobi.o

default: jacobi

jacobi: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

main.o: main.cc

jacobi.o: jacobi.cc

clean:
	rm *.o
