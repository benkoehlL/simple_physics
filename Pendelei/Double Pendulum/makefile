CC=g++
LD=g++
-std=c++11
CFLAGS=-O3 -pedantic
%.o: %.cpp parameter.h
	 $(CC) -c $(CFLAGS) $<

ALL: doublepend

doublepend: doublepend.o
	    $(LD) $(LDFLAGS) -o doublepend doublepend.o -lgsl -lgslcblas -lm
