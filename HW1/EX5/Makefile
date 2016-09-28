integration: integration.o
	icc -O0 integration.o -o integration -lm

integration.o: integration.c
	icc -O0 integration.c -c

integrationFunctions.o: integrationFunctions.h
	icc -O0 integrationFunctions.h -c
