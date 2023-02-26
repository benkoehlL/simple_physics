CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<
ALL: fraktal 

fraktal: fraktal.o
	    $(LD) -o  fraktal fraktal.o -lgsl -lgslcblas -lm $(LDFLAGS)
