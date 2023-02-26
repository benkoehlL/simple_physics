CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<
ALL: Markov

Markov: Markov.o
	    $(LD) -o  Markov Markov.o -lgsl -lgslcblas -lm $(LDFLAGS)
