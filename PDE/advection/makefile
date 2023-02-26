CC=g++
LD=g++
CFLAGS=-O3 -pedantic

%.o: %.cpp parameter.h
	$(CC) -c $(CFLAGS) $<

ALL: advection

poisson: advection.o
	    $(LD) $(LDFLAGS) -o advection advection.o -lgsl -lgslcblas -lm

run:
	./advection
