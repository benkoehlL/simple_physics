CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<


Stabthomas: Stabthomas.o
	    $(LD) $(LDFLAGS) -o Stabthomas Stabthomas.o -lgsl -lgslcblas -lm