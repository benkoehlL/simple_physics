CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<
ALL: mastergleichungsumme 

mastergleichungsumme: mastergleichungsumme.o
	    $(LD) -o  mastergleichungsumme mastergleichungsumme.o -lgsl -lgslcblas -lm $(LDFLAGS)
