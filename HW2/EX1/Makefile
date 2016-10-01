monte: monte.o integrators.o
	g++ -O0 monte.o integrators.o -o monte -lm

monte.o: monte.cc integrators.h
	g++ -O0 -std=c++11 monte.cc -c

integrators.o: integrators.cc
	g++ -O0 -std=c++11 integrators.cc -c
