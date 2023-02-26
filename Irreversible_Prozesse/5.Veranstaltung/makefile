CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

si: si.o
	    $(LD) $(LDFLAGS) -o si si.o -lgsl -lgslcblas -lm