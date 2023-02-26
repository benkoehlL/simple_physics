CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

graphengenerierung: graphengenerierung.o
	    $(LD) $(LDFLAGS) -o graphengenerierung graphengenerierung.o -lgsl -lgslcblas -lm