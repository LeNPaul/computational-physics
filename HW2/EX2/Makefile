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

main.o: main.cc ranz.h

ranz.o: ranz.cc ranz.h

clean:
	rm *.o
