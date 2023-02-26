CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

Transformation: Transformation.o
	    $(LD) $(LDFLAGS) -o Transformation Transformation.o -lgsl -lgslcblas -lm