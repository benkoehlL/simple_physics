CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<
ALL: BaumWelch

BaumWelch: BaumWelch.o
	    $(LD) -o  BaumWelch BaumWelch.o -lgsl -lgslcblas -lm $(LDFLAGS)
