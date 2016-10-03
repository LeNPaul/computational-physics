CPP=g++
LINKER=g++
FFLAGS=-O
LFLAGS=
OBJECTFILES=main.o

default: ising

fortest: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

main.o: main.cc

clean:
	rm *.o
