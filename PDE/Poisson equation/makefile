CC=g++
LD=g++
CFLAGS=-O3 -pedantic

%.o: %.cpp parameter.h
	$(CC) -c $(CFLAGS) $<

ALL: poisson

poisson: poisson.o
	    $(LD) $(LDFLAGS) -o poisson poisson.o -lgsl -lgslcblas -lm

run:
	./poisson
