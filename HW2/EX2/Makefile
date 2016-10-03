CPP=g++
LINKER=g++
FFLAGS=-O
LFLAGS=
OBJECTFILES=main.o ranz.o

default: random

random: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

main.o: main.cc

ranz.o: ranz.cc

clean:
	rm *.o
