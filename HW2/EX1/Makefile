monte: monte.o
	g++ -O0 monte.o -o monte -lm

monte.o: monte.cc
	g++ -O0 -std=c++11 monte.cc -c

integrators.o: integrators.h
	g++ -O0 -std=c++11 integrators.h -c
