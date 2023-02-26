CC=g++
LD=g++
-std=c++11
CFLAGS=-O3 -pedantic
%.o: %.cpp parameter.h
	 $(CC) -c $(CFLAGS) $<

ALL: doublespringpend

doublepend: doublespringpend.o
	    $(LD) $(LDFLAGS) -o doublespringpend doublespringpend.o -lgsl -lgslcblas -lm
